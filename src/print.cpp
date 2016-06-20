#include "print.h"

//  Print message. Prepend with program name.
void print_string(const char *message)
{
    if (message != NULL)
    {
	printf ("%s: %s\n", canProg, message);
    }
}

//  Format message for printing, then print it.
void format_message (const char *rawData)
{
}

void openFile(const char* fname)
{
}

void openFile(const char* fname, const char *path)
{
    openFile(fname);
}

void closeFile()
{
}
