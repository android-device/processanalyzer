#include "kpi.h"
#define DEBUG

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
    std::string proc_fname = "/proc/"+pid+"/stat";
    statFile.open(proc_fname.c_str());
    if(!statFile.is_open())
    {
	print_string("Failed to open /proc/"+pid+"/stat");
	return -1;
    }

    std::string currVal = "";
    int currIndex = 0;
    char currChar;

    while(statFile.good())
    {
	statFile.get(currChar);
	if(currChar==' ') //stat file values are space delimited
	{
	    //add to pinfo based on the index of the current value being read
	    switch(currIndex) {
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
		    pinfo->euid = currVal;
		    break;
		case 4:
		    pinfo->egid = currVal;
		    break;
		case 5:
		    pinfo->ppid = currVal;
		    break;
		case 6:
		    pinfo->pgrp = currVal;
		    break;
		case 7:
		    pinfo->session = currVal;
		    break;
		case 8:
		    pinfo->tty = currVal;
		    break;
		case 9:
		    pinfo->tpgid = currVal;
		    break;
		case 10:
		    pinfo->flags = currVal;
		    break;
		case 11:
		    pinfo->minflt = currVal;
		    break;
		case 12:
		    pinfo->cminflt = currVal;
		    break;
		case 13:
		    pinfo->majflt = currVal;
		    break;
		case 14:
		    pinfo->cmajflt = currVal;
		    break;
		case 15:
		    pinfo->utime = currVal;
		    break;
		case 16:
		    pinfo->cutime = currVal;
		    break;
		case 17:
		    pinfo->cstime = currVal;
		    break;
		case 18:
		    pinfo->counter = currVal;
		    break;
		case 19:
		    pinfo->priority = currVal;
		    break;
		case 20:
		    pinfo->timeout = currVal;
		    break;
		case 21:
		    pinfo->itrealvalue = currVal;
		    break;
		case 22:
		    pinfo->starttime = currVal;
		    break;
		case 23:
		    pinfo->vsize = currVal;
		    break;
		case 24:
		    pinfo->rss = currVal;
		    break;
		case 25:
		    pinfo->rlim = currVal;
		    break;
		case 26:
		    pinfo->startcode = currVal;
		    break;
		case 27:
		    pinfo->endcode = currVal;
		    break;
		case 28:
		    pinfo->startstack = currVal;
		    break;
		case 29:
		    pinfo->kstkesp = currVal;
		    break;
		case 31:
		    pinfo->kstkeip = currVal;
		    break;
		case 32:
		    pinfo->blocked = currVal;
		    break;
		case 33:
		    pinfo->sigignore = currVal;
		    break;
		case 34:
		    pinfo->sigcatch = currVal;
		    break;
		case 35:
		    pinfo->wchan = currVal;
		    break;
		case 36:
		    pinfo->sched = currVal;
		    break;
		case 37:
		    pinfo->sched_priority = currVal;
		    break;
		default: //out of range??
		    return -1;
	    }

	    currIndex++;
	    currVal = "";
	}
	else
	{
	    currVal += currChar;
	}
	statFile.close();
    }
    return 0;
}
