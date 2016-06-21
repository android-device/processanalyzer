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
    bool search = false; //default is to quit immediately if process is not found
    bool terminalOutput = true; //default is to output to file


    //process identifiers
    std::string pid = "";
    std::string pname = "";

    //log file information
    std::string fpath = "/tmp"; //default location is /tmp
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
			pid = argv[i+1];
#ifdef DEBUG
			print_string("PID Set: " + pid);
#endif
			break;

		    case 'n': //process name, which will be used to find the pid
			pname = argv[i+1];
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
    if (!processSearch(search, pid)) //process not found
    {
	print_string("Process not found");
	return 1;
    }
    if(pid == "")
    {
	print_string("Process not found");
	return 1;
    }

    //TODO: implement quit on state change
#ifdef DEBUG
    print_string("Gathering Data");
#endif
    fflush(stdout);

    procinfo pinfo;
    bool keepLogging = true;
    while (keepLogging)
    {
	switch(get_proc_info(&pinfo, pid))
	{
	    case -3: //error condition
		print_string("Not all pinfo values filled");
		break;
	    case -2: //error condition
		print_string("Extraneous values, some not read");
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
	if(pinfo.state == "D") //D for DEAD
	{
	    keepLogging = false;
	}
	outputData(pinfo);
	sleep (1);
    }
    return 0;
}
