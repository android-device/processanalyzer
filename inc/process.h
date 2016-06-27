#ifndef PROCESS
#define PROCESS

#include "kpi_consts.h"
#include <fstream>
#include <string>
#include "print.h"

class process {
    private:
	//process identifiers
	int pid;
	std::string pname;

	//log file information
	std::string fpath; //default location is /tmp
	std::string fname; //default file name is pname.log

	bool search; //default is to quit immediately if process is not found
	bool terminalOutput; //default is to output to file
	bool running; //used to determine whether to search for a process before attempting to read it's data
	int logTimes;

	bool keepLogging; //if logTimes is zero, keep logging until the process dies
	bool showOnce; //show the process details, only once

	procinfo pinfo; //uses more memory, but makes it easier to use in the future for trend analysis, etc
	std::ofstream outputFile;

    public:
	process();
	process& operator=(const process&);
	process(const process&);

	void set_pid(int npid) { pid = npid; }
	void set_pname(std::string);
	void set_fpath(std::string nfpath) { fpath = nfpath; }
	void set_fname(std::string nfname) { fname = nfname; }
	void set_search(bool nsearch) { search = nsearch; }
	void set_terminalOutput() { terminalOutput = true; } //defaults to false, only ever set
	void set_logTimes(int nlogTimes) { logTimes = nlogTimes; }
	void increment_logTimes() { logTimes++; }

	void set_pinfo(procinfo npinfo);

	//only ever cleared, start set and are cleared once shown
	void clear_keepLogging() { keepLogging = false; } 
	void clear_showOnce() { showOnce = false; }
	void set_running() { running = true; }
	void clear_running() { running = false; } //used if the state becomes DEAD

	int get_pid() { return pid; }
	std::string get_pname() { return pname; }
	std::string get_fpath() { return fpath; }
	std::string get_fname() { return fname; }
	bool get_search() { return search; }
	bool get_terminalOutput() { return terminalOutput; }
	int get_logTimes() { return logTimes; }
	bool get_keepLogging() { return keepLogging; }
	bool get_showOnce() { return showOnce; }
	bool is_running() { return running; }

	void outputData();
};

#endif
