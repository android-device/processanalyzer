#include "print.h"
//#define DEBUG

// Print message. Prepend with program name.
void print_string(std::string message)
{
    printf("%s: %s\n", kpiProg.c_str(), message.c_str());
}

/* Format message for printing, then print it. To add or remove values from the
 * output, add or remove them here. The available values can be found under the
 * pinfoval enum in kpi_consts.h
 * 
 * The exception is CPU usage. Because that has to be calculated using utime,
 * stime, cutime, and cstime, it cannot simply be added - use the
 * get_cpuLoad(pinfo) function made available in print.h/cpp */
std::string format_message (procinfo pinfo, std::string outputSeparator)
{
    std::string formattedVal = "";
    formattedVal +=
	pinfo.values[cpu_rss] + outputSeparator +
	get_cpuLoad(pinfo);
    return formattedVal;
}

/* Refer to:
 * http://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat */
std::string get_cpuLoad(procinfo pinfo)
{
    std::ifstream uptimeFile(uptimeFname.c_str());
    int uptime = 0;
    std::string temp = "";
    uptimeFile >> temp; //ignore the first value...
    uptime = std::stoi(temp);

#ifdef DEBUG
    print_string(pinfo.values[cpu_utime]);
    print_string(pinfo.values[cpu_stime]);
#endif
    double totalTime = std::stoi(pinfo.values[cpu_utime]) + std::stoi(pinfo.values[cpu_stime]);
    double ctotalTime = totalTime + std::stoi(pinfo.values[cpu_cutime]) + std::stoi(pinfo.values[cpu_cstime]);

    double totalTime_seconds = uptime - (std::stoi(pinfo.values[cpu_starttime]) / sysconf(_SC_CLK_TCK));
    double cpuUsage = 100 * ((ctotalTime / sysconf(_SC_CLK_TCK)) / totalTime_seconds);

    temp = roundVal(cpuUsage) + "%";

#ifdef DEBUG
    print_string("CPU totalTime: " + std::to_string(totalTime));
    print_string("CPU ctotalTime: " + std::to_string(ctotalTime));
    print_string("CPU totalTime_seconds: " + std::to_string(totalTime_seconds));
    print_string("CPU cpuUsage: " + std::to_string(cpuUsage));
    print_string("CPU cpuUsage: " + temp);
#endif

    return temp;
}

std::string roundVal(double d)
{
    std::string temp = std::to_string(d);
    std::size_t pos = temp.find('.');
    temp = temp.substr(0,pos+3);
    return temp;
}
