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
	switch(currIndex)
	{
	    case 0:
		pinfo->pid = currVal;
		break;
	    case 1:
		pinfo->exName = currVal;
		break;
	    case 2:
		pinfo->state = currVal;
		break;
	    case 3:
		pinfo->ppid = currVal; //parent pid
		break;
	    case 4:
		pinfo->egid = currVal; //groud id
		break;
	    case 5:
		pinfo->session = currVal; //session id
		break;
	    case 6:
		pinfo->tty = currVal;
		break;
	    case 7:
		//euid??
		pinfo->euid = currVal; //foreground process group id
		break;
	    case 8:
		pinfo->flags = currVal;
		break;
	    case 9:
		pinfo->minflt = currVal; //minor faults
		break;
	    case 10:
		pinfo->cminflt = currVal; //minor faults with children
		break;
	    case 11:
		pinfo->majflt = currVal;
		break;
	    case 12:
		pinfo->cmajflt = currVal;
		break;
	    case 13:
		pinfo->utime = currVal; //Time process spent in user mode (clock ticks)
		break;
	    case 14:
		pinfo->stime = currVal; //Time spent in kernel mode
		break;
	    case 15:
		pinfo->cutime = currVal; //Child time in user mode
		break;
	    case 16:
		pinfo->cstime = currVal; //Child time in kernel mode
		break;
	    case 17:
		pinfo->priority = currVal; //nice value + 15 (?)
		break;
	    case 18:
		//the nice value
		break;
	    case 19:
		pinfo->numThreads = currVal;
		break;
	    case 20:
		pinfo->itrealvalue = currVal; //time before sigalarm is sent
		break;
	    case 21:
		pinfo->starttime = currVal;
		break;
	    case 22:
		pinfo->vsize = currVal; //virtual memory size
		break;
	    case 23:
		pinfo->rss = currVal;
		break;
	    case 24:
		pinfo->rlim = currVal;
		break;
	    case 25:
		pinfo->startcode = currVal;
		break;
	    case 26:
		pinfo->endcode = currVal;
		break;
	    case 27:
		pinfo->startstack = currVal;
		break;
	    case 28:
		pinfo->kstkesp = currVal; //current ESP (stack pointer)
		break;
	    case 29:
		pinfo->kstkeip = currVal; //current EIP (instruction pointer)
		break;
	    case 30:
		//OBSOLETE INFO - signal
		break;
	    case 31:
		//OBSOLETE INFO - blocked
		break;
	    case 32:
		//OBSOLETE INFO - sigignore
		break;
	    case 33:
		//OBSOLETE INFO - sigcatch
		break;
	    case 34:
		pinfo->wchan = currVal; //channel in which the process is waiting
		break;
	    case 35:
		//number of pages swapped
		break;
	    case 36:
		//number of pages swapped for child processes
		break;
	    case 37:
		//signal sent to parent when process dies
		break;
	    default: 
		if(currIndex > 37) //More values available than are being used.
		{
		    statFile.close();
		    return -2;
		} else { //Missed a value!
		    print_string("Skipped " + std::to_string(currIndex));
		}
	}
	currIndex++;
	currVal = "";
    }
    statFile.close();
    return -3; //less value available than are being used.
}
