#include <string>
#include <vector>
#include "../../structs/structs.h"

using namespace std;

class FailureDetectedExcep : public exception {
private:
	vector<FailureMetricIndicatorType> failureIndicators;
	string errorMsg;
	string logError;
	test perfomedTest;

	void buildFailureLog();

public:
	FailureDetectedExcep(FaultDiagnosisType faultDiagnosis);
	vector<FailureMetricIndicatorType> getFailureIndicators();
	const char* what() const throw();
	string getFailureLog();
	string getPerfomedTestName();
};