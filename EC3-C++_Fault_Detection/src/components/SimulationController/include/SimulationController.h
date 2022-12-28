#include "ProcessUnitSC.h"

using namespace std;
class SimulationController {
public:
	SimulationController(int seed, double simulationStep, string dirFailureSpecs, string dirFaultModes, bool verboseMode);
	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);
	void runSimulation(int duration);
private:
	vector<Component> componentsArray;
	TestScenarioType testScenario;
	mt19937 generator;

	ParamsController paramsController;
	FailureController failureController;
	ProcessUnitSC processUnit;

	bool verboseMode;
};