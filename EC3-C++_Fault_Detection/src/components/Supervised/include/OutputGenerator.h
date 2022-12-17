#include <random>
#include <cmath>

using namespace std;

class OutputGenerator {
public:
	OutputGenerator(double meanValueFuseResultBurn,
		double meanValueFuseResultNotBurn,
		double minFuseResultBurn,
		double maxFuseResultBurn,
		double minFuseResultNotBurn,
		double maxFuseResultNotBurn,
		double maxStdDeviation,
		double uncertaintyRangeInput,
		unsigned int seed);

	double generateOutput(double fuseTest);
	double generateOutput2(double fuseTest);

	double getStdDeviation();

protected:
	double meanValueFuseResultBurn;
	double minFuseResultBurn, maxFuseResultBurn;

	double meanValueFuseResultNotBurn;
	double minFuseResultNotBurn, maxFuseResultNotBurn;

	double uncertaintyRangeInput;
	unsigned int seed;
	double maxStdDeviation;
	double stdDeviation;

	default_random_engine generator;
	uniform_real_distribution<double> uniformDist;

	double truncateFuseResult(double fuseResult, bool burnTest);
	bool checkFuseResultOutOfBounds(double fuseResult, bool burnTest);
};