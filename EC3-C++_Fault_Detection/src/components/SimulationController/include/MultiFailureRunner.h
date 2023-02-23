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

	string simulationsDir;
	vector<InjectedFailureType> injectedFailuresArray;

	void collectInjectedFailures();
	void runSimulationCycleWithInjectedFailures();

	void restoreDefaultSimulationCondition();
	void resetSupervisor();
};