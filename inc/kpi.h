/* Header file specifying the functions used by the kpiAnalyzer
*/
#ifndef KPI
#define KPI

//strings and ints
#include <string>
#include <string.h>

#include <fstream>
#include "kpi_consts.h"
#include "print.h"
#include "file.h"

//finding folders
#include <unistd.h>

/* The function to find the specified process - returns false if the process
 * could not be found, indicating that it is not currently running.
 *
 * Searches using the pname or pid - specified using pname search
 *
 * If the -s parameter is given, this function is an ifinite loop! It will not
 * exit until a process with a matching PID is found.
 */
bool processSearch(bool search, std::string id, bool pnameSearch);

//get the process info, using the pid, and put it in a pinfo
//based on: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html
int get_proc_info(procinfo *pinfo, std::string pid);

static std::string procFile = "";

#endif
