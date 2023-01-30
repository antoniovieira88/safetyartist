#include "CorrectOutputGenerator.h"
#include "FailedOutputGenerator.h"

using namespace std;

class ProcessUnitSD {
public:
	ProcessUnitSD(
		CorrectOutputGenerator& correctOutputGenerator,
		FailedOutputGenerator& failedOutputGenerator
	);

	void setTestScenario(TestScenarioType& testScenario);

	// FuseTest
	void setFuseTest(double fuseTest);
	double runFuseTest();

	// KeepPowTest
	void setKeepPower(int keepPower);
	int runKeepPowTest();

private:
	double fuseTest;
	int keepPower;
	double stdDeviationTest;
	bool fail;

	FailureScenarioType* failureScenario;

	// member added only for test purpose
	FailureScenarioType multipleFailureScenario;

	CorrectOutputGenerator& correctOutputGenerator;
	FailedOutputGenerator& failedOutputGenerator;
};