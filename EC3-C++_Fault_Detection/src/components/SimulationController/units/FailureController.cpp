#include "../include/FailureController.h"

FailureController::FailureController(vector<Component>& componentsArray, vector<int>& testScenario) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::numberOfFailedComponents = 0;
	FailureController::singleFailedComponentId = -1;
	FailureController::verboseMode = false;

}

FailureController::FailureController(vector<Component>& componentsArray, vector<int>& testScenario, bool verboseMode) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::numberOfFailedComponents = 0;
	FailureController::singleFailedComponentId = -1;
	FailureController::verboseMode = verboseMode;

}

void FailureController::defineNewTestScenario()
{
	testScenario.clear();
	numberOfFailedComponents = 0;
	singleFailedComponentId = -1;

	int failureModeId;

	if (verboseMode) {
		cout << endl << "------------------" << endl;
		cout << "* Creation of a new testScenario * " << endl;
	}

	for (Component& component : componentsArray) {

		if (verboseMode) {
			cout << endl;
			cout << "Component name: " << component.getComponentName() << endl;
		}

		// recalculate the the components's reliability accordingly to its new "countBetweenFailures"
		component.calculateReliability();

		// when the method below is called, the "countBetweenFailures" of the correspondent component
		// is automatically updated for the next iteration
		component.generateNewOperationalState();

		failureModeId = component.getCurrentFaultModeId();
		testScenario.push_back(failureModeId);

		if (failureModeId != -1) {
			numberOfFailedComponents++;
			singleFailedComponentId = component.getComponentId();
		};

		if (verboseMode) {
			cout << "Component reliability: " << component.getReliability() << endl;
			cout << "Component fault mode: " << component.getCurrentFaultModeName() << endl;
			cout << endl;
		}
	}

	if (verboseMode) {
		cout << endl;
		cout << "* New testScenario created * " << endl;
		cout << "Number of failed components: " << numberOfFailedComponents << endl;
		cout << "------------------" << endl;
	}

}

int FailureController::getNumberOfFailedComponents()
{
	return numberOfFailedComponents;
}
