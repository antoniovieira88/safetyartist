#include "IterationRunner.h"

using namespace std;
class MultiFailureRunner {
public:
	MultiFailureRunner(
		FailureController& failureController,
		TestScenarioType& testScenario,
		string& simulationName,
		vector<Component>& componentsArray,
		Supervisor* supervisorPointer,
		Supervised* supervisedPointer,
		string dataMemoryDir,
		string simulationMemoryDir,
		bool& verboseMode
	);

	void run();
private:

	FailureController& failureController;
	SimulationFileHandler simulationFileHandler;
	string& simulationName;
	int*& iterationPointer;
	vector<Component>& componentsArray;
	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;
	TestScenarioType& testScenario;
	vector<FailureEventType> failureEventsArray;

	bool& verboseMode;

	void addFailureToEventsArray(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed, int iteration);

	string simulationsDir, outputFilename;
	vector<InjectedFailureType> injectedFailuresArray;

	void chooseOption();

	void runAllTests(string srcDir);
	void runSpecificTest(string inputFilename, string srcDir);

	void collectInjectedFailures(string inputFilename, string srcDir);
	void runSimulationCycleWithInjectedFailures(string testName);

	void restoreDefaultSimulationCondition();
	void resetSupervisor();

	string readTestName();
	string extractTestName(string inputFilename);
};