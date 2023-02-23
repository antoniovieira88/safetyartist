#include "include/SimulationController.h"

SimulationController::SimulationController(
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	generator(), simulationName(""), iterationPointer(nullptr),
	simulationSpecificParams({}), componentsArray(),
	testScenario(
		{ 0, false, false, false, false,
		vector<FaultModeType*>(), vector<int>(),
		nullptr, nullptr }),
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
	void* refForObject = nullptr;

	using typeObj = simulationMemberObj;

	switch (obj) {
	case typeObj::processUnit:
		refForObject = &processUnit;
		break;
	case typeObj::paramsController:
		refForObject = &paramsController;
		break;
	case typeObj::failureController:
		refForObject = &failureController;
		break;
	case typeObj::generator:
		refForObject = &generator;
		break;
	case typeObj::simulationName:
		refForObject = &simulationName;
		break;
	case typeObj::iterationPointer:
		refForObject = &iterationPointer;
		break;
	case typeObj::simulationSpecificParams:
		refForObject = &simulationSpecificParams;
		break;
	case typeObj::verboseMode:
		refForObject = &verboseMode;
		break;
	case typeObj::iterationEquivalentTime:
		refForObject = &iterationEquivalentTime;
		break;
	case typeObj::componentsArray:
		refForObject = &componentsArray;
		break;
	case typeObj::testScenario:
		refForObject = &testScenario;
		break;
	default:
		break;
	}

	return refForObject;
}

void SimulationController::run()
{
	processUnit.run();
}
