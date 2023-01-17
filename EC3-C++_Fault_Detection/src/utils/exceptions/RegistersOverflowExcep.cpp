#include "include/RegistersOverflowExcep.h"
#include <string>
using namespace std;

RegistersOverflowExcep::RegistersOverflowExcep(int numberOfRegisters, int maxNumberOfRegisters)
{
	string numberOfRegistersStr = to_string(numberOfRegisters);
	string maxNumberOfRegistersStr = to_string(maxNumberOfRegisters);
	errorMsg = "Overflow in SupervisorUnit: the number of registers (" + numberOfRegistersStr + ") exceeded the maximum limit (" + maxNumberOfRegistersStr + ")";
}

const char* RegistersOverflowExcep::what() const throw()
{
	return const_cast<char*>(errorMsg.c_str());
}
