#include "include/FailureDetectedExcep.h"

FailureDetectedExcep::FailureDetectedExcep(FaultDiagnosisType faultDiagnosis)
{
	failureIndicators = faultDiagnosis.failureIndicators;
	perfomedTest = faultDiagnosis.perfomedTest;
	errorMsg = "-> Failure detected by supervisor ";
	if (perfomedTest == fuseTest) {
		errorMsg = errorMsg + " in Fuse Test. Keep power set off to ensure safety\n";
	}
	else {
		errorMsg = errorMsg + " in Keep Power Test. Fuse Test set off to ensure safety\n";
	}
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

string FailureDetectedExcep::getPerfomedTestName()
{
	return testStr[perfomedTest];
}

void FailureDetectedExcep::buildLogError()
{
	logError = "";
	for (FailureMetricIndicatorType& failureIndicator : failureIndicators) {

		logError = logError +
			to_string(failureIndicator.iteration) + "," +
			testStr[perfomedTest] + "," +
			metricStr[failureIndicator.metric] + "," +
			to_string(failureIndicator.tolerance) + "," +
			to_string(failureIndicator.variation) + "\n";
	}
}


const char* FailureDetectedExcep::what() const throw()
{
	return const_cast<char*>(errorMsg.c_str());
}

