#include "include/Supervised.h"

Supervised::Supervised(
	double nominalFuseResultBurn,
	double nominalFuseResultNotBurn,
	bool verboseMode) :
	generator(),
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

void Supervised::setBasicParams(
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn,
	int seed)
{
	correctOutputGenerator.setBasicParams(
		minNominalFuseResultBurn,
		maxNominalFuseResultBurn,
		minNominalFuseResultNotBurn,
		maxNominalFuseResultNotBurn);

	generator.seed(seed);

	if (seed >= 0) generator.seed(seed);
	else generator.setRandSeed();
}

void Supervised::loadMtEngineState()
{
	generator.loadState(verboseMode);
}

void Supervised::saveMtEngineState()
{
	generator.saveState(verboseMode);
}

void Supervised::setMtEngineSrcFile(string srcFileDir)
{
	generator.setFileDir(srcFileDir);
}

void Supervised::setMtEngineRandSeed()
{
	generator.setRandSeed();
}
