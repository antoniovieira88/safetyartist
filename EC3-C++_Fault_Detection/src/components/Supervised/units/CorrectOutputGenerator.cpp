#include "../include/CorrectOutputGenerator.h"
#include <random>

using namespace std;

CorrectOutputGenerator::CorrectOutputGenerator(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double minFuseResultBurn,
	double maxFuseResultBurn,
	double minFuseResultNotBurn,
	double maxFuseResultNotBurn,
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator)
	: OutputGenerator(
		nominalValueFuseResultBurn,
		nominalValueFuseResultNotBurn,
		minFuseResultBurn,
		maxFuseResultBurn,
		minFuseResultNotBurn,
		maxFuseResultNotBurn,
		maxStdDeviation,
		uncertaintyRangeInput,
		generator
	) {}

CorrectOutputGenerator::CorrectOutputGenerator(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double uncertaintyRangeInput,
	mt19937& generator) :
	OutputGenerator(
		nominalValueFuseResultBurn,
		nominalValueFuseResultNotBurn,
		uncertaintyRangeInput,
		generator
	)
{}

CorrectOutputGenerator::CorrectOutputGenerator(
	double uncertaintyRangeInput,
	mt19937& generator) : OutputGenerator(
		uncertaintyRangeInput,
		generator
	)
{}

void CorrectOutputGenerator::setBasicParams(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn,
	double maxStdDeviation)
{
	meanValueFuseResultBurn = nominalValueFuseResultBurn;
	meanValueFuseResultNotBurn = nominalValueFuseResultNotBurn;
	minFuseResultBurn = minNominalFuseResultBurn;
	maxFuseResultBurn = maxNominalFuseResultBurn;
	minFuseResultNotBurn = minNominalFuseResultNotBurn;
	maxFuseResultNotBurn = maxNominalFuseResultNotBurn;
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
}

// this function is an override of the method generateKeepPowTestOutput
// when there is no failure, the output of the test, provided by CorrectOutputGenerator,
// is simply 'keepPowerReadback == keepPower'
int CorrectOutputGenerator::generateKeepPowTestOutput(int keepPower)
{
	return keepPower;
};
