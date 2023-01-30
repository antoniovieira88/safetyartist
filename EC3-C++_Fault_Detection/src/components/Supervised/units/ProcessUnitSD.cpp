#include "../include/ProcessUnitSD.h"

ProcessUnitSD::ProcessUnitSD(
	CorrectOutputGenerator& correctOutputGenerator,
	FailedOutputGenerator& failedOutputGenerator)
	:
	correctOutputGenerator(correctOutputGenerator),
	failedOutputGenerator(failedOutputGenerator),
	multipleFailureScenario({ 2.0, 3.0, 1.9, 2.1, 2.9, 3.1 }) // member added only for test purpose
{
	ProcessUnitSD::fuseTest = (double NAN);
	ProcessUnitSD::keepPower = 0;
	ProcessUnitSD::stdDeviationTest = (double NAN);
	ProcessUnitSD::fail = false;
	ProcessUnitSD::failureScenario = nullptr;
}

// the following method runs the fuseTest based on the current
// value of fuseTest, which must be by the 'setFuseTest' method
double ProcessUnitSD::runFuseTest()
{
	double fuseResult = (double NAN);
	if (keepPower == 1) {
		if (fail) {
			failedOutputGenerator.setFailureScenario(failureScenario);
			fuseResult = failedOutputGenerator.generateFuseTestOutput(fuseTest);
			stdDeviationTest = failedOutputGenerator.getStdDeviation();
		}
		else {
			fuseResult = correctOutputGenerator.generateFuseTestOutput(fuseTest);
			stdDeviationTest = correctOutputGenerator.getStdDeviation();
		}
	}

	return fuseResult;
}

void ProcessUnitSD::setTestScenario(TestScenarioType& testScenario)
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

void ProcessUnitSD::setFuseTest(double fuseTest)
{
	ProcessUnitSD::fuseTest = fuseTest;
}

int ProcessUnitSD::runKeepPowTest()
{
	int keepPowerReadback = (int NAN);
	stdDeviationTest = 0.0; // stdDeviation is set to zero since there is no random number generated for the output test
	if (fail) {
		failedOutputGenerator.setFailureScenario(failureScenario);
		keepPowerReadback = failedOutputGenerator.generateKeepPowTestOutput(keepPower);
	}
	else {
		keepPowerReadback = correctOutputGenerator.generateKeepPowTestOutput(keepPower);
	}

	return keepPowerReadback;
}

void ProcessUnitSD::setKeepPower(int keepPower)
{
	ProcessUnitSD::keepPower = keepPower;
}
