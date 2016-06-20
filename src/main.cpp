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
			//TODO: Implement search feature
			//search = true;
			break;

		    case 'i': //given the pid!
			pid = argv[i+1];
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

    print_string("Searching for process");
    if (!processSearch()) //process not found
    {
	print_string("Process not found");
	return 1;
    }
    if(pid == "")
    {
	print_string("Process not found");
	return 1;
    }

    print_string("Logging " + pname + ", " + pid);

    //TODO: implement quit on state change
    print_string("Gathering Data");
    fflush(stdout);

    procinfo pinfo;
    bool keepLogging = true;
    while (true)
    {
	switch(get_proc_info(&pinfo))
	{
	    case -1: //error condition
		keepLogging = false;
		print_string("Error while reading pid info");
		break;
	    case 0:
		keepLogging = true;
		break;
	    default:
		keepLogging = false;
		print_string("Unkown exit condition");
		break;
	}
	outputData(pinfo);
	sleep (1);
    }
    return 0;
}
