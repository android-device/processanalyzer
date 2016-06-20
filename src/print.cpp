#include "print.h"

//  Print message. Prepend with program name.
void print_string(const std::string message)
{
    if (message != "")
    {
	printf ("%s: %s\n", kpiProg, message);
    }
}

//  Format message for printing, then print it.
void format_message (const std::string rawData)
{
}

void openFile(const std::string  fname)
{
}

void openFile(const std::string  fname, const std::string path)
{
    openFile(fname);
}

void closeFile()
{
}
