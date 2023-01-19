#include "include/SimulationControllerTest1.h"

using namespace std;

int SimulationControllerTest1()
{
	// Test Params for Simulation Controller
	string dataMemoryDir = "data/DataMemory",
		simulationMemoryDir = "data/SimulationMemory";
	bool verboseMode = true;

	// Test Params for Supervisor and Supervised
	int maxNumberOfRegisters = 1000;
	double nominalFuseResultBurn = 0.1, nominalFuseResultNotBurn = 0.9;

	cout << "Test started" << endl;

	Supervisor supervisor(
		maxNumberOfRegisters,
		nominalFuseResultBurn, nominalFuseResultNotBurn,
		dataMemoryDir, simulationMemoryDir);

	Supervised supervised(nominalFuseResultBurn, nominalFuseResultNotBurn);

	supervisor.attach(&supervised);

	SimulationController simulationController(dataMemoryDir, simulationMemoryDir, verboseMode);

	simulationController.attach(&supervisor, &supervised);

	simulationController.run();

	cout << "Test completed";

	return 0;
}
