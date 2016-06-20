/* Header file specifying the functions used by the kpiAnalyzer
*/
#ifndef KPI
#define KPI

/* The function to find the specified process - returns false if the process
 * could not be found, indicating that it is not currently running.
 *
 * Searches using the pname or pid - preference is given to the pid
 */
bool processSearch();

//get the process info, using the pid, and put it in a pinfo
int get_proc_info(procinfo *pinfo);

#endif
