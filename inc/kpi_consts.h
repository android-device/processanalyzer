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
static const std::string  logHeader = "state,\tutime,\tstime,\tcutime,\tcstime,\tpriority,\tvsize,\trss,\trlim,\tstarttime";

// Pointer to program name
static std::string kpiProg = "CPU/Mem Analyzer";

/* Refer to http://man7.org/linux/man-pages/man5/proc.5.html for the
 * explanation of each value.
 * 
 * When modifying, change the order here to change the order in the output.
 * 
 * If adding or removing values, remember to change NUMVALUES
 */
#define NUMVALUES 52
enum pinfoVal {
    cpu_pid,
    cpu_comm,
    cpu_state,
    cpu_ppid,
    cpu_pgrp,
    cpu_session,
    cpu_tty_nr,
    cpu_tpgid,
    cpu_flags,
    cpu_minflt,
    cpu_cminflt,
    cpu_majflt,
    cpu_cmajflt,
    cpu_utime,
    cpu_stime,
    cpu_cutime,
    cpu_cstime,
    cpu_priority,
    cpu_nice,
    cpu_numThreads,
    cpu_itrealvalue,
    cpu_starttime,
    cpu_vsize,
    cpu_rss,
    cpu_rlim,
    cpu_startcode,
    cpu_endcode,
    cpu_startstack,
    cpu_kstkesp,
    cpu_kstkeip,
    cpu_signal,
    cpu_blocked,
    cpu_sigignore,
    cpu_sigcatch,
    cpu_wchan,
    cpu_nswap,
    cpu_cnswap,
    cpu_exit_signal,
    cpu_processor,
    cpu_rt_priority,
    cpu_policy,
    cpu_delayacct_blkio_ticks,
    cpu_guest_time,
    cpu_cguest_time,
    cpu_start_data,
    cpu_end_data,
    cpu_start_brk,
    cpu_arg_start,
    cpu_arg_end,
    cpu_env_start,
    cpu_env_end,
    cpu_exit_code
};

typedef struct statstruct_proc {
    std::string values[NUMVALUES];
} procinfo;

#endif
