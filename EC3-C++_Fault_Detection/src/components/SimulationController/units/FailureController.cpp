#include "../include/FailureController.h"

FailureController::FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::maxNumberOfFailuresWithImpact = 2;
	FailureController::numberOfFailedComponents = 0;
	FailureController::singleFailedComponentId = -1;
	FailureController::verboseMode = verboseMode;
	FailureController::failureScenarioFuseTstLocked = false;
	FailureController::failureScenarioKeepPowTstLocked = false;
}

void FailureController::defineNewRandomTestScenario(test nextTestToBePerfomed)
{
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
		componentOpStatus status = component.generateNewOperationalState();

		// update of TestScenario when a new failure is identified
		if (status == newFault) {
			int faultModeId = component.getCurrentFaultModeId();
			FaultModeType* pointerForNewFaultMode = component.getPointerForFaultMode(faultModeId);

			updateTestScenario(pointerForNewFaultMode);

			// the names of the failed components is captured for log
			// purposes (they appear in the log file 'AllHistoricalFailures.csv')
			failedComponentsNameSet.insert(component.getComponentName());
		}

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

void FailureController::defineTestScenarioWithoutFailure()
{
	testScenario.numberOfFailedComponents = 0;

	// failure scenario for each test is set to null
	testScenario.fuseFailureScenarioPointer = nullptr;
	testScenario.keepPowFailureScenarioPointer = nullptr;

	failureScenarioFuseTstLocked = false;
	failureScenarioKeepPowTstLocked = false;

	failuresWithImpactArray.clear();
}

void FailureController::defineTestScenarioForSpecificFaultMode(FaultModeType* faultModePointer)
{
	testScenario.numberOfFailedComponents = 1;

	// failure scenario is set to the specif fault mode for the desired component
	testScenario.fuseFailureScenarioPointer = &(faultModePointer->singleFailureScenario.fuseFailureScenario);
	testScenario.keepPowFailureScenarioPointer = &(faultModePointer->singleFailureScenario.keepPowFailureScenario);
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

fmDetectable FailureController::getFmDetectableForNextText(FaultModeType* pointerForFaultMode, test nextTestToBePerfomed)
{
	if (nextTestToBePerfomed == fuseTest)
		return pointerForFaultMode->fmDetectableFuse;

	return pointerForFaultMode->fmDetectableKeepPow;
}

void FailureController::updateTestScenario(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed)
{
	numberOfFailedComponents++;
	testScenario.numberOfFailedComponents = numberOfFailedComponents;

	fmDetectable fmDetectable = getFmDetectableForNextText(pointerForNewFaultMode, nextTestToBePerfomed);

	int numberOFFailuresWithImpact = failuresWithImpactArray.size();

	if (numberOFFailuresWithImpact == 0) {
		testScenario.fuseFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.fuseFailureScenario);
		testScenario.keepPowFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.keepPowFailureScenario);

		if (fmDetectable != impactless) {
			failuresWithImpactArray.push_back(pointerForNewFaultMode);
		}
	}

	else if (numberOFFailuresWithImpact < maxNumberOfFailuresWithImpact) {
		if (fmDetectable != impactless) {
			resolveFailureScenarioForMultipleFailuresWithImpact(pointerForNewFaultMode);
			failuresWithImpactArray.push_back(pointerForNewFaultMode);
		}
	}

	else {
		throw exception();
	}
}

void FailureController::resolveFailureScenarioForMultipleFailuresWithImpact(FaultModeType* pointerForNewFaultMode)
{
	FaultModeType* pointerForLastFaultMode = failuresWithImpactArray.back();

	if (!failureScenarioFuseTstLocked) {
		resolveFuseFailureScenario(pointerForLastFaultMode, pointerForNewFaultMode);
	}

	if (!failureScenarioKeepPowTstLocked) {
		resolveKeepPowFailureScenario(pointerForLastFaultMode, pointerForNewFaultMode);
	}
}

void FailureController::resolveFuseFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode)
{
	classMultipleFaults eqClassNewFm = pointerForNewFaultMode->classMultipleFaults;

	if (eqClassNewFm == cm2 || eqClassNewFm == cm3) {
		testScenario.fuseFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.fuseFailureScenario);
		failureScenarioFuseTstLocked = true;
	}
	else {
		fmDetectable detectableLastFm = pointerForLastFaultMode->fmDetectableFuse;
		if (detectableLastFm != yes) {
			testScenario.fuseFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.fuseFailureScenario);
		}
	}
}

void FailureController::resolveKeepPowFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode)
{
	classMultipleFaults eqClassNewFm = pointerForNewFaultMode->classMultipleFaults;

	if (eqClassNewFm == cm1 || eqClassNewFm == cm3) {
		testScenario.keepPowFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.keepPowFailureScenario);
		failureScenarioKeepPowTstLocked = true;
	}
	else {
		fmDetectable detectableLastFm = pointerForLastFaultMode->fmDetectableKeepPow;
		if (detectableLastFm != yes) {
			testScenario.keepPowFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.keepPowFailureScenario);
		}
	}
}

