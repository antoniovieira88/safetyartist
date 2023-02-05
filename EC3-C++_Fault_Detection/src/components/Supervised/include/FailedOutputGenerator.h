#include "OutputGenerator.h"
#include "../../../utils/structs/structs.h"

using namespace std;

class FailedOutputGenerator : public OutputGenerator {
public:
	FailedOutputGenerator(
		double maxStdDeviation,
		double uncertaintyRangeInput,
		mt19937& generator);

	FailedOutputGenerator(
		double uncertaintyRangeInput,
		mt19937& generator);

	void setFailureScenario(FailureScenarioType* failureScenario);
	int generateKeepPowTestOutput(int keepPower);
	void setMaxStdDeviation(double maxStdDeviation);

};