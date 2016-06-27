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

    //at least: <option> <name>
    if(argc <= 2)
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
#ifdef DEBUG
			print_string("p");
			print_string(currProcess.get_fpath());
#endif
			break;

		    case 'f': //file name parameter
			currProcess.set_fname(argv[i+currParam]);
			skipParams++; //fname is separate param
#ifdef DEBUG
			print_string("f");
			print_string(currProcess.get_fname());
#endif
			break;

		    case 's': //search parameter
			currProcess.set_search(true);
#ifdef DEBUG
			print_string("s");
#endif
			break;

		    case 'i': //given the pid!
			currProcess.set_pid(std::stoi(argv[i+currParam]));
			skipParams++; //pid is separate
#ifdef DEBUG
			print_string("i");
			print_string(std::to_string(currProcess.get_pid()));
#endif
			break;

		    case 'n': //process name, which will be used to find the pid
			currProcess.set_pname(argv[i+currParam]);
			skipParams++; //pname is separate
#ifdef DEBUG
			print_string("n");
			print_string(currProcess.get_pname());
#endif
			break;

		    case 'c':
			currProcess.set_logTimes(std::stoi(argv[i+currParam]));
			skipParams++; //count is separate
#ifdef DEBUG
			print_string("c");
			print_string(std::to_string(currProcess.get_logTimes()));
#endif
			break;

		    case 'o': //output to terminal instead of file - file name and path do nothing
			currProcess.set_terminalOutput();
#ifdef DEBUG
			print_string("o");
#endif
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

	    i += skipParams; //skip over separate params, which are for the just finished process
	    if(currProcess.get_logTimes() > 0) //has execution times, don't keep logging
	    {
		currProcess.clear_keepLogging();
	    }
#ifdef DEBUG
	    print_string("Pushing back process.");
#endif
	    processes.push_back(currProcess);
	}
    }

#ifdef DEBUG
    print_string("Searching for processes");
#endif
    for(std::vector<process>::iterator currProcess=processes.begin(); currProcess!=processes.end(); ++currProcess)
    {
	//TODO remove bad processes instead of quitting
	if(!processSearch(*currProcess)) //process not found (searches with pname OR pid based on which is set)
	{
	    print_string(currProcess->get_pid() + ":" + currProcess->get_pname() + " not found");
	    return 1;
	}
	if(currProcess->get_pid() == 0) //this should not be possible...
	{
	    print_string(currProcess->get_pid() + ":" + currProcess->get_pname() + " not found - failed to set PID");
	    return 1;
	}
	if(currProcess->get_logTimes()< 0) //negative numbers make no sense
	{
	    currProcess->set_logTimes(0);
	}
    }

    int currLogTime = 0; //increased once after iterating through every process
    int finishedProcesses = 0;
    bool finished = false;
    while(!finished)
    {
	for(std::vector<process>::iterator currProcess=processes.begin(); currProcess!=processes.end(); ++currProcess)
	{
#ifdef DEBUG
	    print_string("currProcess is: " + std::to_string(currProcess->get_pid()) + ":" + currProcess->get_pname());
#endif

#ifdef DEBUG
	    print_string("Gathering Data");
#endif
	    fflush(stdout);

	    procinfo pinfo;

	    //loop until logtimes is up, or keeploogging stops.
	    if((currLogTime < currProcess->get_logTimes()) || currProcess->get_keepLogging())
	    {
		switch(get_proc_info(&pinfo, currProcess->get_pid()))
		{
		    case -3: //error condition
			//TODO error handling
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
			currProcess->clear_keepLogging();
			print_string("Error while opening stat file");
			break;
		    case 0: //do nothing
			break;
		    default:
			currProcess->clear_keepLogging();
			print_string("Unkown exit condition");
			break;
		}

		currProcess->set_pinfo(pinfo);

		if(currProcess->get_fname() == "") //use the pid
		{
#ifdef DEBUG
		    print_string("Using PID");
#endif
		    if(currProcess->get_pname() == "") //set the pname for the log file.
		    {
#ifdef DEBUG
			print_string("Setting pname");
#endif
			currProcess->set_pname(pinfo.values[cpu_comm]);
			if(currProcess->get_terminalOutput())
			{
			    print_string(std::to_string(currProcess->get_pid()) + " pname is: " + currProcess->get_pname());
			}
		    }
		    if(!currProcess->get_terminalOutput()) //don't care about the log file if not logging....
		    {
#ifdef DEBUG
			print_string("Setting logname");
#endif
			currProcess->set_fname(currProcess->get_pname()+ "." + pinfo.values[cpu_pid] + ".log");
		    }
		}

		//only show logname once, and only if outputting to a log
		if(currProcess->get_showOnce() && !currProcess->get_terminalOutput())
		{
#ifdef DEBUG
		    print_string("Show Once, not terminalOutput");
#endif
		    print_string("Log File: " + currProcess->get_fpath() + currProcess->get_fname());
		}

		if(pinfo.values[cpu_state] == "D") //D for DEAD
		{
#ifdef DEBUG
		    print_string("DEAD");
#endif
		    currProcess->clear_keepLogging();
		}

#ifdef DEBUG
		print_string("Clearing show once");
#endif
		currProcess->clear_showOnce();
#ifdef DEBUG
		print_string("Outputting Data");
#endif
		currProcess->outputData();
	    } else { //process keepLogging is false and count is exceeded
		if(currLogTime == currProcess->get_logTimes()) { //only add once per process
		    finishedProcesses++;
		}
	    }
	}
	currLogTime++;
	//TODO remove finished processes from list.
	finished = (finishedProcesses == processes.size());
#ifdef DEBUG
	print_string("Log Time: " + std::to_string(currLogTime));
#endif
    }
    return 0;
}
