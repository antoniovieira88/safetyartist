#include "ProcessUnitSC.h"

using namespace std;

class SimulationController {
public:

	SimulationController(
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true);
	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);
	void* getObjectMemberRef(simulationMemberObj obj);
	void run();

private:
	vector<Component> componentsArray;
	TestScenarioType testScenario;
	MtRandEngine generator;
	string simulationName;
	int* iterationPointer;
	SimulationSpecificParamsType simulationSpecificParams;

	ParamsController paramsController;
	FailureController failureController;
	ProcessUnitSC processUnit;

	bool verboseMode;
	double iterationEquivalentTime;
};