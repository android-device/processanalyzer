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
    std::string outputSeparator = ",\t"; //TEMPORARY
    std::string formattedVal = "";
    formattedVal += pinfo.state + outputSeparator +
	//pinfo.exName + "," +
	pinfo.utime + outputSeparator +
	pinfo.stime + outputSeparator +
	pinfo.cutime + outputSeparator +
	pinfo.cstime + outputSeparator +
	pinfo.priority + outputSeparator +
	pinfo.vsize + outputSeparator +
	pinfo.rss + outputSeparator +
	pinfo.rlim + outputSeparator +
	pinfo.starttime;
    return formattedVal;
}

void openFile(const std::string  fname, const std::string path)
{
}

void closeFile()
{
}
