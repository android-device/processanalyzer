//  Print message. Prepend with program name.
void analyzer_print_string(const char *s)
{
    if (s != NULL)
    {
	printf ("%s: %s\n", canProg, s);
    }
}

//  Format message for printing, then print it.
void analyzer_format_message (const char *message)
