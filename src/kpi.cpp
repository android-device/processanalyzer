#include "kpi.h"

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
    char *szStatStr; //buffer
    char *s, *t;
    FILE *fp;

    if((fp = fopen(procFile.c_str(), "r")) == NULL) {
	return(pinfo->pid = -1);
    }

    if((s = fgets(szStatStr, 2048, fp)) == NULL) {
	fclose(fp);
	return(pinfo->pid = -1);
    }

    /** pid **/
    sscanf(szStatStr, "%u", &(pinfo->pid));
    s = strchr(szStatStr, '(') + 1;
    t = strchr(szStatStr, ')');
    strncpy(pinfo->exName, s, t - s);
    pinfo->exName [t - s] = '\0';

    sscanf(t + 2, "%c %d %d %d %d %d %u %u %u %u %u %d %d %d %d %d %d %u %u %d %u %u %u %u %u %u %u %u %d %d %d %d %u",
	    /*       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33*/
	    &(pinfo->state),
	    &(pinfo->ppid),
	    &(pinfo->pgrp),
	    &(pinfo->session),
	    &(pinfo->tty),
	    &(pinfo->tpgid),
	    &(pinfo->flags),
	    &(pinfo->minflt),
	    &(pinfo->cminflt),
	    &(pinfo->majflt),
	    &(pinfo->cmajflt),
	    &(pinfo->utime),
	    &(pinfo->stime),
	    &(pinfo->cutime),
	    &(pinfo->cstime),
	    &(pinfo->counter),
	    &(pinfo->priority),
	    &(pinfo->timeout),
	    &(pinfo->itrealvalue),
	    &(pinfo->starttime),
	    &(pinfo->vsize),
	    &(pinfo->rss),
	    &(pinfo->rlim),
	    &(pinfo->startcode),
	    &(pinfo->endcode),
	    &(pinfo->startstack),
	    &(pinfo->kstkesp),
	    &(pinfo->kstkeip),
	    &(pinfo->signal),
	    &(pinfo->blocked),
	    &(pinfo->sigignore),
	    &(pinfo->sigcatch),
	    &(pinfo->wchan));
    fclose(fp);
    return 0;
}
