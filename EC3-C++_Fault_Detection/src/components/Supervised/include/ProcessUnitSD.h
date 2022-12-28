#include "CorrectOutputGenerator.h"
#include "FailedOutputGenerator.h"

class ProcessUnitSD {
public:
	ProcessUnitSD(
		CorrectOutputGenerator& correctOutputGenerator,
		FailedOutputGenerator& failedOutputGenerator
	);
	void setTestInput(double input);
	void setTestScenario(TestScenarioType& testScenario);
	double getTestOutput();

private:
	double testInput, testOutput, stdDeviationTest;
	bool fail;

	FailureScenarioType* failureScenario;

	// member added only for test purpose
	FailureScenarioType multipleFailureScenario;

	CorrectOutputGenerator& correctOutputGenerator;
	FailedOutputGenerator& failedOutputGenerator;
};