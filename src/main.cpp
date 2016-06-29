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

/* Main Function. Expects file name as argument. */
int main(int argc, char *argv[])
{
    bool paused = false;
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
     * anything else: show help */
    for(int i=0; i<argc; i++)
    {
	if(argv[i][0]=='-') //denotes a new process
	{
	    /* Each process' parameters are grouped, such as:
	     * -inco <pid> <pname> <count> */
	    process currProcess; //to put into vector
	    int skipParams = 0;
	    for(int currParam = 1; currParam < strlen(argv[i]); currParam++)
	    {
		switch(argv[i][currParam])
		{
		    case 'p': //file path parameter
			currProcess.set_fpath(argv[i+skipParams+1]);
			skipParams++; //path is separate param
#ifdef DEBUG
			print_string("p");
			print_string(currProcess.get_fpath());
#endif
			break;

		    case 'f': //file name parameter
			currProcess.set_fname(argv[i+skipParams+1]);
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
			currProcess.set_pid(std::stoi(argv[i+skipParams+1]));
			skipParams++; //pid is separate
#ifdef DEBUG
			print_string("i");
			print_string(std::to_string(currProcess.get_pid()));
#endif
			break;

		    case 'n': //process name, which will be used to find the pid
			currProcess.set_pname(argv[i+skipParams+1]);
			skipParams++; //pname is separate
#ifdef DEBUG
			print_string("n");
			print_string(currProcess.get_pname());
#endif
			break;

		    case 'c':
			currProcess.set_logTimes(std::stoi(argv[i+skipParams+1]));
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
	    processes.push_back(currProcess);
	}
    }

    /* Find every available process, quits if any passed processes do not
     * exist. This has the potential to be an inifite loop, because of the use
     * of process search - any processes that are being 'searched' for that
     * never come into existence will stop the execution of the rest of the
     * program - until they ALL exist. */
    for(std::vector<process>::iterator currProcess=processes.begin(); currProcess!=processes.end();)
    {
	bool erase=false;
	if(processSearch(*currProcess)) { //process found (searches with pname OR pid based on which is set)
	    currProcess->set_running();
	} else { //process not found
	    if(!currProcess->get_search()) //should already be executing, don't search
	    {
		//TODO remove bad processes instead of quitting
		print_string(currProcess->get_pid() + ":" + currProcess->get_pname() + " not found, not searching");
		erase = true;
	    }
	}
	if(currProcess->get_logTimes() < 0) //negative numbers make no sense
	{
	    currProcess->set_logTimes(0);
	    if(!currProcess->get_keepLogging()) //logging is messed up
	    {
		print_string(currProcess->get_pid() + ":" + currProcess->get_pname() + " Logging error");
		return 1;
	    }
	}

	if(erase) {
	    currProcess=processes.erase(currProcess);
	} else {
	    ++currProcess;
	}
    }

    int currLogTime = 0; //increased once after iterating through every process
    while(!(processes.size() == 0)) //loop until every process finishes
    {
	if(!paused) //user pauses by pressing enter -- application must be in foreground for this to work!
	{
	    for(std::vector<process>::iterator currProcess=processes.begin(); currProcess!=processes.end();)
	    {
		bool erase = false;
#ifdef DEBUG
		print_string("currProcess is: " + std::to_string(currProcess->get_pid()) + ":" + currProcess->get_pname());
#endif
		fflush(stdout);

		/* If:
		 * 	Haven't reached log limit OR is set to log indefinitely
		 * 	AND is running
		 *
		 * 	Do nothing if the process is not running, regardless of the
		 * 	first two conditions - no point! */
		if(currProcess->is_running())
		{
		    if(currProcess->get_keepLogging()) { //log indefinitely
			getAndShow(*currProcess);
		    } else if(currLogTime < currProcess->get_logTimes()) {
			getAndShow(*currProcess);
		    } else if(currLogTime == currProcess->get_logTimes()) { //not log indefinitely and log times exceeded
			//TODO remove finished processes from list.
			erase = true;
			currProcess->clear_running();
		    }
		} else { //not running
		    if(currProcess->get_search()) //keep searching for it
		    {
			if(currProcess->get_keepLogging()) //log indefinitely
			{
			    if(processSearch(*currProcess)) {
				currProcess->set_running();
			    }
			} else { //if don't log indefinitely
			    if(currLogTime < currProcess->get_logTimes()) //if not done logging
			    {
				if(processSearch(*currProcess)) {
				    currProcess->set_running();
				} else { //look again next time
				    /* not running YET, don't want to affect the number of
				     * times to log it. If the process stops partway through
				     * the number of times to log, it will resume logging if it
				     * is found again.
				     *
				     * If the log limit is reached, incrementing this will have
				     * no effect - as the log limit and current execution
				     * increase at the same rate (max of once per iteration).
				     *
				     * NOTE potential to overflow */
				    currProcess->increment_logTimes();
				    currProcess->clear_running();
				}
			    }
			} //end if(keepLogging)
		    } //end if(search)
		} //end if(running)

		if(erase) {
		    currProcess = processes.erase(currProcess);
		} else {
		    ++currProcess;
		}
	    } //end vector iterator (for)
	    currLogTime++;
	} //end paused
#ifdef DEBUG
	    print_string("Log Time: " + std::to_string(currLogTime));
#endif
	    sleep(1);
    } //end log loop (while)
    return 0;
}
