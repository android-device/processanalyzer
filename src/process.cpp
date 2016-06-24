#include "process.h"

void process::outputData()
{
    if(this.terminalOutput)
    {
	std::string formattedVal = format_message(pinfo, outputSeparatorTerminal);
	print_string(formattedVal);
    } else {
	this.outputFile << format_message(this.pinfo, outputSeparatorFile) << std::endl;
    }
}
