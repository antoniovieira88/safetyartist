#include <random>
#include <cmath>

using namespace std;

#pragma once
class OutputGenerator {
public:
	OutputGenerator(
		double meanValueFuseResultBurn,
		double meanValueFuseResultNotBurn,
		double minFuseResultBurn,
		double maxFuseResultBurn,
		double minFuseResultNotBurn,
		double maxFuseResultNotBurn,
		double maxStdDeviation,
		double uncertaintyRangeInput,
		mt19937& generator);

	OutputGenerator(
		double meanValueFuseResultBurn,
		double meanValueFuseResultNotBurn,
		double uncertaintyRangeInput,
		mt19937& generator);

	OutputGenerator(
		double maxStdDeviation,
		double uncertaintyRangeInput,
		mt19937& generator);

	OutputGenerator(
		double uncertaintyRangeInput,
		mt19937& generator);

	double generateOutput(double fuseTest);
	double generateOutputTruncated(double fuseTest);

	double getStdDeviation();
	vector<double> getNominalFuseResults();

protected:
	double meanValueFuseResultBurn;
	double minFuseResultBurn, maxFuseResultBurn;

	double meanValueFuseResultNotBurn;
	double minFuseResultNotBurn, maxFuseResultNotBurn;

	double uncertaintyRangeInput;
	double stdDeviation;

	mt19937& generator;
	uniform_real_distribution<double> uniformDist;

	double truncateFuseResult(double fuseResult, bool burnTest);
	bool checkFuseResultOutOfBounds(double fuseResult, bool burnTest);
};