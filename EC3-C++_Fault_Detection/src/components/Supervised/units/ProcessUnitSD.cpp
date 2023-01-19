#include "../include/ProcessUnitSD.h"

ProcessUnitSD::ProcessUnitSD(
	CorrectOutputGenerator& correctOutputGenerator,
	FailedOutputGenerator& failedOutputGenerator)
	:
	correctOutputGenerator(correctOutputGenerator),
	failedOutputGenerator(failedOutputGenerator),
	multipleFailureScenario({ 2.0, 3.0, 1.9, 2.1, 2.9, 3.1 }) // member added only for test purpose
{
	ProcessUnitSD::testInput = (double NAN);
	ProcessUnitSD::testOutput = (double NAN);
	ProcessUnitSD::keepPower = 0.0;
	ProcessUnitSD::stdDeviationTest = (double NAN);
	ProcessUnitSD::fail = false;
	ProcessUnitSD::failureScenario = nullptr;
}

void ProcessUnitSD::setFuseTestInput(double testInput)
{
	if (keepPower == 1.0) {
		if (fail) {
			failedOutputGenerator.setFailureScenario(failureScenario);
			testOutput = failedOutputGenerator.generateOutput(testInput);
			stdDeviationTest = failedOutputGenerator.getStdDeviation();
		}
		else {
			testOutput = correctOutputGenerator.generateOutput(testInput);
			stdDeviationTest = correctOutputGenerator.getStdDeviation();
		}
	}
}

void ProcessUnitSD::setFuseTestScenario(FuseTestScenarioType& testScenario)
{
	int numberOfFailedComponents = testScenario.numberOfFailedComponents;

	ProcessUnitSD::fail = (numberOfFailedComponents > 0);

	if (fail) {
		if (numberOfFailedComponents == 1) failureScenario = testScenario.failureScenarioPointer;
		else failureScenario = &multipleFailureScenario; // this solution is only temporary
	}
	else {
		failureScenario = nullptr;
	}
}

double ProcessUnitSD::getFuseTestOutput()
{
	return testOutput;
}

void ProcessUnitSD::setKeepPower(double keepPower)
{
	ProcessUnitSD::keepPower = keepPower;
}
