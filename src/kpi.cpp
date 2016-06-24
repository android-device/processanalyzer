#include "kpi.h"
//#define DEBUG

/* Search for a process, using the pid or the pname version of this overloaded
 * function. Note that if search is true, this function will NOT return until a
 * matching process is found - leading to an infinite loop! Use it only on
 * processes you know will eventually exist; this is very useful for measuring
 * the startup usage of a process.
 */
bool processSearch(bool search, int id) //overloaded
{
    procFile = "/proc/" + std::to_string(id) + "/stat";

#ifdef DEBUG
    if(search)
    {
	print_string("Will Search");
    }
    print_string(procFile);
#endif

    do {
	if(checkFile(procFile) != 0) { //read OR write, doesn't matter for the process
	    return true;
	}
    } while(search); //if search is set, loop until the process is found
    return false;
}

/* Overload for searching with pname instead of pid */
bool processSearch(bool search, std::string pname, int *pid) //overloaded
{
    if(pname == "")
    {
	print_string("Something terrible has happened.");
	return false;
    }
    do {
	//TODO multiple PIDs
	std::string pidofCmd = "pidof " + pname;
	std::string result = exec(pidofCmd.c_str());
	if(result != "") {
	    *pid = stoi(result);
	    return true;
	}
    } while(search); //keep searching until process is found
    return false;
}

bool processSearch(process currProcess)
{
    bool result = false;;
    if((currProcess.get_pname() != "") && (currProcess.get_pid() == 0)) //pname set, pid not set, search with pname
    {
	int pid = 0; //will be set in currprocess, can't be done by called function
	result = processSearch(currProcess.get_search(), currProcess.get_pname(), &pid);
	currProcess.set_pid(pid);
    } else {
	result = processSearch(currProcess.get_search(), currProcess.get_pid());
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
#ifdef DEBUG
	    if((pinfo->values[currIndex] != "") && (pinfo->values[currIndex] != currVal))
	    {
		print_string("Changed: " + pinfo.headers[currIndex] + " : " + pinfo->values[currIndex] + "->" + currVal);
	    }
#endif
	    pinfo->values[currIndex] = currVal;
	}

	currIndex++;
	currVal = "";
    }
    statFile.close();
    return -3; //less value available than are being used.
}
