#include "print.h"
#define DEBUG

void outputData(procinfo pinfo)
{
    std::string formattedVal = format_message(pinfo);
    print_string(formattedVal);
}

void outputData(procinfo pinfo, std::string outputFileName, std::ofstream *outputFile)
{
    if(*outputFile.is_open()) {
#ifdef DEBUG
	print_string("File is open");
#endif
    } else {
#ifdef DEBUG
	print_string("File is not open");
#endif
	*outputFile.open(outputFileName);
#ifdef DEBUG
	if(*outputFile.is_open()) {
	    print_string("File is open");
	} else {
	    print_string("File is not open");
	}
#endif
    }
}

// Print message. Prepend with program name.
void print_string(std::string message)
{
    if (message != "")
    {
	printf("%s: %s\n", kpiProg.c_str(), message.c_str());
    }
}

//  Format message for printing, then print it.
std::string format_message (procinfo pinfo)
{
    std::string formattedVal = "";
    formattedVal += pinfo.state + ',' +
	pinfo.exName + ',' +
	pinfo.utime + ',' +
	pinfo.stime + ',' +
	pinfo.cutime + ',' +
	pinfo.cstime + ',' +
	pinfo.priority + ',' +
	pinfo.vsize + ',' +
	pinfo.rss + ',' +
	pinfo.rlim + ',' +
	pinfo.starttime;
    return formattedVal;
}

void openFile(const std::string  fname, const std::string path)
{
}

void closeFile()
{
}
