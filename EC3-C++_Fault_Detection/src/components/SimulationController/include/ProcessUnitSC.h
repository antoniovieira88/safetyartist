#include "MultiFailureRunner.h"

using namespace std;

class ProcessUnitSC {
public:
	ProcessUnitSC(
		FailureController& failureController,
		ParamsController& paramsController,
		TestScenarioType& testScenario,
		vector<Component>& componentsArray,
		SimulationSpecificParamsType& simulationSpecificParams,
		MtRandEngine& generator,
		string& simulationName,
		int*& iterationPointer,
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true
	);

	~ProcessUnitSC();

	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);
	void setVerboseMode(bool verboseModeValue);

	void run();

private:
	const string dataMemoryDir;
	const string simulationsDir;
	const string simulationMemoryDir;

	vector<FailureEventType> failureEventsArray;

	FailureController& failureController;
	ParamsController& paramsController;
	TestScenarioType& testScenario;
	MtRandEngine& generator;
	vector<Component>& componentsArray;
	string& simulationName;
	SimulationSpecificParamsType& simulationSpecificParams;

	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;
	int*& iterationPointer;

	bool verboseMode;

	void initializeParamsController();
	void runSimulationCycle(int duration, bool noFailuresMode = false);

	void resetComponentsOperationalStates();
	void resetSupervisor();
	void getReadyForNextSimulationCycle();

	void loadMtRandEngines();
	void saveMtRandEngines();
	void resetMtRandEngines();

	void avaliateComponentFaultModes(Component& component, vector<FaultModeAnalysisResultType>& faultModeAnalysisResultArray);
	void singleFailureInjectionOption();
	void singleFailureInjectionTest();

	int userSimulationCycleParamsOptions();

	void chooseVerboseMode();
	void createNewSimulation();
	void collectNewSimulationParams(SimulationSpecificParamsType& simulationParams, string simulationName);
	void loadSimulation();
	void selectSimulation();
	void setSimulationParams();
	void printVerboseMode();

	void collectResultsFromSingleIteration(FuseTestResultsType& fuseTestResults, KeepPowerTestResultsType& keepPowerTestResults);

	test getNextTestToBePerfomed();

	void multipleFailuresTestOption();
};