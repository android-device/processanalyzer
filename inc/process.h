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
	std::string fpath = "/tmp/"; //default location is /tmp
	std::string fname; //default file name is pname.log

	bool search = false; //default is to quit immediately if process is not found
	bool terminalOutput = false; //default is to output to file
	int logTimes = 0;

	bool keepLogging = true; //if logTimes is zero, keep logging until the process dies
	bool showOnce = true; //show the process details, only once

	procinfo pinfo; //uses more memory, but makes it easier to use in the future for trend analysis, etc
	std::ofstream outputFile;

    public:
	void set_pid(int npid) { this.pid = npid; }
	void set_pname(std::string npname) { this.pname = npname; }
	void set_fpath(std::string nfpath) { this.fpath = nfpath; }
	void set_fname(std::string nfname) { this.fname = nfname; }
	void set_search(bool nsearch) { this.search = nsearch; }
	void set_terminalOutput(bool nterminalOutput) { this.terminalOutput = nterminalOutput; }
	void set_logTimes(int nlogTimes) { this.logTimes = nlogTimes; }

	//only ever toggled, start set and are cleared once shown
	void set_keepLogging(bool nkeepLogging) { this.keepLogging = false; } 
	void set_showOnce() { this.showOnce = false; }

	int get_pid() { return this.pid; }
	int get_pname() { return this.pname; }
	int get_fpath() { return this.fpath; }
	int get_fname() { return this.fname; }
	int get_search() { return this.search; }
	int get_terminalOutput() { return this.terminalOutput; }
	int get_logTimes() { return this.logTimes; }
	int get_keepLogging() { return this.keepLogging; }
	int get_showOnce() { return this.showOnce; }

	void outputData();
};
