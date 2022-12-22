#include "ProcessUnitSD.h"

class Supervised {
public:
	Supervised(int seed);
	void setTestInput(double input);
	void setTestScenario(bool fail);
	double getTestOutput();

private:
	mt19937 generator;

	CorrectOutputGenerator correctOutputGenerator;
	FailedOutputGenerator failedOutputGenerator;
	ProcessUnitSD processUnit;

};