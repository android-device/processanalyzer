/* Constant values for use in various functions throughout execution
 */
#ifndef KPI_CONSTS
#define KPI_CONSTS

//header to use for the log files, in csv format
static const char* logHeader = "state,utime,stime,cutime,cstime,priority,vsize,rss,rlim,starttime";

static char *kpiProg = NULL;              //  Pointer to program name
static char *kpiDev  = NULL;              //  Pointer to device or file name.


#endif
