#include "include/Supervised.h"

Supervised::Supervised()
{
	testInput = NAN;
	testOutput = NAN;
	stdDeviationTest = NAN;
	correctOutputGenerator = CorrectOutputGenerator(0.1, 0.9, 0.0, 0.3, 0.7, 1.0, 0.05, 0.001, 1);
}

void Supervised::setTestInput(double input)
{
	testInput = input;
	testOutput = correctOutputGenerator.generateOutput();
	stdDeviationTest = correctOutputGenerator.getStdDeviation();
}

void Supervised::setTestScenario()
{
}

double Supervised::getTestOutput()
{
	return testOutput;
}
