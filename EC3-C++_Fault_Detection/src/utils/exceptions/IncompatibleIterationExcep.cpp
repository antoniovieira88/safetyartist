#include "include/IncompatibleIterationExcep.h"
#include <string>
using namespace std;

IncompatibleIterationExcep::IncompatibleIterationExcep(int iterationMetrics, int iterationData)
{
	string iterationMetricsStr = to_string(iterationMetrics);
	string iterationDataStr = to_string(iterationData);
	errorMessage = "MetricIteration " + iterationMetricsStr + " is incompatible to current interation " + iterationDataStr;
}

const char* IncompatibleIterationExcep::what() const throw()
{
	return const_cast<char*>(errorMessage.c_str());
}
