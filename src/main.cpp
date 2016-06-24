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
	   ) 
	{
	    print_string("Process not found");
	    return 1;
	}

	if(currProcess->get_pid() == 0) //this should not be possible...
	{
	    print_string("Process not found");
	    return 1;
	}

#ifdef DEBUG
	print_string("Gathering Data");
#endif
	fflush(stdout);

	procinfo pinfo;

	//loop until logtimes is up, or keeploogging stops.
	for(int currLogTime = 0; (currLogTime < currProcess->get_logTimes()) || currProcess->get_keepLogging(); currLogTime++)
	{
	    if(currProcess->get_logTimes()< 0) //negative numbers make no sense
	    {
		currProcess->set_logTimes(0);
	    }
	    switch(get_proc_info(&pinfo, currProcess->get_pid()))
	    {
#ifdef DEBUG
		case -3: //error condition
		    //TODO error handling
		    print_string("Not all pinfo values filled");
		    break;
		case -2: //error condition
		    print_string("Extraneous values, some not read");
		    break;
#endif
		case -1: //error condition
		    currProcess->set_keepLogging();
		    print_string("Error while opening stat file");
		    break;
		case 0: //do nothing
		    break;
		default:
		    currProcess->set_keepLogging();
		    print_string("Unkown exit condition");
		    break;
	    }

	    if(currProcess->get_fname() == "") //use the pid
	    {
		if(currProcess->get_pname() == "") //set the pname for the log file.
		{
		    currProcess->set_pname(pinfo.values[cpu_comm]);
		    if(currProcess->get_terminalOutput()) { print_string("pname is: " + currProcess->get_pname()); }
		}
		if(!currProcess->get_terminalOutput()) //don't care about the log file if not logging....
		{
		    currProcess->set_fname(currProcess->get_pname()+ "." + pinfo.values[cpu_pid] + ".log");
		}
	    }

	    //only show logname once, and only if outputting to a log
	    if(currProcess->get_showOnce() && !currProcess->get_terminalOutput())
	    {
		print_string("Log File: " + currProcess->get_fpath() + currProcess->get_fname());
	    }

	    if(pinfo.values[cpu_state] == "D") //D for DEAD
	    {
		currProcess->set_keepLogging();
	    }

	    /* The headers for the outputs are already created. Simply put them in
	     * the same order here as they are in format_output under print.h/cpp.
	     * Note that, similar to within format_output, cpu usage is a
	     * calculated value and is therefore not a predefined header.
	     */
	    std::string logHeader =
		pinfo.headers[cpu_rss] + (currProcess->get_terminalOutput() ? outputSeparatorTerminal:outputSeparatorFile) +
		"cpu_usage";

	    currProcess->set_showOnce();
	}
	currProcess->outputData();
    }
    return 0;
}
