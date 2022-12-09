#include "include/FailureDetectedExcep.h"

FailureDetectedExcep::FailureDetectedExcep(faultDiagnosisType faultDiagnosis)
{
	failureIndicators = faultDiagnosis.failureIndicators;
	errorMessage = "Failure detected by supervisor\n";
	buildLogError();

}

vector<failureMetricIndicatorType> FailureDetectedExcep::getFailureIndicators()
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
	for (failureMetricIndicatorType& failureIndicator : failureIndicators) {

		logError = logError +
			to_string(failureIndicator.iteration) + ";" +
			metricStr[failureIndicator.metric] + ";" +
			to_string(failureIndicator.tolerance) + ";" +
			to_string(failureIndicator.variation) + "\n";
	}
}


const char* FailureDetectedExcep::what() const throw()
{
	return const_cast<char*>(errorMessage.c_str());
}

