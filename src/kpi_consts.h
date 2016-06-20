/* Constant values for use in various functions throughout execution
 */
#ifndef KPI_CONSTS
#define KPI_CONSTS

/* Help message for -h, and bad input...
 * Possible parameters:
 * i pId
 * n process Name
 * p file Path
 * f File name
 * s keep Searching
 * h show Help
 */
static const char *helpMessage = "KPI Analyzer logs the cpu and memory usage of a process\n-i <pid>\n-n <process name>\tWill search in ps with grep to find the pid\n-f <filename>\n-p <path>\t Path to where the output log should be written\n-s\tDo no stop execution if the program is not found, keep searching for it until it starts - useful if running the analyzer before the process is started.\n-h\tShow this message";

//header to use for the log files, in csv format
static const char* logHeader = "state,utime,stime,cutime,cstime,priority,vsize,rss,rlim,starttime";

// Pointer to program name
static char *kpiProg = NULL;

// Pointer to device or file name.
static char *kpiDev  = NULL;

static char *fpath = "/tmp";

static char *fname;

#endif
