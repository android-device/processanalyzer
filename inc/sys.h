/* Used to check whether a file exists
*/
#ifndef SYS
#define SYS
#include <string>
#include "print.h"
#include <unistd.h>

/* Checks whether the file is correctly available to the program and handles
 * any error messages. Does not open any files...
 * 
 * Returns:
 * 	0 not available
 * 	1 read only
 * 	2 read and write
 */
int checkFile(std::string filename);

/* Run a system command and get the output.
 *
 * This could be used for any system command, but it will mostly be used for
 * pidof when searching with pname instead of pid
 */
std::string exec(const char* cmd);

#endif
