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

// here are set the basic params which are specified in 'simulationsParams.csv'.
// since the values of keepPowerReadback are the same for all simulations, 
// there are not taken into account in this method. we can consider the params
// belows as constants for a given simulation
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

void Supervised::setTestScenario(TestScenarioType& testScenario)
{
	processUnit.setTestScenario(testScenario);
}

/* ---------------------------------------------------------------------------------------- */
/* FUSE_TEST methods */

void Supervised::setFuseTest(double fuseTest)
{
	processUnit.setFuseTest(fuseTest);
}

double Supervised::getFuseResult()
{
	return processUnit.runFuseTest();
}

vector<double> Supervised::getNominalFuseResults()
{
	return correctOutputGenerator.getNominalFuseResults();
}

/* ---------------------------------------------------------------------------------------- */
/* KEEP_POWER_TEST methods */

void Supervised::setKeepPower(int keepPower)
{
	processUnit.setKeepPower(keepPower);
}

int Supervised::getKeepPowReadback()
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