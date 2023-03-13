// change the directory to run different tests
#include "../../tests/SimulationController/include/SimulationControllerTest1.h"
//#include "../../tests/RandomGeneratorMt19937/include/RandomGeneratorTest.h"

using namespace std;

int main()
{
	string dataMemoryDir = "data/DataMemory";
	string simulationMemoryDir = "data/SimulationMemory";
	bool verboseMode = true;

	try {
		Supervisor supervisor(dataMemoryDir, simulationMemoryDir);

		Supervised supervised;

		supervisor.attach(&supervised);

		SimulationController simulationController(dataMemoryDir, simulationMemoryDir, verboseMode);

		simulationController.attach(&supervisor, &supervised);

		simulationController.run();
	}
	catch (exception& error) {
		cout << endl << endl << error.what() << endl;
		cout << "Simulator run canceled" << endl;
	}

	cout << endl << endl << "Press any button to close the terminal";

	getchar();

	return 0;
}