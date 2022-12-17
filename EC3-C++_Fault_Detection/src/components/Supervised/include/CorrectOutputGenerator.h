#include <random>
#include <cmath>
#include "OutputGenerator.h"

using namespace std;

class CorrectOutputGenerator : public OutputGenerator {
public:
	CorrectOutputGenerator(double meanValueFuseResultBurn,
		double meanValueFuseResultNotBurn,
		double minFuseResultBurn,
		double maxFuseResultBurn,
		double minFuseResultNotBurn,
		double maxFuseResultNotBurn,
		double maxStdDeviation,
		double uncertaintyRangeInput,
		unsigned int seed);
};