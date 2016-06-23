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
    formattedVal += pinfo.values[state] + outputSeparator +
	//pinfo.values[exName] + "," +
	pinfo.values[utime] + outputSeparator +
	pinfo.values[cpu_stime] + outputSeparator +
	pinfo.values[cutime] + outputSeparator +
	pinfo.values[cstime] + outputSeparator +
	pinfo.values[priority] + outputSeparator +
	pinfo.values[vsize] + outputSeparator +
	pinfo.values[rss] + outputSeparator +
	pinfo.values[rlim] + outputSeparator +
	pinfo.values[starttime];
    return formattedVal;
}

std::string get_cpuLoad(procinfo pinfo)
{
    ifstream uptimeFile(uptimeFname.c_str());
    int uptime = 0;
    std::string temp = "";
    std::string temp << uptimeFile; //ignore the first value...
    temp = "";
    temp << uptimeFile;
    uptime = std::stoi(temp);

    int totalTime = std::stoi(pinfo.utime) + std::stoi(pinfo.stime);
    int ctotalTime = totalTime + std::stoi(pinfo.cutime) + std::stoi(pinfo.cstime);

    double totalTime_seconds = uptime - (std::stoi(pinfo.starttime) / CPUSPEED);
    double cpuUsage = 100 * ((totalTime / CPUSPEED) / totalTime_seconds);

    temp = std::to_string(totalTime_seconds) + outputSeparator + std::to_string(totalTime);
    return temp;
}
