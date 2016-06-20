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
#include "stdio.h"
#include "stdarg.h"
#include "unistd.h"
#include "fcntl.h"
#include "kpi.h"

//  Print Usage Message
int prtUsage ()
{
    kpiAnalyzer_print_message ("Usage: %s <file or device name>", kpiAnalyzerProg);
}

//
//  Main Function. Expects file name as argument.
//
int main(int argc, char *argv[])
{
    kpiAnalyzerProg = argv[0];
    if (argc < 2)
    {
	prtUsage();
	return 1;
    }

    kpiAnalyzerDev  = argv[1];

    kpiAnalyzer_print_message ("Initializing ....");
    if (kpiAnalyzerOpen())
    {
	return 1;
    }

    kpiAnalyzer_print_message ("Entering wait loop. ctrl-c to abort ...");
    fflush(stdout);

    while (true)
    {
	kpiAnalyzerPoll();
	sleep (1);
    }
    return 0;
}
