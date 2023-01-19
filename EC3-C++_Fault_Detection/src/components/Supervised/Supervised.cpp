#include "include/Supervised.h"

Supervised::Supervised(
	double nominalFuseResultBurn,
	double nominalFuseResultNotBurn,
	bool verboseMode) :
	generator(),
	correctOutputGenerator(
		nominalFuseResultBurn, nominalFuseResultNotBurn,
		0.001, generator),
	failedOutputGenerator(0.001, generator),
	processUnit(correctOutputGenerator, failedOutputGenerator)
{
	Supervised::verboseMode = verboseMode;
}

void Supervised::setFuseTestInput(double input)
{
	processUnit.setFuseTestInput(input);
}

void Supervised::setFuseTestScenario(FuseTestScenarioType& testScenario)
{
	processUnit.setFuseTestScenario(testScenario);
}

double Supervised::getFuseTestOutput()
{
	return processUnit.getFuseTestOutput();
}

vector<double> Supervised::getNominalFuseResults()
{
	return correctOutputGenerator.getNominalFuseResults();
}

void Supervised::setBasicParams(
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn,
	double maxStdDeviation,
	unsigned int seed)
{
	correctOutputGenerator.setBasicParams(
		minNominalFuseResultBurn,
		maxNominalFuseResultBurn,
		minNominalFuseResultNotBurn,
		maxNominalFuseResultNotBurn,
		maxStdDeviation);

	failedOutputGenerator.setMaxStdDeviation(maxStdDeviation);

	generator.seed(seed);
}

void Supervised::loadMtEngineState()
{
	generator.loadState(verboseMode);
}

void Supervised::saveMtEngineState()
{
	generator.saveState(verboseMode);
}

void Supervised::setKeepPower(double keepPower)
{
	processUnit.setKeepPower(keepPower);
}

void Supervised::setMtEngineSrcFile(string srcFileDir)
{
	generator.setFileDir(srcFileDir);
}
