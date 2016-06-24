/*
   ============================================================================
Name        : main.cpp
Author      : Jose Rodrigo Sanchez Vicarte
Version     :
Copyright   :
Description : CPU and Memory Analyzer for KPI standards
============================================================================
*/

#include "stdlib.h"
#include "stdarg.h"
#include "unistd.h"
#include "fcntl.h"
#include <fstream>
#include <iosfwd>
#include <vector>

#include "kpi_consts.h"
#include "process.h"
#include "print.h"
#include "kpi.h"

//#define DEBUG

using namespace std;

//  Print Usage Message
int prtUsage ()
{
    print_string(helpMessage);
}

/* Main Function. Expects file name as argument.
*/
int main(int argc, char *argv[])
{
    std::vector<process> processes;

    if(argv[0] != NULL)
    {
	kpiProg = argv[0];
    }

    //check for process name
    if(argc < 2)
    {
	prtUsage();
	return 1;
    }

    /* Retreive Parameters.
     * Possible parameters:
     * i pId
     * n process Name
     * p file Path
     * f File name
     * s keep Searching
     * o Output to terminal
     * c number of times to log
     * h show Help
     * anything else: show help
     */
    for(int i=0; i<argc; i++)
    {
	if(argv[i][0]=='-') //is a parameter
	{
	    /* Each process' parameters are grouped, such as:
	     * -inco <pid> <pname> <count>
	     */
	    process currProcess; //to put into vector
	    int skipParams = 0;
	    for(int currParam = 1; currParam < strlen(argv[i]); currParam++)
	    {
		switch(argv[i][currParam])
		{
		    case 'p': //file path parameter
			currProcess.set_fpath(argv[i+currParam]);
			skipParams++; //path is separate param
			break;

		    case 'f': //file name parameter
			currProcess.set_fname(argv[i+currParam]);
			skipParams++; //fname is separate param
			break;

		    case 's': //search parameter
			currProcess.set_search(true);
			break;

		    case 'i': //given the pid!
			currProcess.set_pid(stoi(argv[i+currParam]));
			skipParams++; //pid is separate
			break;

		    case 'n': //process name, which will be used to find the pid
			currProcess.set_pname(argv[i+currParam]);
			skipParams++; //pname is separate
			break;

		    case 'c':
			currProcess.set_logTimes(stoi(argv[i+currParam]));
			skipParams++; //count is separate
			break;

		    case 'o': //output to terminal instead of file - file name and path do nothing
			currProcess.set_terminalOutput(true);
			break;

		    default: //includes help parameter...
			prtUsage();
			return 1;
		}
	    }

	    //neither pid nor name is set
	    if((currProcess.get_pid() == 0) && (currProcess.get_pname()==""))
	    {
		print_string("Check parameter number " + std::to_string(i));
		prtUsage();
		return 1;
	    }
	    
	    i += skipParams; //skip over separate params
	    processes.push_back(currProcess);
	}
    }

#ifdef DEBUG
    print_string("Searching for processes");
#endif

    for(std::vector<process>::iterator currProcess=processes.begin(); currProcess!=processes.end(); ++currProcess)
    {
	if ( //process not found (searches with pname OR pid based on which is set)
		processSearch(*currProcess)
		//((currProcess->pname!="") && (currProcess->pid==0)) ? !processSearch(currProcess->search, currProcess->pname, &currProcess->pid) : !processSearch(currProcess->search, currProcess->pid)
	   ) 
	{
	    print_string("Process not found");
	    return 1;
	}

	if(currProcess->pid == 0) //this should not be possible...
	{
	    print_string("Process not found");
	    return 1;
	}

#ifdef DEBUG
	print_string("Gathering Data");
#endif
	fflush(stdout);

	procinfo pinfo;
	for(int currLogTime = 0; (currLogTime < currProcess->logTimes) || currProcess->keepLogging; currLogTime++)
	{
	    if(currProcess->logTimes < 0) //negative numbers make no sense
	    {
		currProcess->logTimes = 0;
	    }
	    switch(get_proc_info(&pinfo, currProcess->pid))
	    {
		case -3: //error condition
#ifdef DEBUG
		    print_string("Not all pinfo values filled");
#endif
		    break;
		case -2: //error condition
#ifdef DEBUG
		    print_string("Extraneous values, some not read");
#endif
		    break;
		case -1: //error condition
		    currProcess->keepLogging = false;
		    print_string("Error while opening stat file");
		    break;
		case 0:
		    currProcess->keepLogging = true;
		    break;
		default:
		    currProcess->keepLogging = false;
		    print_string("Unkown exit condition");
		    break;
	    }

	    if(currProcess->fname == "") //using the pid
	    {
		if(currProcess->pname == "") //set the pname for the log file.
		{
		    currProcess->pname = pinfo.values[cpu_comm];
		    //The pname, when read from the stat file, is formatted as: (pname)
		    currProcess->pname.erase(0,1);
		    currProcess->pname.erase(currProcess->pname.size() - 1);
		    if(currProcess->terminalOutput) { print_string("pname is: " + currProcess->pname); }
		}
		if(!currProcess->terminalOutput) //don't care about the log file if not logging....
		{
		    currProcess->fname = currProcess->pname + "." + pinfo.values[cpu_pid] + ".log";
		}
	    }

	    //only show logname once, and only if outputting to a log
	    if(currProcess->showOnce && !currProcess->terminalOutput)
	    {
		print_string("Log File: " + currProcess->fpath + currProcess->fname);
	    }

	    if(pinfo.values[cpu_state] == "D") //D for DEAD
	    {
		currProcess->keepLogging = false;
	    }

	    /* The headers for the outputs are already created. Simply put them in
	     * the same order here as they are in format_output under print.h/cpp.
	     * Note that, similar to within format_output, cpu usage is a
	     * calculated value and is therefore not a predefined header.
	     */
	    std::string logHeader =
		pinfo.headers[cpu_rss] + (currProcess->terminalOutput ? outputSeparatorTerminal:outputSeparatorFile) +
		"cpu_usage";

	    if(currProcess->terminalOutput) {
		if(currProcess->showOnce) { print_string(logHeader); }
		outputData(pinfo);
	    } else {
		if(!currProcess->outputFile.is_open())
		{
		    std::string outfname = currProcess->fpath + currProcess->fname;
		    currProcess->outputFile.open(outfname);
		    currProcess->outputFile << logHeader << std::endl;
		}
		outputData(pinfo, &currProcess->outputFile);
	    }
	    currProcess->showOnce = false;
	}
	currProcess->outputFile.close();
    }
    return 0;
}
