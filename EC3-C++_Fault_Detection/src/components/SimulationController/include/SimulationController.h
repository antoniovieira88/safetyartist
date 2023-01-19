#include "ProcessUnitSC.h"

using namespace std;

class SimulationController {
public:
	SimulationController(
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true);
	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);
	void run();

private:
	vector<Component> componentsArray;
	FuseTestScenarioType testScenario;
	MtRandEngine generator;
	string simulationName;
	SimulationSpecificParamsType simulationSpecificParams;

	ParamsController paramsController;
	FailureController failureController;
	ProcessUnitSC processUnit;

	bool verboseMode;
	double iterationEquivalentTime;
};