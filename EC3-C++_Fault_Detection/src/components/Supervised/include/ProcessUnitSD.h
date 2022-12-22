#include "CorrectOutputGenerator.h"
#include "FailedOutputGenerator.h"

class ProcessUnitSD {
public:
	ProcessUnitSD(
		CorrectOutputGenerator& correctOutputGenerator,
		FailedOutputGenerator& failedOutputGenerator
	);
	void setTestInput(double input);
	void setTestScenario(bool fail);
	double getTestOutput();

private:
	double testInput, testOutput, stdDeviationTest;
	bool fail;

	FailureScenarioType failureScenario;

	CorrectOutputGenerator& correctOutputGenerator;
	FailedOutputGenerator& failedOutputGenerator;
};