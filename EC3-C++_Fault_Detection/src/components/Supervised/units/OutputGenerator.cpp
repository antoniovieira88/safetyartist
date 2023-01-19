#include <mlpack/core.hpp>
#include "../include/OutputGenerator.h"

using namespace std;

OutputGenerator::OutputGenerator(
	double meanValueFuseResultBurn,
	double meanValueFuseResultNotBurn,
	double minFuseResultBurn,
	double maxFuseResultBurn,
	double minFuseResultNotBurn,
	double maxFuseResultNotBurn,
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator) :
	generator(generator)
{
	OutputGenerator::meanValueFuseResultBurn = meanValueFuseResultBurn;
	OutputGenerator::meanValueFuseResultNotBurn = meanValueFuseResultNotBurn;
	OutputGenerator::minFuseResultBurn = minFuseResultBurn;
	OutputGenerator::maxFuseResultBurn = maxFuseResultBurn;
	OutputGenerator::minFuseResultNotBurn = minFuseResultNotBurn;
	OutputGenerator::maxFuseResultNotBurn = maxFuseResultNotBurn;
	OutputGenerator::uncertaintyRangeInput = uncertaintyRangeInput;
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
	stdDeviation = 0.0;
}

OutputGenerator::OutputGenerator(
	double meanValueFuseResultBurn,
	double meanValueFuseResultNotBurn,
	double uncertaintyRangeInput,
	mt19937& generator) :
	generator(generator)
{
	OutputGenerator::meanValueFuseResultBurn = meanValueFuseResultBurn;
	OutputGenerator::meanValueFuseResultNotBurn = meanValueFuseResultNotBurn;
	OutputGenerator::minFuseResultBurn = (double NAN);
	OutputGenerator::maxFuseResultBurn = (double NAN);
	OutputGenerator::minFuseResultNotBurn = (double NAN);
	OutputGenerator::maxFuseResultNotBurn = (double NAN);
	uniformDist = uniform_real_distribution<double>{ 0.0, 0.1 };
	OutputGenerator::uncertaintyRangeInput = uncertaintyRangeInput;
	stdDeviation = 0.0;
}

OutputGenerator::OutputGenerator(
	double maxStdDeviation,
	double uncertaintyRangeInput,
	mt19937& generator) :
	generator(generator)
{
	OutputGenerator::meanValueFuseResultBurn = (double NAN);
	OutputGenerator::meanValueFuseResultNotBurn = (double NAN);
	OutputGenerator::minFuseResultBurn = (double NAN);
	OutputGenerator::maxFuseResultBurn = (double NAN);
	OutputGenerator::minFuseResultNotBurn = (double NAN);
	OutputGenerator::maxFuseResultNotBurn = (double NAN);
	uniformDist = uniform_real_distribution<double>{ 0.0, maxStdDeviation };
	OutputGenerator::uncertaintyRangeInput = uncertaintyRangeInput;
	stdDeviation = 0.0;
}

OutputGenerator::OutputGenerator(
	double uncertaintyRangeInput,
	mt19937& generator) :
	generator(generator)
{
	OutputGenerator::meanValueFuseResultBurn = (double NAN);
	OutputGenerator::meanValueFuseResultNotBurn = (double NAN);
	OutputGenerator::minFuseResultBurn = (double NAN);
	OutputGenerator::maxFuseResultBurn = (double NAN);
	OutputGenerator::minFuseResultNotBurn = (double NAN);
	OutputGenerator::maxFuseResultNotBurn = (double NAN);
	uniformDist = uniform_real_distribution<double>{ 0.0, 0.1 };
	OutputGenerator::uncertaintyRangeInput = uncertaintyRangeInput;
	stdDeviation = 0.0;
}

// Implementation of generateOutput method which truncates the value of fuseResult 
// if it is out of the specifed bounds

double OutputGenerator::generateOutputTruncated(double fuseTest)
{
	double fuseResult = 0.0;
	double meanValueFuseResult = 0.0;
	bool burnTest = false;


	stdDeviation = uniformDist(generator);

	if (abs(fuseTest - 0.0) < uncertaintyRangeInput) {
		meanValueFuseResult = meanValueFuseResultBurn;
		burnTest = true;
	}
	else if (abs(fuseTest - 1.0) < uncertaintyRangeInput) {
		meanValueFuseResult = meanValueFuseResultNotBurn;
	}
	else {
		throw runtime_error("Invalid test fuseTest");
	}

	auto normalDistFuseResult = normal_distribution<double>{ meanValueFuseResult, stdDeviation };

	fuseResult = normalDistFuseResult(generator);

	fuseResult = truncateFuseResult(fuseResult, burnTest);

	return fuseResult;
}

double OutputGenerator::getStdDeviation()
{
	return stdDeviation;
}

double OutputGenerator::truncateFuseResult(double fuseResult, bool burnTest) {
	double max = 0.0, min = 0.0;
	if (burnTest) {
		max = maxFuseResultBurn;
		min = minFuseResultBurn;
	}
	else {
		max = maxFuseResultNotBurn;
		min = minFuseResultNotBurn;
	}

	if (fuseResult > max) {
		return max;
	}
	else if (fuseResult < min) {
		return min;
	}
	else {
		return fuseResult;
	}

};

// Implementation of generateOutput method which raffles a value for fuseResult again 
// if its value is out of the specifed bounds

double OutputGenerator::generateOutput(double fuseTest)
{
	double fuseResult = -1.0;
	double meanValueFuseResult = -1.0;
	bool burnTest = false;

	stdDeviation = uniformDist(generator);

	if (abs(fuseTest - 0.0) < uncertaintyRangeInput) {
		meanValueFuseResult = meanValueFuseResultBurn;
		burnTest = true;
	}
	else if (abs(fuseTest - 1.0) < uncertaintyRangeInput) {
		meanValueFuseResult = meanValueFuseResultNotBurn;
	}
	else {
		throw runtime_error("Invalid test fuseTest");
	}

	auto normalDistFuseResult = normal_distribution<double>{ meanValueFuseResult, stdDeviation };

	do {
		fuseResult = normalDistFuseResult(generator);
	} while (checkFuseResultOutOfBounds(fuseResult, burnTest));

	return fuseResult;
}

bool OutputGenerator::checkFuseResultOutOfBounds(double fuseResult, bool burnTest) {
	double max = 0.0, min = 0.0;
	if (burnTest) {
		max = maxFuseResultBurn;
		min = minFuseResultBurn;
	}
	else {
		max = maxFuseResultNotBurn;
		min = minFuseResultNotBurn;
	}
	return (fuseResult > max) || (fuseResult < min);
};

