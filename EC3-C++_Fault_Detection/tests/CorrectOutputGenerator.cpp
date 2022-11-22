#include <mlpack/core.hpp>
#include "include/CorrectOutputGenerator.h"
#include <random>

using namespace std;

CorrectOutputGenerator::CorrectOutputGenerator(double meanValueFuseResultBurn,
	double meanValueFuseResultNotBurn,
	double minFuseResultBurn,
	double maxFuseResultBurn,
	double minFuseResultNotBurn,
	double maxFuseResultNotBurn,
	double maxStdDeviation,
	double uncertaintyRangeInput,
	unsigned int seed) : OutputGenerator(
		meanValueFuseResultBurn,
		meanValueFuseResultNotBurn,
		minFuseResultBurn,
		maxFuseResultBurn,
		minFuseResultNotBurn,
		maxFuseResultNotBurn,
		maxStdDeviation,
		uncertaintyRangeInput,
		seed
	) {};