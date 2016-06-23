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

#include "kpi_consts.h"
#include "print.h"
#include "kpi.h"

//#define DEBUG

using namespace std;

//  Print Usage Message
int prtUsage ()
{
    print_string(helpMessage);
}

//
//  Main Function. Expects file name as argument.
//
int main(int argc, char *argv[])
{
    std::ofstream outputFile;

    bool search = false; //default is to quit immediately if process is not found
    bool terminalOutput = false; //default is to output to file
    int logTimes = 0;

    //process identifiers
    int pid = 0;
    std::string pname = "";

    //log file information
    std::string fpath = "/tmp/"; //default location is /tmp
    std::string fname; //default file name is pname.log

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
	    if(strlen(argv[i]) == 2) //is correctly formatted, eg -n <name>
	    {
		switch(argv[i][1])
		{
		    case 'p': //file path parameter
			fpath = argv[i+1];
			break;

		    case 'f': //file name parameter
			fname = argv[i+1];
			break;

		    case 's': //search parameter
			search = true;
			break;

		    case 'i': //given the pid!
			pid = stoi(argv[i+1]);
#ifdef DEBUG
			print_string("PID Set: " + std::to_string(pid));
#endif
			break;

		    case 'n': //process name, which will be used to find the pid
			pname = argv[i+1];
			break;

		    case 'c':
			logTimes = stoi(argv[i+1]);
			break;

		    case 'o': //output to terminal instead of file - file name and path do nothing
			terminalOutput = true;
			break;

		    default: //includes help parameter...
			prtUsage();
			return 1;
		}
	    }
	    else //is not correctly formatted
	    {
		prtUsage();
		return 1;
	    }
	}
    }

#ifdef DEBUG
    print_string("Searching for process");
#endif

    if ( //process not found (searches with pname OR pid)
	    ((pname!="") && (pid==0)) ? !processSearch(search, pname, &pid) : !processSearch(search, pid)
	    ) 
    {
	print_string("Process not found");
	return 1;
    }

    if(pid == 0) //this should not be possible...
    {
	print_string("Process not found");
	return 1;
    }

#ifdef DEBUG
    print_string("Gathering Data");
#endif
    fflush(stdout);

    procinfo pinfo;
    if(logTimes < 0) //negative numbers make no sense
    {
	logTimes = 0;
    }
    bool keepLogging = (logTimes==0); //if logTimes is zero, keep logging until the process dies
    for(int currLogTime = 0; (currLogTime < logTimes) || keepLogging; currLogTime++)
    {
	switch(get_proc_info(&pinfo, pid))
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
		keepLogging = false;
		print_string("Error while opening stat file");
		break;
	    case 0:
		keepLogging = true;
		break;
	    default:
		keepLogging = false;
		print_string("Unkown exit condition");
		break;
	}

	if(fname == "")
	{
	    if(pname == "")
	    {
		pname = pinfo.values[cpu_comm];
		pname.erase(0,1);
		pname.erase(pname.size() - 1);
		print_string("pname is: " + pname);
	    }
	    if(!terminalOutput) //don't care about the log file if not logging....
	    {
		fname = pname + "." + pinfo.values[cpu_pid] + ".log";
		print_string("Log File: " + fpath + fname);
	    }
	}

	if(pinfo.values[cpu_state] == "D") //D for DEAD
	{
	    keepLogging = false;
	}
	//TODO: Implement custom path
	//log file information
	//std::string fpath = "/tmp"; //default location is /tmp
	//std::string fname; //default file name is pname.log
	if(terminalOutput) {
	    outputData(pinfo);
	} else {
	    if(!outputFile.is_open())
	    {
		std::string outfname = fpath + fname;
		outputFile.open(outfname);
		outputFile << logHeader << std::endl;
	    }
	    outputData(pinfo, &outputFile);
	}
	sleep (1);
    }
    outputFile.close();
    return 0;
}
