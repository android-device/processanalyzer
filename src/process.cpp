#include "process.h"

process::process() {
    //log file information
    fpath = "/tmp/"; //default location is /tmp
    fname; //default file name is pname.log

    search = false; //default is to quit immediately if process is not found
    terminalOutput = false; //default is to output to file
    logTimes = 0;

    keepLogging = true; //if logTimes is zero, keep logging until the process dies
    showOnce = true; //show the process details, only once
}

process& process::operator=(process nprocess)
{
    this->pid = nprocess.get_pid();
    this->pname = nprocess.get_pname();
    this->fpath = nprocess.get_fpath();
    this->fname = nprocess.get_fname();
    this->search = nprocess.get_search();
    this->terminalOutput = nprocess.get_terminalOutput();
    this->logTimes = nprocess.get_logTimes();
    this->keepLogging = nprocess.get_keepLogging();
    this->showOnce = nprocess.get_showOnce();
}
process::process(const process &nprocess)
{
    this->pid = nprocess.get_pid();
    this->pname = nprocess.get_pname();
    this->fpath = nprocess.get_fpath();
    this->fname = nprocess.get_fname();
    this->search = nprocess.get_search();
    this->terminalOutput = nprocess.get_terminalOutput();
    this->logTimes = nprocess.get_logTimes();
    this->keepLogging = nprocess.get_keepLogging();
    this->showOnce = nprocess.get_showOnce();
}

void process::outputData()
{
    if(this.terminalOutput)
    {
	std::string formattedVal = format_message(pinfo, outputSeparatorTerminal);
	print_string(formattedVal);
    } else {
	this.outputFile << format_message(this.pinfo, outputSeparatorFile) << std::endl;
    }
}

void process::set_pinfo(procinfo pinfo) {
    for(int currIndex=0; currIndex<NUMVALUES; currIndex++)
    {
	this->pinfo[currIndex] = pinfo[currIndex];
    }
}
