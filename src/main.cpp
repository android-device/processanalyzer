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
#include "poll.h"

static char *canProg = NULL;              //  Pointer to program name
static char *canDev  = NULL;              //  Pointer to device or file name.

//  Print message. Prepend with program name.
void can_print_string (const char *s)
{
    if (s != NULL)
    {
	printf ("%s: %s\n", canProg, s);
    }
}

//  Format message for printing, then print it.
void kpiAnalyzer_print_message (const char *format, ... )
{
    va_list     list;
    char        *myBuf = NULL;

    myBuf = (char *) malloc (MAX_PRT_BUF);
    if (myBuf != NULL)
    {
	va_start  (list, format);
	vsnprintf (myBuf, MAX_PRT_BUF, format, list);
	va_end (list);

	kpiAnalyzer_print_string (myBuf);
	free (myBuf);
    }
}

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
	kpiAnalyzerPoll ();
	sleep (1);
    }
    return 0;
}
