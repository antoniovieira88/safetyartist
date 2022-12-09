#include "include/Supervised.h"

Supervised::Supervised(): correctOutputGenerator(0.1, 0.9, 0.0, 0.3, 0.7, 1.0, 0.1, 0.01, 1)
{
	testInput = NAN;
	testOutput = NAN;
	stdDeviationTest = NAN;
}

void Supervised::setTestInput(double input)
{
	testInput = input;
	testOutput = correctOutputGenerator.generateOutput(testInput);
	stdDeviationTest = correctOutputGenerator.getStdDeviation();
}

void Supervised::setTestScenario()
{
}

double Supervised::getTestOutput()
{
	return testOutput;
}
