#include "OutputGenerator.h"

using namespace std;

class CorrectOutputGenerator : public OutputGenerator {
public:
	CorrectOutputGenerator(
		double nominalValueFuseResultBurn,
		double nominalValueFuseResultNotBurn,
		double minFuseResultBurn,
		double maxFuseResultBurn,
		double minFuseResultNotBurn,
		double maxFuseResultNotBurn,
		double maxStdDeviation,
		double uncertaintyRangeInput,
		mt19937& generator);

	CorrectOutputGenerator(
		double nominalValueFuseResultBurn,
		double nominalValueFuseResultNotBurn,
		double uncertaintyRangeInput,
		mt19937& generator);

	CorrectOutputGenerator(
		double uncertaintyRangeInput,
		mt19937& generator);

	void setBasicParams(
		double nominalValueFuseResultBurn,
		double nominalValueFuseResultNotBurn,
		double minNominalFuseResultBurn,
		double maxNominalFuseResultBurn,
		double minNominalFuseResultNotBurn,
		double maxNominalFuseResultNotBurn,
		double maxStdDeviation);

	int generateKeepPowTestOutput(int keepPower);
};