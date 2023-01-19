#include <mlpack/core.hpp>
#include "../include/CorrectOutputGenerator.h"
#include <random>

using namespace std;

CorrectOutputGenerator::CorrectOutputGenerator(
	double meanValueFuseResultBurn,
	double meanValueFuseResultNotBurn,
	double minFuseResultBurn,
	double maxFuseResultBurn,
	double minFuseResultNotBurn,
	double maxFuseResultNotBurn,
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator)
	: OutputGenerator(
		meanValueFuseResultBurn,
		meanValueFuseResultNotBurn,
		minFuseResultBurn,
		maxFuseResultBurn,
		minFuseResultNotBurn,
		maxFuseResultNotBurn,
		maxStdDeviation,
		uncertaintyRangeInput,
		generator
	) {}

CorrectOutputGenerator::CorrectOutputGenerator(
	double meanValueFuseResultBurn,
	double meanValueFuseResultNotBurn,
	double uncertaintyRangeInput,
	mt19937& generator) :
	OutputGenerator(
		meanValueFuseResultBurn,
		meanValueFuseResultNotBurn,
		uncertaintyRangeInput,
		generator
	)
{}

void CorrectOutputGenerator::setBasicParams(
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn,
	double maxStdDeviation)
{
	minFuseResultBurn = minNominalFuseResultBurn;
	maxFuseResultBurn = maxNominalFuseResultBurn;
	minFuseResultNotBurn = minNominalFuseResultNotBurn;
	maxFuseResultNotBurn = maxNominalFuseResultNotBurn;
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
};
