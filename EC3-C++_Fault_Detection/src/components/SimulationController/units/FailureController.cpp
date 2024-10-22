#include "../include/FailureController.h"

FailureController::FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode) :
	componentsArray(componentsArray),
	testScenario(testScenario)
{
	FailureController::maxNumberOfFailuresWithImpact = 2;
	FailureController::numberOfFailedComponents = 0;
	FailureController::verboseMode = verboseMode;
	FailureController::failureScenarioFuseTstLocked = false;
	FailureController::failureScenarioKeepPowTstLocked = false;
	FailureController::failuresWithImpactArray = vector<FaultModeType*>();
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
		if (status != noFault) {
			int faultModeId = component.getCurrentFaultModeId();
			FaultModeType* pointerForFaultMode = component.getPointerForFaultMode(faultModeId);
			if (status == newFault) {
				addNewFailureToTestScenario(pointerForFaultMode, nextTestToBePerfomed);
			}

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
	// failure controller is restored to default condition,
	// which means no failure
	reset();
}

void FailureController::defineTestScenarioForSpecificSingleFaultMode(FaultModeType* faultModePointer)
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

void FailureController::setVerboseMode(bool verboseModeValue)
{
	FailureController::verboseMode = verboseModeValue;
}

void FailureController::reset()
{
	numberOfFailedComponents = 0;

	// reset of testScenario for the entire application
	testScenario.numberOfFailedComponents = 0;
	testScenario.detectableFailureGenerated = false;
	testScenario.outsideScopeFailureGenerated = false;
	testScenario.unsafeFailureGenerated = false;
	testScenario.impactlessFailureGenerated = false;
	testScenario.fuseFailureScenarioPointer = nullptr;
	testScenario.keepPowFailureScenarioPointer = nullptr;
	testScenario.newFaultModesArray.clear();
	testScenario.failedComponentsIdArray.clear();

	failureScenarioFuseTstLocked = false;
	failureScenarioKeepPowTstLocked = false;

	failuresWithImpactArray.clear();
}

void FailureController::updateTestScenarioFlags(test performedTest)
{
	FaultModeType* pointerForLastFaultMode = testScenario.newFaultModesArray.back();
	fmDetectable fmDetectable = getFmDetectableForATest(pointerForLastFaultMode, performedTest);
	fmSafety fmSafety = pointerForLastFaultMode->fmSafety;

	if (fmDetectable == yes) testScenario.detectableFailureGenerated = true;
	if (fmDetectable == outsideScope) testScenario.outsideScopeFailureGenerated = true;
	if (fmDetectable == impactless) testScenario.impactlessFailureGenerated = true;
	if (fmSafety == unsafe) testScenario.unsafeFailureGenerated = true;
}

fmDetectable FailureController::getFmDetectableForATest(FaultModeType* pointerForFaultMode, test nextTestToBePerfomed)
{
	if (nextTestToBePerfomed == fuseTest)
		return pointerForFaultMode->fmDetectableFuse;

	return pointerForFaultMode->fmDetectableKeepPow;
}

void FailureController::addNewFailureToTestScenario(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed)
{
	numberOfFailedComponents++;
	testScenario.numberOfFailedComponents = numberOfFailedComponents;

	int failedComponentId = pointerForNewFaultMode->componentId;
	testScenario.newFaultModesArray.push_back(pointerForNewFaultMode);
	testScenario.failedComponentsIdArray.push_back(failedComponentId);

	fmDetectable fmDetectable = getFmDetectableForATest(pointerForNewFaultMode, nextTestToBePerfomed);

	int numberOFFailuresWithImpact = failuresWithImpactArray.size();

	if (numberOFFailuresWithImpact == 0) {
		testScenario.fuseFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.fuseFailureScenario);
		testScenario.keepPowFailureScenarioPointer = &(pointerForNewFaultMode->singleFailureScenario.keepPowFailureScenario);

		if (fmDetectable != impactless) {
			failuresWithImpactArray.push_back(pointerForNewFaultMode);
			classMultipleFaults eqClassNewFm = pointerForNewFaultMode->classMultipleFaults;
			if (eqClassNewFm == cm2) {
				failureScenarioFuseTstLocked = true;
			}

			else if (eqClassNewFm == cm1) {
				failureScenarioKeepPowTstLocked = true;
			}

			else if (eqClassNewFm == cm3) {
				failureScenarioFuseTstLocked = true;
				failureScenarioKeepPowTstLocked = true;
			}
		}
	}

	else if (numberOFFailuresWithImpact < maxNumberOfFailuresWithImpact) {
		if (fmDetectable != impactless) {
			resolveFailureScenarioForMultipleFailuresWithImpact(pointerForNewFaultMode);
			failuresWithImpactArray.push_back(pointerForNewFaultMode);
		}
	}

	else {
		string reasonMsg = " maximum number of failures with impact (" + to_string(maxNumberOfFailuresWithImpact) + ") reached";
		throw ForcedSimulationEndExcep(reasonMsg, nextTestToBePerfomed);
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

void FailureController::resetComponentsOperationalStates()
{
	for (Component& component : componentsArray) {
		component.repair();
	}

	if (verboseMode) cout << "Components restored to normal operational states" << endl;

	reset();
}