/* Header file specifying the functions used by the kpiAnalyzer
*/
#ifndef KPI
#define KPI

//strings and ints
#include <string>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>

#include <fstream>
#include "kpi_consts.h"
#include "print.h"
//finding folders
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* The function to find the specified process - returns false if the process
 * could not be found, indicating that it is not currently running.
 *
 * Searches using the pname or pid - preference is given to the pid
 */
bool processSearch(bool search, std::string pid);

//get the process info, using the pid, and put it in a pinfo
//based on: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html
int get_proc_info(procinfo *pinfo, std::string pid);

static std::string procFile = "";

#endif