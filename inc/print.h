/* Functions for anything that shows info to the user, including outputing to files
 */

#include <cstddef>
#include "kpi_consts.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iosfwd>

/* Formats the message for printing
 */
void outputData(procinfo pinfo);
void outputData(procinfo pinfo, std::ofstream *outputFile);

std::string format_message(procinfo pinfo);

/* Prints the formatted message using printf
 */
void print_string(const std::string message);

/* Writes the formatted message to a file
 */
void write_string(const std::string message);

//TODO: Implement custom path
/* Functions for handling the file creation. If the user has specified a path,
 * that is handled here.
 */
