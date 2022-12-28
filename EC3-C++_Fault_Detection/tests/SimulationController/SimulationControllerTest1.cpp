#include "include/SimulationControllerTest1.h"

using namespace std;

int SimulationControllerTest1()
{
	string userInput = "y";
	int duration = 30;
	cout << "Test started" << endl;

	Supervisor supervisor(
		1000,
		0.1, 0.9,
		0.01, 0.01, 0.01, true);

	Supervised supervised(0.1, 0.9, 1);

	supervisor.attach(&supervised);

	SimulationController simulationController(20, 1.0, "data/SimulationMemory/FailureSpecs", "data/SimulationMemory/FailureSpecs/FaultModes", true);

	simulationController.attach(&supervisor, &supervised);

	while (userInput == "y") {
		cout << endl << "Would you like to start a new Simulation?" << endl;
		cout << "Input [y/n]: ";
		cin >> userInput;

		if (userInput == "y") {
			cout << "Set a duration: ";
			cout << "Input [integer number]: ";
			cin >> userInput;
			duration = stoi(userInput);
			cout << endl << endl;
			simulationController.runSimulation(duration);
			userInput = "y";
			supervisor.reinitializeForNewSimulation();
		}
	}

	cout << "Test completed";

	return 0;
}
