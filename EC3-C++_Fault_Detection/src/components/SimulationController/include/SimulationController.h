#include "ProcessUnitSC.h"

class SimulationController {
public:
	SimulationController(int seed, double simulationStep, string dirFailureSpecs, string dirFaultModes, bool verboseMode);
	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);
	void runSimulation(int duration);
private:
	vector<Component> componentsArray;
	vector<int> testScenario;
	mt19937 generator;

	ParamsController paramsController;
	FailureController failureController;
	ProcessUnitSC processUnit;
};