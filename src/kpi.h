/* Header file specifying the functions used by the kpiAnalyzer
 */
#ifndef KPI
#define KPI

/* The function to find the specified process - returns false if the process
 * could not be found, indicating that it is not currently running.
 *
 * Parameters:
 * 	processName
 * 	search, which specifies whether to continue searching for the process
 * 		until it exists or quit immediately
 */
bool analyzerOpen(const char *processName, bool search);

void analyzerPoll();

bool executionState();

#endif
