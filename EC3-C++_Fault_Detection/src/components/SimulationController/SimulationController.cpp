#include "include/SimulationController.h"

SimulationController::SimulationController(
	int seed,
	double simulationStep,
	string dirFailureSpecs,
	string dirFaultModes,
	bool verboseMode)
	:
	generator(seed),
	componentsArray(), testScenario(),
	paramsController(simulationStep, generator, componentsArray, dirFailureSpecs, dirFaultModes, verboseMode),
	failureController(componentsArray, testScenario, verboseMode),
	processUnit(failureController, paramsController, testScenario)
{

}

void SimulationController::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	processUnit.attach(supervisorPointer, supervisedPointer);
}

void SimulationController::runSimulation(int duration)
{
	processUnit.runSimulation(duration);
}
