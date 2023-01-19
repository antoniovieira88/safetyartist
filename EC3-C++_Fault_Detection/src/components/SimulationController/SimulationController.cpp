#include "include/SimulationController.h"

SimulationController::SimulationController(
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	generator(), iterationEquivalentTime(1.0), simulationName(""),
	simulationSpecificParams({}), componentsArray(),
	testScenario({ 0, vector<int>(), nullptr }),
	paramsController(simulationName, simulationSpecificParams, generator, componentsArray, simulationMemoryDir, verboseMode),
	failureController(componentsArray, testScenario, verboseMode),
	processUnit(
		failureController,
		paramsController,
		testScenario,
		componentsArray,
		simulationSpecificParams,
		generator,
		simulationName,
		dataMemoryDir,
		simulationMemoryDir,
		verboseMode
	)
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

void SimulationController::run()
{
	processUnit.run();
}
