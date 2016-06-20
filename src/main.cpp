

/*
 ============================================================================
 Name        : main.cpp
 Author      :
 Version     :
 Copyright   :
 Description : Program polls the specified file (or device) for data.
 ============================================================================
 */

#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "unistd.h"
#include "fcntl.h"
#include "poll.h"

#define MAX_CAN_BUF   1000
#define MAX_PRT_BUF   1000

static char *canProg = NULL;              //  Pointer to program name
static char *canDev  = NULL;              //  Pointer to device or file name.

//  Data structure required by poll function.
static struct pollfd aPoll[0];

//  Print message. Prepend with program name.
void can_print_string (const char *s)
{
	if (s != NULL)
    {
        printf ("%s: %s\n", canProg, s);
    }
}

//  Format message for printing, then print it.
void can_print_message (const char *format, ... )
{
	va_list     list;
	char        *myBuf = NULL;

	myBuf = (char *) malloc (MAX_PRT_BUF);
    if (myBuf != NULL)
    {
        va_start  (list, format);
        vsnprintf (myBuf, MAX_PRT_BUF, format, list);
        va_end (list);

        can_print_string (myBuf);
        free (myBuf);
    }
}

//  Print Usage Message
int prtUsage ()
{
    can_print_message ("Usage: %s <file or device name>", canProg);
}

//  Open specified device or port.
int canOpen ()
{
	int fd = open(canDev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (!fd)
	{
		can_print_message ("Unable to open file %s. Aborting ...", canDev);
		return 1;
	}
	
	aPoll[0].fd = fd;
    aPoll[0].events = POLLIN;
    can_print_message ("Opened device %s", canDev);
    
    return 0;
}

//  Poll file (or device) for data
int canPoll ()
{
    int ret = poll(&aPoll[0], 1, 10);
    if (ret > 0)
    {		
        if (aPoll[0].revents & POLLIN)
        {
            char *myBuf = (char *) malloc(MAX_CAN_BUF);
            int readChars = read (aPoll[0].fd, myBuf, sizeof(myBuf));
            if (readChars > 0)
            {
				int count = readChars;
				while (readChars > 0)
				{
					readChars = read (aPoll[0].fd, myBuf+count, sizeof(myBuf));
					count += readChars;
				}
				*(myBuf+count) = '\0' ;
                can_print_message ("Received CAN message of length: %d", count);
				can_print_message ("Received message %s", myBuf);
            }
            free (myBuf);
        }
    }
    return 0;
}

//
//  Main Function. Expects file name as argument.
//
int main(int argc, char *argv[])
{
    canProg = argv[0];
    if (argc < 2)
    {
        prtUsage();
        return 1;
    }
    
    canDev  = argv[1];
    
	can_print_message ("Initializing ....");
    if (canOpen())
    {
        return 1;
    }
	
    can_print_message ("Entering wait loop. ctrl-c to abort ...");
    fflush(stdout);
    
    while (true)
    {
        canPoll ();
        sleep (1);
    }
	return 0;
}


