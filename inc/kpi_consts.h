/* Constant values for use in various functions throughout execution.
 * This is where all the static values and constants are kept, so they can be
 * easily changed later.
 */
#ifndef KPI_CONSTS
#define KPI_CONSTS

#include <string>

/* Help message for -h, and bad input...
 * Possible parameters:
 * i pId
 * n process Name
 * p file Path
 * f File name
 * s keep Searching
 * o Output to terminal
 * h show Help
 */
static const std::string helpMessage = "KPI Analyzer logs the cpu and memory usage of a process\n-i <pid>\n-n <process name>\tWill search in ps with grep to find the pid\n-f <filename>\n-p <path>\t\tPath to where the output log should be written\n-s\t\t\tDo no stop execution if the program is not found, keep searching for it until it starts - useful if running the analyzer before the process is started.\n-o\t\t\tOutput to terminal instead of file\n-h\t\t\tShow this message";

//process identifiers
static std::string pid = "";
static std::string pname = "";

//log file information
static std::string fpath = "/tmp"; //default location is /tmp
static std::string fname; //default file name is pname.log

static bool search = false; //default is to quit immediately if process is not found
static bool terminalOutput = true; //default is to output to file

//header to use for the log files, in csv format
static const std::string  logHeader = "state,utime,stime,cutime,cstime,priority,vsize,rss,rlim,starttime";

// Pointer to program name
static std::string kpiProg = "CPU/Mem Analyzer";

//struct from: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html
typedef struct statstruct_proc {
    int           pid;                      /** The process id. **/
    char*          exName; /** The filename of the executable **/
    char*          state; /** 1 **/          /** R is running, S is sleeping, 
					      D is sleeping in an uninterruptible wait,
					      Z is zombie, T is traced or stopped **/
    unsigned      euid,                      /** effective user id **/
		  egid;                      /** effective group id */					     
    int           ppid;                     /** The pid of the parent. **/
    int           pgrp;                     /** The pgrp of the process. **/
    int           session;                  /** The session id of the process. **/
    int           tty;                      /** The tty the process uses **/
    int           tpgid;                    /** (too long) **/
    unsigned int	flags;                    /** The flags of the process. **/
    unsigned int	minflt;                   /** The number of minor faults **/
    unsigned int	cminflt;                  /** The number of minor faults with childs **/
    unsigned int	majflt;                   /** The number of major faults **/
    unsigned int  cmajflt;                  /** The number of major faults with childs **/
    int           utime;                    /** user mode jiffies **/
    int           stime;                    /** kernel mode jiffies **/
    int		cutime;                   /** user mode jiffies with childs **/
    int           cstime;                   /** kernel mode jiffies with childs **/
    int           counter;                  /** process's next timeslice **/
    int           priority;                 /** the standard nice value, plus fifteen **/
    unsigned int  timeout;                  /** The time in jiffies of the next timeout **/
    unsigned int  itrealvalue;              /** The time before the next SIGALRM is sent to the process **/
    int           starttime; /** 20 **/     /** Time the process started after system boot **/
    unsigned int  vsize;                    /** Virtual memory size **/
    unsigned int  rss;                      /** Resident Set Size **/
    unsigned int  rlim;                     /** Current limit in bytes on the rss **/
    unsigned int  startcode;                /** The address above which program text can run **/
    unsigned int	endcode;                  /** The address below which program text can run **/
    unsigned int  startstack;               /** The address of the start of the stack **/
    unsigned int  kstkesp;                  /** The current value of ESP **/
    unsigned int  kstkeip;                 /** The current value of EIP **/
    int		signal;                   /** The bitmap of pending signals **/
    int           blocked; /** 30 **/       /** The bitmap of blocked signals **/
    int           sigignore;                /** The bitmap of ignored signals **/
    int           sigcatch;                 /** The bitmap of catched signals **/
    unsigned int  wchan;  /** 33 **/        /** (too long) **/
    int		sched, 		  /** scheduler **/
		sched_priority;		  /** scheduler priority **/

} procinfo;

#endif
