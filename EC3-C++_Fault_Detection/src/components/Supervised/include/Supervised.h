#include "ProcessUnitSD.h"

class Supervised {
public:
	Supervised(double nominalFuseResultBurn, double nominalFuseResultNotBurn, int seed);
	void setTestInput(double input);
	void setTestScenario(TestScenarioType& testScenario);
	double getTestOutput();

private:
	mt19937 generator;

	CorrectOutputGenerator correctOutputGenerator;
	FailedOutputGenerator failedOutputGenerator;
	ProcessUnitSD processUnit;

};