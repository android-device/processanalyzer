#include "kpi.h"
#define DEBUG

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
#ifdef DEBUG
		if((pinfo->pid != "") && (pinfo->pid != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->pid = currVal;
		break;
	    case 1:
#ifdef DEBUG
		if((pinfo->exName != "") && (pinfo->exName != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->exName = currVal;
		break;
	    case 2:
#ifdef DEBUG
		if((pinfo->state != "") && (pinfo->state != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->state = currVal;
		break;
	    case 3:
#ifdef DEBUG
		if((pinfo->ppid != "") && (pinfo->ppid != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->ppid = currVal; //parent pid
		break;
	    case 4:
#ifdef DEBUG
		if((pinfo->egid != "") && (pinfo->egid != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->egid = currVal; //groud id
		break;
	    case 5:
#ifdef DEBUG
		if((pinfo->session != "") && (pinfo->session != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->session = currVal; //session id
		break;
	    case 6:
#ifdef DEBUG
		if((pinfo->tty != "") && (pinfo->tty != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->tty = currVal;
		break;
	    case 7:
#ifdef DEBUG
		if((pinfo->euid != "") && (pinfo->euid != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->euid = currVal; //foreground process group id
		//euid??
		break;
	    case 8:
#ifdef DEBUG
		if((pinfo->flags != "") && (pinfo->flags != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->flags = currVal;
		break;
	    case 9:
#ifdef DEBUG
		if((pinfo->minflt != "") && (pinfo->minflt != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->minflt = currVal; //minor faults
		break;
	    case 10:
#ifdef DEBUG
		if((pinfo->cminflt != "") && (pinfo->cminflt != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->cminflt = currVal; //minor faults with children
		break;
	    case 11:
#ifdef DEBUG
		if((pinfo->majflt != "") && (pinfo->majflt != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->majflt = currVal;
		break;
	    case 12:
#ifdef DEBUG
		if((pinfo->cmajflt != "") && (pinfo->cmajflt != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->cmajflt = currVal;
		break;
	    case 13:
#ifdef DEBUG
		if((pinfo->utime != "") && (pinfo->utime != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->utime = currVal; //Time process spent in user mode (clock ticks)
		break;
	    case 14:
#ifdef DEBUG
		if((pinfo->stime != "") && (pinfo->stime != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->stime = currVal; //Time spent in kernel mode
		break;
	    case 15:
#ifdef DEBUG
		if((pinfo->cutime != "") && (pinfo->cutime != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->cutime = currVal; //Child time in user mode
		break;
	    case 16:
#ifdef DEBUG
		if((pinfo->cstime != "") && (pinfo->cstime != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->cstime = currVal; //Child time in kernel mode
		break;
	    case 17:
#ifdef DEBUG
		if((pinfo->priority != "") && (pinfo->priority != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->priority = currVal; //nice value + 15 (?)
		break;
	    case 18:
		//the nice value
		break;
	    case 19:
#ifdef DEBUG
		if((pinfo->numThreads != "") && (pinfo->numThreads != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->numThreads = currVal;
		break;
	    case 20:
#ifdef DEBUG
		if((pinfo->itrealvalue != "") && (pinfo->itrealvalue != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->itrealvalue = currVal; //time before sigalarm is sent
		break;
	    case 21:
#ifdef DEBUG
		if((pinfo->starttime != "") && (pinfo->starttime != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->starttime = currVal;
		break;
	    case 22:
#ifdef DEBUG
		if((pinfo->vsize != "") && (pinfo->vsize != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->vsize = currVal; //virtual memory size
		break;
	    case 23:
#ifdef DEBUG
		if((pinfo->rss != "") && (pinfo->rss != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->rss = currVal;
		break;
	    case 24:
#ifdef DEBUG
		if((pinfo->rlim != "") && (pinfo->rlim != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->rlim = currVal;
		break;
	    case 25:
#ifdef DEBUG
		if((pinfo->startcode != "") && (pinfo->startcode != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->startcode = currVal;
		break;
	    case 26:
#ifdef DEBUG
		if((pinfo->endcode != "") && (pinfo->endcode != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->endcode = currVal;
		break;
	    case 27:
#ifdef DEBUG
		if((pinfo->startstack != "") && (pinfo->startstack != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->startstack = currVal;
		break;
	    case 28:
#ifdef DEBUG
		if((pinfo->kstkesp != "") && (pinfo->kstkesp != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
		pinfo->kstkesp = currVal; //current ESP (stack pointer)
		break;
	    case 29:
#ifdef DEBUG
		if((pinfo->kstkeip != "") && (pinfo->kstkeip != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
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
#ifdef DEBUG
		if((pinfo->wchan != "") && (pinfo->wchan != currVal))
		{
		    print_string("Changed: " + currVal + ": " + std::to_string(currIndex));
		}
#endif
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
