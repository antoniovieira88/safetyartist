#include "include/SimulationControllerTest1.h"

using namespace std;

int SimulationControllerTest1()
{
	// Test Params for Simulation Controller
	// ! the paths must not start with /
	/*string dataMemoryDir = "tests/data/SimulationControllerTests/DataMemory",
		simulationMemoryDir = "tests/data/SimulationControllerTests/SimulationMemory";*/
	string dataMemoryDir = "data/DataMemory",
		simulationMemoryDir = "data/SimulationMemory";
	bool verboseMode = true;

	cout << "Test started" << endl;

	Supervisor supervisor(dataMemoryDir, simulationMemoryDir);

	Supervised supervised;

	supervisor.attach(&supervised);

	SimulationController simulationController(dataMemoryDir, simulationMemoryDir, verboseMode);

	simulationController.attach(&supervisor, &supervised);

	simulationController.run();

	cout << "Test completed";

	return 0;
}
