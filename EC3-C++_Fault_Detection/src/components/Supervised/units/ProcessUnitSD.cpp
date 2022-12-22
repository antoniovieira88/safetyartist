#include "../include/ProcessUnitSD.h"

ProcessUnitSD::ProcessUnitSD(
	CorrectOutputGenerator& correctOutputGenerator,
	FailedOutputGenerator& failedOutputGenerator)
	:
	correctOutputGenerator(correctOutputGenerator),
	failedOutputGenerator(failedOutputGenerator)
{
	ProcessUnitSD::testInput = (double NAN);
	ProcessUnitSD::testOutput = (double NAN);
	ProcessUnitSD::stdDeviationTest = (double NAN);
	ProcessUnitSD::fail = false;
	ProcessUnitSD::failureScenario = {};
}

void ProcessUnitSD::setTestInput(double testInput)
{
	if (fail) {
		failedOutputGenerator.setFailureScenario(failureScenario);
		failedOutputGenerator.generateOutput(testInput);
	}
	else {
		testOutput = correctOutputGenerator.generateOutput(testInput);
		stdDeviationTest = correctOutputGenerator.getStdDeviation();
	}
}

void ProcessUnitSD::setTestScenario(bool fail)
{
	ProcessUnitSD::fail = fail;
	failureScenario = { 1.0, 2.0, 0.9, 1.1, 1.9, 2.1 };
}

double ProcessUnitSD::getTestOutput()
{
	return testOutput;
}