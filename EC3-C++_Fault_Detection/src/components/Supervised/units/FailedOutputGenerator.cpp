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
	meanValueFuseResultBurn = failureScenario->meanValueFuseResultBurn;
	meanValueFuseResultNotBurn = failureScenario->meanValueFuseResultNotBurn;
	minFuseResultBurn = failureScenario->minFuseResultBurn;
	maxFuseResultBurn = failureScenario->maxFuseResultBurn;
	minFuseResultNotBurn = failureScenario->minFuseResultNotBurn;
	maxFuseResultNotBurn = failureScenario->maxFuseResultNotBurn;
}

void FailedOutputGenerator::setMaxStdDeviation(double maxStdDeviation)
{
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
}


