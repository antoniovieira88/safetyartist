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

void FailedOutputGenerator::setFailureScenarioFuseTst(FailureScenarioFuseType* failureScenarioPointer)
{
	meanValueFuseResultBurn = failureScenarioPointer->meanValueFuseResultBurn;
	meanValueFuseResultNotBurn = failureScenarioPointer->meanValueFuseResultNotBurn;
	minFuseResultBurn = failureScenarioPointer->minFuseResultBurn;
	maxFuseResultBurn = failureScenarioPointer->maxFuseResultBurn;
	minFuseResultNotBurn = failureScenarioPointer->minFuseResultNotBurn;
	maxFuseResultNotBurn = failureScenarioPointer->maxFuseResultNotBurn;
}

void FailedOutputGenerator::setFailureScenarioKeepPowTst(FailureScenarioKeepPowType* failureScenarioPointer)
{
	keepPowerReadbackOffValue = failureScenarioPointer->keepPowerReadbackOffValue;
	keepPowerReadbackOnValue = failureScenarioPointer->keepPowerReadbackOnValue;
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

