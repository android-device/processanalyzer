#include "sys.h"
#define DEBUG

int checkFile(std::string filename)
{
#ifdef DEBUG
    print_string("Inside!");
#endif
    if(access(filename.c_str(), F_OK) == -1) //error
    {
#ifdef DEBUG
    print_string("Read Error!");
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
	return 0;
    } else if(access(filename.c_str(), W_OK) == -1) { //read okay, check write
	std::string errMsg = "";
	switch(errno)
	{
	    case EACCES:
		errMsg=filename + " write access denied";
		break;
	    case ELOOP:
		errMsg=filename + " write too many simlinks";
		break;
	    case ENAMETOOLONG:
		errMsg=filename + " write path too long";
		break;
	    case ENOENT:
		errMsg=filename + " write component of path doesn't exist";
		break;
	    case ENOTDIR:
		errMsg=filename + " write component of path isn't directory";
		break;
	    default:
		errMsg=filename + " write unknown error";
		break;
	}
	print_string(errMsg);
	return 1; //1 means read only
    } else { //read AND write
#ifdef DEBUG
    print_string(filename + ", r/w");
#endif
	return 2;
    }
}

std::string exec(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
	if (fgets(buffer, 128, pipe.get()) != NULL)
	    result += buffer;
    }
    return result;
}
