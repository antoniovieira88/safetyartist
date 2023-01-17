#include "include/FailureDetectedExcep.h"

FailureDetectedExcep::FailureDetectedExcep(faultDiagnosisType faultDiagnosis)
{
	failureIndicators = faultDiagnosis.failureIndicators;
	errorMsg = "-> Failure detected by supervisor\n";
	buildLogError();
}

vector<FailureMetricIndicatorType> FailureDetectedExcep::getFailureIndicators()
{
	return failureIndicators;
}

string FailureDetectedExcep::getLogError()
{
	return logError;
}

void FailureDetectedExcep::buildLogError()
{
	logError = "";
	for (FailureMetricIndicatorType& failureIndicator : failureIndicators) {

		logError = logError +
			to_string(failureIndicator.iteration) + "," +
			metricStr[failureIndicator.metric] + "," +
			to_string(failureIndicator.tolerance) + "," +
			to_string(failureIndicator.variation) + "\n";
	}
}


const char* FailureDetectedExcep::what() const throw()
{
	return const_cast<char*>(errorMsg.c_str());
}

