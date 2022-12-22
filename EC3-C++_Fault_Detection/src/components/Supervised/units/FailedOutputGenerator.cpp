#include "../include/FailedOutputGenerator.h"

FailedOutputGenerator::FailedOutputGenerator(
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator)
	: OutputGenerator(
		maxStdDeviation,
		uncertaintyRangeInput,
		generator)
{
}

void FailedOutputGenerator::setFailureScenario(FailureScenarioType& failureScenario)
{
	meanValueFuseResultBurn = failureScenario.meanValueFuseResultBurn;
	meanValueFuseResultNotBurn = failureScenario.meanValueFuseResultNotBurn;
	minFuseResultBurn = failureScenario.minFuseResultBurn;
	maxFuseResultBurn = failureScenario.maxFuseResultBurn;
	minFuseResultNotBurn = failureScenario.minFuseResultNotBurn;
	maxFuseResultNotBurn = failureScenario.maxFuseResultNotBurn;
}


