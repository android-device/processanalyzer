/* Constant values for use in various functions throughout execution.
 * This is where all the static values and constants are kept, so they can be
 * easily changed later.
 */
#ifndef KPI_CONSTS
#define KPI_CONSTS

#include <string>
#include <fstream>

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

//header to use for the log files, in csv format
static const std::string  logHeader = "state,utime,stime,cutime,cstime,priority,vsize,rss,rlim,starttime";

// Pointer to program name
static std::string kpiProg = "CPU/Mem Analyzer";

//struct from: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html
// NOTE: Every value has been changed to a string to facilitate reading/writing
// in files
typedef struct statstruct_proc {
    std::string pid,	/** The process id. **/
	exName,		/** The filename of the executable **/
	state,		/** R is running, S is sleeping, 
				D is sleeping in an uninterruptible wait,
				Z is zombie, T is traced or stopped **/
	euid,		/** effective user id **/
	egid,		/** effective group id */
	ppid,		/** The pid of the parent. **/
	pgrp,		/** The pgrp of the process. **/
	session,	/** The session id of the process. **/
	tty,		/** The tty the process uses **/
	tpgid,		/** (too long) **/
	flags,		/** The flags of the process. **/
	minflt,		/** The number of minor faults **/
	cminflt,	/** The number of minor faults with childs **/
	majflt,		/** The number of major faults **/
	cmajflt,	/** The number of major faults with childs **/
	utime,		/** user mode jiffies **/
	stime,		/** kernel mode jiffies **/
	cutime,		/** user mode jiffies with childs **/
	cstime,		/** kernel mode jiffies with childs **/
	counter,	/** process's next timeslice **/
	priority,	/** the standard nice value, plus fifteen **/
	timeout,	/** The time in jiffies of the next timeout **/
	itrealvalue,	/** The time before the next SIGALRM is sent to the process **/
	starttime,	/** 20 **/     /** Time the process started after system boot **/
	vsize,		/** Virtual memory size **/
	rss,		/** Resident Set Size **/
	rlim,		/** Current limit in bytes on the rss **/
	startcode,	/** The address above which program text can run **/
	endcode,	/** The address below which program text can run **/
	startstack,	/** The address of the start of the stack **/
	kstkesp,	/** The current value of ESP **/
	kstkeip,	/** The current value of EIP **/
	signal,		/** The bitmap of pending signals **/
	blocked,	/** 30 **/       /** The bitmap of blocked signals **/
	sigignore,	/** The bitmap of ignored signals **/
	sigcatch,	/** The bitmap of catched signals **/
	wchan,		/** 33 **/        /** (too long) **/
	sched,		/** scheduler **/
	sched_priority;	/** scheduler priority **/
} procinfo;

#endif
