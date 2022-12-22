#include "include/LoadFaultModesTest.h"

using namespace std;

int LoadFaultModesTest()
{
	vector<Component> componentsArray;
	mt19937 generator(10);

	int iteration;

	cout << "Test started" << endl;

	ParamsController paramsController(1.0, generator, componentsArray, "data/SimulationMemory", "data/SimulationMemory/FaultModes", true);
	paramsController.loadFailureSpecs();

	for (iteration = 1; iteration < 20; iteration++) {
		cout << endl;
		cout << "Begin of iteration " << iteration << endl;

		for (Component& component : componentsArray) {
			cout << endl;
			cout << "Component name: " << component.getComponentName() << endl;

			component.calculateReliability();
			component.generateNewOperationalState();

			cout << "Component reliability: " << component.getReliability() << endl;
			cout << "Component fault mode: " << component.getCurrentFaultModeName() << endl;
			cout << endl;
		}

		cout << "End of iteration" << iteration << endl;
		cout << endl;
		cout << "------------------" << endl;
	}
	cout << "Test completed";

	return 0;
}
