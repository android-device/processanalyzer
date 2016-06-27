#include "process.h"
//#define DEBUG

process::process() {
    //log file information
    fpath = "/tmp/"; //default location is /tmp
    fname; //default file name is pname.log, which is set later

    search = false; //default is to quit immediately if process is not found
    terminalOutput = false; //default is to output to file
    logTimes = 0; //default is never stop

    keepLogging = true; //if logTimes is zero, keep logging until the process dies
    showOnce = true; //show the process details, only once
}

process& process::operator=(const process &nprocess)
{
    pid = nprocess.pid;
    pname = nprocess.pname;
    fpath = nprocess.fpath;
    fname = nprocess.fname;
    search = nprocess.search;
    terminalOutput = nprocess.terminalOutput;
    logTimes = nprocess.logTimes;
    keepLogging = nprocess.keepLogging;
    showOnce = nprocess.showOnce;
}
process::process(const process &nprocess)
{
    pid = nprocess.pid;
    pname = nprocess.pname;
    fpath = nprocess.fpath;
    fname = nprocess.fname;
    search = nprocess.search;
    terminalOutput = nprocess.terminalOutput;
    logTimes = nprocess.logTimes;
    keepLogging = nprocess.keepLogging;
    showOnce = nprocess.showOnce;
}

void process::outputData()
{
    if(terminalOutput)
    {
#ifdef DEBUG
	print_string("Output is Terminal");
#endif
	std::string formattedVal = format_message(pinfo, outputSeparatorTerminal);
	print_string(pname+"."+std::to_string(pid) + ":\t" + formattedVal);
    } else {
#ifdef DEBUG
	print_string("Output is File");
#endif
	if(!outputFile.is_open())
	{
	    /* The headers for the outputs are already created. Simply put them in
	     * the same order here as they are in format_output under print.h/cpp.
	     * Note that, similar to within format_output, cpu usage is a
	     * calculated value and is therefore not a predefined header.
	     */
	    static const std::string logHeader =
		headers[cpu_rss] + (terminalOutput ? outputSeparatorTerminal:outputSeparatorFile) +
		"cpu_usage";

	    std::string outfname = fpath + fname;
	    outputFile.open(outfname);
	    outputFile << logHeader << std::endl;
	}
	outputFile << format_message(pinfo, outputSeparatorFile) << std::endl;
    }
}

void process::set_pinfo(const procinfo npinfo) {
    for(int currIndex=0; currIndex<NUMVALUES; currIndex++)
    {
	pinfo.values[currIndex] = npinfo.values[currIndex];
    }
}

void process::set_pname(std::string npname)
{
    std::string temp = npname;
    if(npname.at(0) == '(')
    {
	//The pname, when read from the stat file, is formatted as: (pname)
	temp.erase(0,1);
	temp.erase(temp.size() - 1);
    }
    pname = temp;
}
