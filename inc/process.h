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
	int logTimes;

	bool keepLogging; //if logTimes is zero, keep logging until the process dies
	bool showOnce; //show the process details, only once

	procinfo pinfo; //uses more memory, but makes it easier to use in the future for trend analysis, etc
	std::ofstream outputFile;

    public:
	process();
	process& operator=(process);
	process(const process&);

	void set_pid(int npid) { this->pid = npid; }
	void set_pname(std::string npname) { this->pname = npname; }
	void set_fpath(std::string nfpath) { this->fpath = nfpath; }
	void set_fname(std::string nfname) { this->fname = nfname; }
	void set_search(bool nsearch) { this->search = nsearch; }
	void set_terminalOutput(bool nterminalOutput) { this->terminalOutput = nterminalOutput; }
	void set_logTimes(int nlogTimes) { this->logTimes = nlogTimes; }

	void set_pinfo(procinfo npinfo);

	//only ever cleared, start set and are cleared once shown
	void set_keepLogging(bool nkeepLogging) { this->keepLogging = false; } 
	void set_showOnce() { this->showOnce = false; }

	int get_pid() { return this->pid; }
	std::string get_pname() { return this->pname; }
	std::string get_fpath() { return this->fpath; }
	std::string get_fname() { return this->fname; }
	bool get_search() { return this->search; }
	bool get_terminalOutput() { return this->terminalOutput; }
	int get_logTimes() { return this->logTimes; }
	bool get_keepLogging() { return this->keepLogging; }
	bool get_showOnce() { return this->showOnce; }

	void outputData();
};

#endif
