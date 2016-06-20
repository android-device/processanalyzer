/* Functions for anything that shows info to the user, including outputing to files
 */

#include <cstddef>
#include "kpi_consts.h"
#include "stdio.h"
#include <string>

/* Formats the message for printing
 */
void format_message(const std::string rawData);

/* Prints the formatted message using printf
 */
void print_string(const std::string message);

/* Writes the formatted message to a file
 */
void write_string(const std::string message);

//TODO: implement file output
/* Functions for handling the file creation. If the user has specified a path,
 * that is handled here.
 */
void openFile(const std::string fname);
//TODO: Implement custom path
void openFile(const std::string fname, const std::string path);
void closeFile();
