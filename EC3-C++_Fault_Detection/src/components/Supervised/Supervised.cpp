#include "include/Supervised.h"

Supervised::Supervised(
	double uncertaintyRangeInput,
	bool verboseMode) :
	generator(),
	correctOutputGenerator(uncertaintyRangeInput, generator),
	failedOutputGenerator(uncertaintyRangeInput, generator),
	processUnit(correctOutputGenerator, failedOutputGenerator)
{
	Supervised::verboseMode = verboseMode;
}

Supervised::Supervised(
	double nominalFuseResultBurn,
	double nominalFuseResultNotBurn,
	double uncertaintyRangeInput,
	bool verboseMode) :
	generator(),
	correctOutputGenerator(
		nominalFuseResultBurn, nominalFuseResultNotBurn,
		uncertaintyRangeInput, generator),
	failedOutputGenerator(uncertaintyRangeInput, generator),
	processUnit(correctOutputGenerator, failedOutputGenerator)
{
	Supervised::verboseMode = verboseMode;
}

void Supervised::setBasicParams(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn,
	double maxStdDeviation,
	unsigned int seed)
{
	correctOutputGenerator.setBasicParams(
		nominalValueFuseResultBurn,
		nominalValueFuseResultNotBurn,
		minNominalFuseResultBurn,
		maxNominalFuseResultBurn,
		minNominalFuseResultNotBurn,
		maxNominalFuseResultNotBurn,
		maxStdDeviation);

	failedOutputGenerator.setMaxStdDeviation(maxStdDeviation);

	generator.seed(seed);
}

/* ---------------------------------------------------------------------------------------- */
/* FUSE_TEST methods */
void Supervised::setFuseTestScenario(FuseTestScenarioType& testScenario)
{
	processUnit.setFuseTestScenario(testScenario);
}

void Supervised::setFuseTest(double fuseTest)
{
	processUnit.setFuseTest(fuseTest);
}

double Supervised::runFuseTest()
{
	return processUnit.runFuseTest();
}

vector<double> Supervised::getNominalFuseResults()
{
	return correctOutputGenerator.getNominalFuseResults();
}

/* ---------------------------------------------------------------------------------------- */
/* KEEP_POWER_TEST methods */
void Supervised::setKeepPowTestScenario(bool fail)
{
	processUnit.setKeepPowTestScenario(fail);
}

void Supervised::setKeepPower(double keepPower)
{
	processUnit.setKeepPower(keepPower);
}

double Supervised::runKeepPowTest()
{
	return processUnit.runKeepPowTest();
}

/* ---------------------------------------------------------------------------------------- */
/* MT_ENGINE methods */
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