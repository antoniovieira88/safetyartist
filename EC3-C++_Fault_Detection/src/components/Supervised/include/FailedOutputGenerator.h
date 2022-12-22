#include "OutputGenerator.h"
#include "../../../utils/structs/structs.h"

class FailedOutputGenerator : public OutputGenerator {
public:
	FailedOutputGenerator(
		double maxStdDeviation,
		double uncertaintyRangeInput,
		mt19937& generator);

	void setFailureScenario(FailureScenarioType& failureScenario);

};