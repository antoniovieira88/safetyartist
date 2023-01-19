#include "CorrectOutputGenerator.h"
#include "FailedOutputGenerator.h"

using namespace std;

class ProcessUnitSD {
public:
	ProcessUnitSD(
		CorrectOutputGenerator& correctOutputGenerator,
		FailedOutputGenerator& failedOutputGenerator
	);
	void setFuseTestInput(double input);
	void setFuseTestScenario(FuseTestScenarioType& testScenario);
	void setKeepPower(double keepPower);
	double getFuseTestOutput();

private:
	double testInput, testOutput, stdDeviationTest, keepPower;
	bool fail;

	FailureScenarioType* failureScenario;

	// member added only for test purpose
	FailureScenarioType multipleFailureScenario;

	CorrectOutputGenerator& correctOutputGenerator;
	FailedOutputGenerator& failedOutputGenerator;
};