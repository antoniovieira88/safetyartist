#include "../include/FailureController.h"

FailureController::FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::numberOfFailedComponents = 0;
	FailureController::singleFailedComponentId = -1;
	FailureController::verboseMode = false;
	FailureController::failedComponentsNameSet = unordered_set<string>();
}

FailureController::FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::numberOfFailedComponents = 0;
	FailureController::singleFailedComponentId = -1;
	FailureController::verboseMode = verboseMode;
}

void FailureController::defineNewRandomTestScenario()
{
	numberOfFailedComponents = 0;

	int failureModeId, singleFailedComponentId;

	if (verboseMode) {
		cout << endl << "------------------" << endl;
		cout << "* Creation of a new testScenario * " << endl;
	}

	for (Component& component : componentsArray) {

		if (verboseMode) {
			cout << endl;
			cout << "Component name: " << component.getComponentName() << endl;
		}

		// recalculate the components's reliability accordingly to its new "countBetweenFailures"
		component.calculateReliability();

		// when the method below is called, the "countBetweenFailures" of the correspondent component
		// is automatically updated for the next iteration
		component.generateNewOperationalState();

		failureModeId = component.getCurrentFaultModeId();

		if (failureModeId != -1) {
			numberOfFailedComponents++;
			failedComponentsNameSet.insert(component.getComponentName());

			// here, the componentId of the single failed component is captured.
			// If there are multiple fails, this information will be later ignored
			singleFailedComponentId = component.getComponentId();
		};

		if (verboseMode) {
			cout << "Component reliability: " << component.getReliability() << endl;
			cout << "Component fault mode: " << component.getCurrentFaultModeName() << endl;
			cout << endl;
		}
	}

	testScenario.numberOfFailedComponents = numberOfFailedComponents;

	if (numberOfFailedComponents == 1) {
		testScenario.singleFailureScenarioPointer = componentsArray[singleFailedComponentId].getPointerForCurrentSingleFailureScenario();
	}
	else if (numberOfFailedComponents == 0) {
		testScenario.singleFailureScenarioPointer = nullptr;
	}
	else {
		// later, there will be an if for multiple failure scenario. 
		// At the moment, singleFailureScenarioPointer is set to nullptr in this condition
		testScenario.singleFailureScenarioPointer = nullptr;
	}

	if (verboseMode) {
		cout << endl;
		cout << "* New testScenario created * " << endl;
		cout << "Number of failed components: " << numberOfFailedComponents << endl;
		cout << "------------------" << endl;
	}

}

void FailureController::defineTestScenarioWithoutFailure()
{
	testScenario.numberOfFailedComponents = 0;

	// failure scenario is set to null
	testScenario.singleFailureScenarioPointer = nullptr;

	// all fault modes in test scenario are set to non-faulty state
	testScenario.nonDetectFailuresFuseTstArray.clear();
}

void FailureController::defineTestScenarioForSpecificFailure(int componentId, int faultModeId, FailureScenarioType* singleFailureScenarioPointer)
{
	testScenario.numberOfFailedComponents = 1;

	// failure scenario is set to the specif fault mode for the desired component
	testScenario.singleFailureScenarioPointer = singleFailureScenarioPointer;
}

int FailureController::getNumberOfFailedComponents()
{
	return numberOfFailedComponents;
}

unordered_set<string>& FailureController::getFailedComponentsNameSet()
{
	return failedComponentsNameSet;
}

void FailureController::setVerboseMode(bool verboseModeValue)
{
	FailureController::verboseMode = verboseModeValue;
}
