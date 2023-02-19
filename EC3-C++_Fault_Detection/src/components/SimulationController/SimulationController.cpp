#include "include/SimulationController.h"

SimulationController::SimulationController(
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	generator(), simulationName(""), iterationPointer(nullptr),
	simulationSpecificParams({}), componentsArray(),
	testScenario({ 0, false, false, false, false, vector<int>(), nullptr, nullptr }),
	paramsController(simulationName, simulationSpecificParams, generator, componentsArray, iterationPointer, simulationMemoryDir, verboseMode),
	failureController(componentsArray, testScenario, verboseMode),
	processUnit(
		failureController,
		paramsController,
		testScenario,
		componentsArray,
		simulationSpecificParams,
		generator,
		simulationName,
		iterationPointer,
		dataMemoryDir,
		simulationMemoryDir,
		verboseMode
	)
{
	SimulationController::iterationEquivalentTime = (double NAN);
	SimulationController::verboseMode = verboseMode;
}

void SimulationController::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	processUnit.attach(supervisorPointer, supervisedPointer);
	iterationPointer = supervisorPointer->getIterationPointer();

	if (verboseMode) {
		cout << endl << "Supervisor and Supervised attached to Simulation Controller" << endl;
	}
}

void* SimulationController::getObjectMemberRef(simulationMemberObj obj)
{
	void* pointerForObject = nullptr;

	switch (obj) {
	default:
		break;
	}

	return pointerForObject;
}

void SimulationController::run()
{
	processUnit.run();
}
