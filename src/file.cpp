#include "file.h"
#define DEBUG

bool checkFile(std::string filename)
{
#ifdef DEBUG
    print_string("Inside!");
#endif
    if(access(filename.c_str(), F_OK) == -1) //error
    {
#ifdef DEBUG
    print_string("Error!");
#endif
	std::string errMsg = "";
	switch(errno)
	{
	    case EACCES:
		errMsg=filename + " access denied";
		break;
	    case ELOOP:
		errMsg=filename + " too many simlinks";
		break;
	    case ENAMETOOLONG:
		errMsg=filename + " path too long";
		break;
	    case ENOENT:
		errMsg=filename + " component of path doesn't exist";
		break;
	    case ENOTDIR:
		errMsg=filename + " component of path isn't directory";
		break;
	    default:
		errMsg=filename + " unknown error";
		break;
	}
	print_string(errMsg);
#ifdef DEBUG
    print_string("Printing!");
#endif
	return false;
    } else {
#ifdef DEBUG
    print_string("no error!");
#endif
	return true;
    }
}
