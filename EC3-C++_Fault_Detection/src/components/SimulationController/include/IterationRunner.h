#include "../../Supervisor/include/Supervisor.h"
#include "FailureController.h"
#include "SimulationFileHandler.h"

class IterationRunner {
public:
	IterationRunner(
		Supervisor* supervisorPointer,
		Supervised* supervisedPointer,
		vector<Component>& componentsArray,
		TestScenarioType& testScenario,
		vector<FailureEventType>& failureEventsArray,
		int*& iterationPointer,
		string simulationDir,
		bool verboseMode);

	void runTest();

	test getNextTestToBePerfomed();

private:
	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;
	TestScenarioType& testScenario;
	vector<Component>& componentsArray;
	vector<FailureEventType>& failureEventsArray;
	int*& iterationPointer;

	string simulationDir;

	bool verboseMode;

	void verifyTestScenarioForSimulationEnd(test perfomedTest);

	void recordHistoricalFailureLog(bool noFaults, bool failureDetected, string logError = "");

	string failedComponentsListString();

	void updateFailureEventsArray(bool failureDetected, test testName);
};