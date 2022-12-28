#include "include/Supervised.h"

Supervised::Supervised(double nominalFuseResultBurn, double nominalFuseResultNotBurn, int seed) :
	generator(seed),
	correctOutputGenerator(
		nominalFuseResultBurn, nominalFuseResultNotBurn,
		0.0, 0.2, 0.8, 1.0,
		0.1, 0.001, generator),
	failedOutputGenerator(0.1, 0.001, generator),
	processUnit(correctOutputGenerator, failedOutputGenerator)
{
}

void Supervised::setTestInput(double input)
{
	processUnit.setTestInput(input);
}

void Supervised::setTestScenario(TestScenarioType& testScenario)
{
	processUnit.setTestScenario(testScenario);
}

double Supervised::getTestOutput()
{
	return processUnit.getTestOutput();
}
