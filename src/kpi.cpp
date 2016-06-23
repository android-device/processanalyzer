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
	    case cpu_pid:
		pinfo->values[cpu_pid] = currVal;
		break;
	    case cpu_comm:
		pinfo->values[cpu_comm] = currVal;
		break;
	    case cpu_state:
		pinfo->values[cpu_state] = currVal;
		break;
	    case cpu_ppid:
		pinfo->values[cpu_ppid] = currVal;
		break;
	    case cpu_pgrp:
		pinfo->values[cpu_pgrp] = currVal;
		break;
	    case cpu_session:
		pinfo->values[cpu_session] = currVal;
		break;
	    case cpu_tty_nr:
		pinfo->values[cpu_tty_nr] = currVal;
		break;
	    case cpu_tpgid:
		pinfo->values[cpu_tpgid] = currVal;
		break;
	    case cpu_flags:
		pinfo->values[cpu_flags] = currVal;
		break;
	    case cpu_minflt:
		pinfo->values[cpu_minflt] = currVal;
		break;
	    case cpu_cminflt:
		pinfo->values[cpu_cminflt] = currVal;
		break;
	    case cpu_majflt:
		pinfo->values[cpu_majflt] = currVal;
		break;
	    case cpu_cmajflt:
		pinfo->values[cpu_cmajflt] = currVal;
		break;
	    case cpu_utime:
		pinfo->values[cpu_utime] = currVal;
		break;
	    case cpu_stime:
		pinfo->values[cpu_stime] = currVal;
		break;
	    case cpu_cutime:
		pinfo->values[cpu_cutime] = currVal;
		break;
	    case cpu_cstime:
		pinfo->values[cpu_cstime] = currVal;
		break;
	    case cpu_priority:
		pinfo->values[cpu_priority] = currVal;
		break;
	    case cpu_nice:
		pinfo->values[cpu_nice] = currVal;
		break;
	    case cpu_numThreads:
		pinfo->values[cpu_numThreads] = currVal;
		break;
	    case cpu_itrealvalue:
		pinfo->values[cpu_itrealvalue] = currVal;
		break;
	    case cpu_starttime:
		pinfo->values[cpu_starttime] = currVal;
		break;
	    case cpu_vsize:
		pinfo->values[cpu_vsize] = currVal;
		break;
	    case cpu_rss:
		pinfo->values[cpu_rss] = currVal;
		break;
	    case cpu_startcode:
		pinfo->values[cpu_startcode] = currVal;
		break;
	    case cpu_endcode:
		pinfo->values[cpu_endcode] = currVal;
		break;
	    case cpu_startstack:
		pinfo->values[cpu_startstack] = currVal;
		break;
	    case cpu_kstkesp:
		pinfo->values[cpu_kstkesp] = currVal;
		break;
	    case cpu_kstkeip:
		pinfo->values[cpu_kstkeip] = currVal;
		break;
	    case cpu_signal:
		pinfo->values[cpu_signal] = currVal;
		break;
	    case cpu_blocked:
		pinfo->values[cpu_blocked] = currVal;
		break;
	    case cpu_sigignore:
		pinfo->values[cpu_sigignore] = currVal;
		break;
	    case cpu_sigcatch:
		pinfo->values[cpu_sigcatch] = currVal;
		break;
	    case cpu_wchan:
		pinfo->values[cpu_wchan] = currVal;
		break;
	    case cpu_nswap:
		pinfo->values[cpu_nswap] = currVal;
		break;
	    case cpu_cnswap:
		pinfo->values[cpu_cnswap] = currVal;
		break;
	    case cpu_exit_signal:
		pinfo->values[cpu_exit_signal] = currVal;
		break;
	    case cpu_processor:
		pinfo->values[cpu_processor] = currVal;
		break;
	    case cpu_rt_priority:
		pinfo->values[cpu_rt_priority] = currVal;
		break;
	    case cpu_policy:
		pinfo->values[cpu_policy] = currVal;
		break;
	    case cpu_delayacct_blkio_ticks:
		pinfo->values[cpu_delayacct_blkio_ticks] = currVal;
		break;
	    case cpu_guest_time:
		pinfo->values[cpu_guest_time] = currVal;
		break;
	    case cpu_cguest_time:
		pinfo->values[cpu_cguest_time] = currVal;
		break;
	    case cpu_start_data:
		pinfo->values[cpu_start_data] = currVal;
		break;
	    case cpu_end_data:
		pinfo->values[cpu_end_data] = currVal;
		break;
	    case cpu_start_brk:
		pinfo->values[cpu_start_brk] = currVal;
		break;
	    case cpu_arg_start:
		pinfo->values[cpu_arg_start] = currVal;
		break;
	    case cpu_arg_end:
		pinfo->values[cpu_arg_end] = currVal;
		break;
	    case cpu_env_start:
		pinfo->values[cpu_env_start] = currVal;
		break;
	    case cpu_env_end:
		pinfo->values[cpu_env_end] = currVal;
		break;
	    case cpu_exit_code:
		pinfo->values[cpu_exit_code] = currVal;
		break;
	}
	currIndex++;
	currVal = "";
    }
    statFile.close();
    return -3; //less value available than are being used.
}
