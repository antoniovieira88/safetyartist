#include "include/SimulationControllerTest1.h"

using namespace std;

int SimulationControllerTest1()
{

	cout << "Test started" << endl;

	Supervisor supervisor(1000, 0.01, 0.01, 0.01, true);
	Supervised supervised(1);

	cout << endl << "Supervised attached to supervisor" << endl;
	supervisor.attach(&supervised);

	SimulationController simulationController(10, 1.0, "data/SimulationMemory", "data/SimulationMemory/FaultModes", true);

	cout << endl << "Supervisor and Supervised attached to Simulation Controller" << endl;

	simulationController.attach(&supervisor, &supervised);

	simulationController.runSimulation(20);

	cout << "Test completed";

	return 0;
}
