#include "CorrectOutputGenerator.h"
#include "FailedOutputGenerator.h"

using namespace std;

class ProcessUnitSD {
public:
	ProcessUnitSD(
		CorrectOutputGenerator& correctOutputGenerator,
		FailedOutputGenerator& failedOutputGenerator
	);

	// FuseTest
	void setFuseTestScenario(FuseTestScenarioType& testScenario);
	void setFuseTest(double fuseTest);
	double runFuseTest();

	// KeepPowTest
	void setKeepPowTestScenario(bool fail);
	void setKeepPower(double keepPower);
	double runKeepPowTest();

private:
	double fuseTest, keepPower;
	double stdDeviationTest;
	bool fail;

	FailureScenarioType* failureScenario;

	// member added only for test purpose
	FailureScenarioType multipleFailureScenario;

	CorrectOutputGenerator& correctOutputGenerator;
	FailedOutputGenerator& failedOutputGenerator;
};