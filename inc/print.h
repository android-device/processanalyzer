/* Functions for anything that shows info to the user, including outputing to files
 */

#include <cstddef>
#include "kpi_consts.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <unistd.h>

/* Formats the message for printing - is called by the print function
 */
std::string format_message(procinfo pinfo, std::string outputSeparator);

/* Prints the formatted message to the console
 */
void print_string(const std::string message);

/* Writes the formatted message to a file
 */
void write_string(const std::string message);

/* Using the utime, stime, cutime, and sutime, the actual cpu load is
 * calculated as a percent.
 */
std::string get_cpuLoad(procinfo pinfo);

/* Used to round the cpu usage to two significant figures */
std::string roundVal(double d);
