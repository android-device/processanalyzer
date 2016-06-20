/* Functions for anything that shows info to the user, including outputing to files
 */

/* Formats the message for printing
 */
void format_message(const char *rawData);

/* Prints the formatted message using printf
 */
void print_string(const char *message);

/* Writes the formatted message to a file
 */
void write_string(const char *message);

//TODO: implement file output
/* Functions for handling the file creation. If the user has specified a path,
 * that is handled here.
 */
void openFile(const char *fname);
//TODO: Implement custom path
void openFile(const char *fname, const char *path);
void closeFile();
