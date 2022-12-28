#include "include/SimulationController.h"

SimulationController::SimulationController(
	int seed,
	double simulationStep,
	string dirFailureSpecs,
	string dirFaultModes,
	bool verboseMode)
	:
	generator(seed),
	componentsArray(), testScenario({ 0, vector<int>(), nullptr }),
	paramsController(simulationStep, generator, componentsArray, dirFailureSpecs, dirFaultModes, verboseMode),
	failureController(componentsArray, testScenario, verboseMode),
	processUnit(failureController, paramsController, testScenario, componentsArray, simulationStep, verboseMode)
{
	SimulationController::verboseMode = verboseMode;
}

void SimulationController::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	processUnit.attach(supervisorPointer, supervisedPointer);

	if (verboseMode) {
		cout << endl << "Supervisor and Supervised attached to Simulation Controller" << endl;
	}
}

void SimulationController::runSimulation(int duration)
{
	processUnit.runSimulation(duration);

	if (verboseMode) {
		cout << endl << "Simulation finished" << endl;
	}
}
