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
#include "sys.h"
#include "process.h"

//finding folders
#include <unistd.h>

/* The function to find the specified process - returns false if the process
 * could not be found, indicating that it is not currently running.
 *
 * Finds a process using either the pname or pid. Main passes only the process
 * object, without caring which is used.
 *
 * If the -s parameter is given, this function is an ifinite loop! It will not
 * exit until a process with a matching PID is found.
 *
 * The specific functions to search should never be accessed outside kpi.cpp
 *
 * Becaues pname search calls an external application (pidof), pid search is
 * preferred.
 */
//bool processSearch(bool search, int id);
//bool processSearch(bool search, std::string pname, int *pid);
bool processSearch(process &currProcess);

//get the process info, using the pid, and put it in a pinfo
//based on: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html
int get_proc_info(procinfo *pinfo, int pid);

static std::string procFile = "";

#endif
