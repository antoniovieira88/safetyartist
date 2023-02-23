#include "include/ForcedSimulationEndExcep.h"

ForcedSimulationEndExcep::ForcedSimulationEndExcep(string reason, test testName)
{
	ForcedSimulationEndExcep::reason = "Simulation cycle end was brought on by " + reason + " in " + testStr[testName] + "\n";
}

const char* ForcedSimulationEndExcep::what() const throw()
{
	return const_cast<char*>(reason.c_str());
}