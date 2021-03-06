#include "kpi.h"
//#define DEBUG

/* Search for a process, using the pid or the pname version of this overloaded
 * function. Note that if search is true, this function will NOT return until a
 * matching process is found - leading to an infinite loop! Use it only on
 * processes you know will eventually exist; this is very useful for measuring
 * the startup usage of a process.
 *
 * This function is not public.
 */
bool processSearch(int id) //overloaded
{
    bool result = false;
    std::string procFile = "/proc/" + std::to_string(id) + "/stat";

    if(checkFile(procFile) != 0) { //read OR write, doesn't matter for the process
	result = true;
    }
    return result;
}

/* Overload for searching with pname instead of pid
 * 
 * This function is not public.
 */
bool processSearch(std::string pname, int *pid) //overloaded
{
    bool result = false;
    if(pname == "")
    {
	print_string("No pname specified.");
	result = false;
    } else { //pname specified
	//TODO multiple PIDs
	std::string pidofCmd = "pidof " + pname;
	std::string result_str = exec(pidofCmd.c_str());
	if(result_str != "")
	{
	    *pid = stoi(result_str);
	    result = true;
	}
    }
    return result;
}

bool processSearch(process &currProcess)
{
    bool result = false;;
    if((currProcess.get_pname() != "") && (currProcess.get_pid() == 0)) //pname set, pid not set, search with pname
    {
#ifdef DEBUG
	print_string("Using Name Search");
#endif
	int pid = 0; //will be set in currprocess, can't be done by this function
	result = processSearch(currProcess.get_pname(), &pid);
	currProcess.set_pid(pid);
    } else {
#ifdef DEBUG
	print_string("Using PID Search");
#endif
	result = processSearch(currProcess.get_pid());
    }
    return result;
}

int get_proc_info(procinfo *pinfo, int pid)
{
    std::ifstream statFile;
    std::string proc_fname = "/proc/"+std::to_string(pid)+"/stat";

#ifdef DEBUG
    print_string("In get_proc_info");
    print_string("PID is: " + std::to_string(pid));
    print_string(proc_fname);
#endif
    statFile.open(proc_fname.c_str());
    if(!statFile.is_open())
    {
	print_string("Failed to open /proc/"+std::to_string(pid)+"/stat");
	return -1;
    }

    std::string currVal = "";
    int currIndex = 0;

    while(statFile.good())
    {
	statFile >> currVal;
	/* add to pinfo based on the index of the current value being read. If
	 * reordering, refer to kpi_consts.h for the names of each.
	 * Based on: http://linux.die.net/man/5/proc
	 */
#ifdef DEBUG
	print_string(std::to_string(currIndex) + ", " + currVal);
#endif

	if(currIndex < NUMVALUES) //is within valid range
	{
	    pinfo->values[currIndex] = currVal;
	}

	currIndex++;
	currVal = "";
    }
    statFile.close();
    return -3; //less value available than are being used.
}

void getAndShow(process &currProcess) {
    procinfo pinfo;
    switch(get_proc_info(&pinfo, currProcess.get_pid()))
    {
	case -3: //error condition
	    //TODO error handling
#ifdef DEBUG
	    print_string("Not all pinfo values filled");
#endif
	    break;
	case -2: //error condition
#ifdef DEBUG
	    print_string("Extraneous values, some not read");
#endif
	    break;
	case -1: //error condition
	    currProcess.clear_keepLogging();
	    print_string("Error while opening stat file");
	    break;
	case 0: //do nothing
	    break;
	default:
	    currProcess.clear_keepLogging();
	    print_string("Unkown exit condition");
	    break;
    }

    currProcess.set_pinfo(pinfo);

    if(currProcess.get_fname() == "") //use the pid
    {
#ifdef DEBUG
	print_string("Using PID");
#endif
	if(currProcess.get_pname() == "") //set the pname for the log file.
	{
#ifdef DEBUG
	    print_string("Setting pname");
#endif
	    currProcess.set_pname(pinfo.values[cpu_comm]);
	    if(currProcess.get_terminalOutput()) //show pname if not set and outputting to terminal
	    {
		print_string(std::to_string(currProcess.get_pid()) + " pname is: " + currProcess.get_pname());
	    }
	}
	if(!currProcess.get_terminalOutput()) //don't care about the log file if not logging....
	{
#ifdef DEBUG
	    print_string("Setting logname");
#endif
	    currProcess.set_fname(currProcess.get_pname()+ "." + pinfo.values[cpu_pid] + ".log");
	}
    }

    //only show logname once, and only if outputting to a log
    if(currProcess.get_showOnce() && !currProcess.get_terminalOutput())
    {
#ifdef DEBUG
	print_string("Show Once, not terminalOutput");
#endif
	print_string("Log File: " + currProcess.get_fpath() + currProcess.get_fname());
    }

    if(pinfo.values[cpu_state] == "D") //D for DEAD
    {
#ifdef DEBUG
	print_string("DEAD");
#endif
	/* No idea what pid will be if  it comes back! Execution will never
	 * stop if search is set and it never comes back. pname should be set
	 * by now.
	 * Will continue to search, by pname only.
	 */
	currProcess.set_pid(0);
	currProcess.clear_running();
	if(!currProcess.get_search()) {
	    currProcess.clear_keepLogging();
	}
    }
    currProcess.clear_showOnce();

    currProcess.outputData();
}
