#include "include/AbortSimulationOpExcep.h"

AbortSimulationOpExcep::AbortSimulationOpExcep(string reason)
{
	AbortSimulationOpExcep::errorMsg = "Operation aborted. \nReason: " + reason;
}

const char* AbortSimulationOpExcep::what() const throw()
{
	return const_cast<char*>(errorMsg.c_str());
}
