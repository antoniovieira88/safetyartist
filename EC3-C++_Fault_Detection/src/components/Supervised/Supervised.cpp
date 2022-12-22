#include "include/Supervised.h"

Supervised::Supervised(int seed) :
	generator(seed),
	correctOutputGenerator(0.1, 0.9, 0.0, 0.2, 0.8, 1.0, 0.1, 0.001, generator),
	failedOutputGenerator(0.1, 0.001, generator),
	processUnit(correctOutputGenerator, failedOutputGenerator)
{
}

void Supervised::setTestInput(double input)
{
	processUnit.setTestInput(input);
}

void Supervised::setTestScenario(bool fail)
{
	processUnit.setTestScenario(fail);
}

double Supervised::getTestOutput()
{
	return processUnit.getTestOutput();
}
