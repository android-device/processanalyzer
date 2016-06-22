#include "print.h"
//#define DEBUG

void outputData(procinfo pinfo)
{
    std::string formattedVal = format_message(pinfo);
    print_string(formattedVal);
}

void outputData(procinfo pinfo, std::ofstream *outputFile)
{
    *outputFile << format_message(pinfo) << std::endl;
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
	//pinfo.exName + ',' +
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
