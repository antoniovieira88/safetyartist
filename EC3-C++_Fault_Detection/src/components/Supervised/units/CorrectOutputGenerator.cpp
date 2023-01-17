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

void CorrectOutputGenerator::setBasicParams(
	double minNominalFuseResultBurn,
	double maxNominalFuseResultBurn,
	double minNominalFuseResultNotBurn,
	double maxNominalFuseResultNotBurn)
{
	minFuseResultBurn = minNominalFuseResultBurn;
	maxFuseResultBurn = maxNominalFuseResultBurn;
	minFuseResultNotBurn = minNominalFuseResultNotBurn;
	maxFuseResultNotBurn = maxNominalFuseResultNotBurn;
};
