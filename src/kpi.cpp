#include "kpi.h"
//#define DEBUG

//TODO: implement search
bool processSearch()
{
    procFile = "/proc/";
    procFile += pid;
    procFile += "/stat";
    return true;
}

int get_proc_info(procinfo * pinfo)
{
#ifdef DEBUG
    print_string("In get_proc_info");
#endif
    std::ifstream statFile;
    std::string proc_fname = "/proc/22552/stat";
    statFile.open(proc_fname.c_str());
    if(!statFile.is_open())
    {
	print_string("Failed to open /proc/"+pid+"/stat");
	return -1;
    }

    std::string currVal = "";
    int currIndex = 0;

    while(statFile.good())
    {
	statFile >> currVal;
	//add to pinfo based on the index of the current value being read
	switch(currIndex)
	{
	    case 0:
		pinfo->pid = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 1:
		pinfo->exName = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 2:
		pinfo->state = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 3:
		pinfo->euid = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 4:
		pinfo->egid = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 5:
		pinfo->ppid = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 6:
		pinfo->pgrp = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 7:
		pinfo->session = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 8:
		pinfo->tty = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 9:
		pinfo->tpgid = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 10:
		pinfo->flags = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 11:
		pinfo->minflt = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 12:
		pinfo->cminflt = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 13:
		pinfo->majflt = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 14:
		pinfo->cmajflt = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 15:
		pinfo->utime = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 16:
		pinfo->cutime = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 17:
		pinfo->cstime = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 18:
		pinfo->counter = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 19:
		pinfo->priority = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 20:
		pinfo->timeout = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 21:
		pinfo->itrealvalue = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 22:
		pinfo->starttime = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 23:
		pinfo->vsize = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 24:
		pinfo->rss = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 25:
		pinfo->rlim = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 26:
		pinfo->startcode = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 27:
		pinfo->endcode = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 28:
		pinfo->startstack = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 29:
		pinfo->kstkesp = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 31:
		pinfo->kstkeip = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 32:
		pinfo->blocked = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 33:
		pinfo->sigignore = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 34:
		pinfo->sigcatch = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 35:
		pinfo->wchan = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 36:
		pinfo->sched = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    case 37:
		pinfo->sched_priority = currVal;
#ifdef DEBUG
		print_string(currVal);
#endif
		break;
	    default: //More values available than are being used.
		statFile.close();
		return -2;
	}
	currIndex++;
	currVal = "";
    }
    statFile.close();
    return -3; //less value available than are being used.
}
