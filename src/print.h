/* Functions for anything that shows info to the user, including outputing to files
 */

/* Formats the message for printing
 */
void analyzer_format_message(const char *format);

/* Prints the formatted message using printf
 */
void analyzer_print_string(const char *s);

/* Writes the formatted message to a file
 */
void analyzer_write_string(const char *s);
