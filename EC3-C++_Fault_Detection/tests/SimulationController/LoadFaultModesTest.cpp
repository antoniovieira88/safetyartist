#include "include/LoadFaultModesTest.h"

using namespace std;

int LoadFaultModesTest()
{
	vector<Component> componentsArray;
	mt19937 generator(10);

	int iteration;
	double stepDuration = 1.0;
	string simulationName = "LoadFaultModesTest";
	SimulationSpecificParamsType params{};

	cout << "Test started" << endl;

	ParamsController paramsController(simulationName, params, generator, componentsArray);
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
