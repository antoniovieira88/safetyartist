#include "FailureController.h"
#include "../../../utils/exceptions/include/AbortSimulationOpExcep.h"
#include "../../Supervisor/include/Supervisor.h"
#include <filesystem>

using namespace std;

class ProcessUnitSC {
public:
	ProcessUnitSC(
		FailureController& failureController,
		ParamsController& paramsController,
		FuseTestScenarioType& testScenario,
		vector<Component>& componentsArray,
		SimulationSpecificParamsType& simulationSpecificParams,
		MtRandEngine& generator,
		string& simulationName,
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

	FailureController& failureController;
	ParamsController& paramsController;
	FuseTestScenarioType& testScenario;
	MtRandEngine& generator;
	vector<Component>& componentsArray;
	string& simulationName;
	SimulationSpecificParamsType& simulationSpecificParams;
	vector<double> nominalFuseResults;

	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;
	int* iterationPointer;

	bool verboseMode;
	filesystem::path defaultComponentsOperationStateFilePath;

	void initializeParamsController();
	void runSimulationCycle(int duration);

	void resetComponentsOperationalStates();
	void resetSupervisor();
	void getReadyForNextSimulationCycle();
	void loadMtRandEngines();
	void saveMtRandEngines();

	void createSimulationFiles(string simulationName);

	int userSimulationCycleParamsOptions();

	void chooseVerboseMode();
	void createNewSimulation();
	void createSimulationParams(string simulationName);
	bool searchForSimulationDirectories(string simulationName);
	void loadSimulation();
	void selectSimulation();
	void setSimulationParams();
	void createLogAndStatusCSVFiles(string simulationName);
	void printVerboseMode();
	void recordHistoricalFailureLog(bool noFaults, bool failureDetected, string LogError = "");
};

