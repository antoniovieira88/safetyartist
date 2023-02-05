#include "../include/FailedOutputGenerator.h"

FailedOutputGenerator::FailedOutputGenerator(
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator) :
	OutputGenerator(
		maxStdDeviation,
		uncertaintyRangeInput,
		generator)
{}

FailedOutputGenerator::FailedOutputGenerator(
	double uncertaintyRangeInput,
	mt19937& generator) :
	OutputGenerator(
		uncertaintyRangeInput,
		generator)

{}

void FailedOutputGenerator::setFailureScenario(FailureScenarioType* failureScenario)
{
	meanValueFuseResultBurn = failureScenario->fuseTestFailureScenario.meanValueFuseResultBurn;
	meanValueFuseResultNotBurn = failureScenario->fuseTestFailureScenario.meanValueFuseResultNotBurn;
	minFuseResultBurn = failureScenario->fuseTestFailureScenario.minFuseResultBurn;
	maxFuseResultBurn = failureScenario->fuseTestFailureScenario.maxFuseResultBurn;
	minFuseResultNotBurn = failureScenario->fuseTestFailureScenario.minFuseResultNotBurn;
	maxFuseResultNotBurn = failureScenario->fuseTestFailureScenario.maxFuseResultNotBurn;

	keepPowerReadbackOffValue = failureScenario->keepPowFailureScenario.keepPowerReadbackOffValue;
	keepPowerReadbackOnValue = failureScenario->keepPowFailureScenario.keepPowerReadbackOnValue;
}

void FailedOutputGenerator::setMaxStdDeviation(double maxStdDeviation)
{
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
}

int FailedOutputGenerator::generateKeepPowTestOutput(int keepPower)
{
	if (keepPower == 0) return keepPowerReadbackOffValue;
	return keepPowerReadbackOnValue;
}

