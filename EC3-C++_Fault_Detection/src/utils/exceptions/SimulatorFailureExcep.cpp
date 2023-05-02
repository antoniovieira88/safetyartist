#include "include/SimulatorFailureExcep.h"
#include <iostream>

SimulatorFailureExcep::SimulatorFailureExcep(string reason, string where)
{
	SimulatorFailureExcep::errorMsg = "EC3_Fault_Detection Simulator failed.\nError: "
		+ reason + "\nWhere: " + where;

	std::cout << reason + where;
}

const char* SimulatorFailureExcep::what() const throw()
{
	return const_cast<char*>(errorMsg.c_str());
}
