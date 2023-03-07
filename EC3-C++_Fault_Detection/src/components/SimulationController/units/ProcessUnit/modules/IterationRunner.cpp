#include "../../../include/IterationRunner.h"

IterationRunner::IterationRunner(
	Supervisor* supervisorPointer,
	Supervised* supervisedPointer,
	vector<Component>& componentsArray,
	TestScenarioType& testScenario,
	vector<FailureEventType>& failureEventsArray,
	int*& iterationPointer,
	string simulationDir,
	bool verboseMode)
	:
	componentsArray(componentsArray),
	iterationPointer(iterationPointer),
	testScenario(testScenario),
	supervisorPointer(supervisorPointer),
	supervisedPointer(supervisedPointer),
	failureEventsArray(failureEventsArray)
{
	IterationRunner::simulationDir = simulationDir;
	IterationRunner::verboseMode = verboseMode;
}

void IterationRunner::runTest()
{
	string failureLog;

	// it indicates whenever there is a failed component or not
	bool noFaults = true;

	bool failureDetected = false;

	// 'noFaults' indicates whenever there is a failed component or not
	noFaults = (testScenario.numberOfFailedComponents == 0);


	if (verboseMode && !noFaults) {
		cout << endl << "TestScenario with failures" << endl;
		cout << "Number of Failed Components: " << testScenario.numberOfFailedComponents << endl;
	}

	test testName = getNextTestToBePerfomed();

	supervisedPointer->setTestScenario(testScenario);

	try {
		supervisorPointer->runTest();
		failureDetected = false;

		if (noFaults) {
			if (verboseMode) cout << endl << "-> No failure in the supervised system. Supervisor didn't detect any fault" << endl;
		}
		else {
			cout << endl << "-> There was a fault in the supervised system"
				<< " but supervisor didn't detect it in " << testStr[testName] << endl;

			updateTestScenarioFlags(testName);
			recordHistoricalFailureLog(noFaults, failureDetected);
			updateFailureEventsArray(failureDetected, testName);

			verifyTestScenarioForSimulationEnd(testName);

		}

	}
	catch (FailureDetectedExcep& excep) {
		failureDetected = true;

		cout << excep.what() << endl;
		if (noFaults) cout << "-> Supervisor identified a failure that doesn't exist (misdiagnose) in " << endl;

		failureLog = excep.getFailureLog();
		updateTestScenarioFlags(testName);
		recordHistoricalFailureLog(noFaults, failureDetected, failureLog);
		updateFailureEventsArray(failureDetected, testName);

		cout << endl << "Simulation finished in " << testStr[testName] << endl;

		throw excep;
	}
	catch (ForcedSimulationEndExcep& excep) {
		cout << excep.what() << endl;

		failureEventsArray.back().forcedEnd = true;

		cout << endl << "Simulation finished in " << testStr[testName] << endl;

		throw excep;
	}

	if (verboseMode) cout << "End of iteration " << *iterationPointer << endl << endl;
}

void IterationRunner::verifyTestScenarioForSimulationEnd(test perfomedTest)
{

	if (testScenario.detectableFailureGenerated) {
		throw ForcedSimulationEndExcep("a supervisor miss on catching a detectable failure", perfomedTest);
	}

	if (testScenario.unsafeFailureGenerated) {
		throw ForcedSimulationEndExcep("an unsafe non-detected failure", perfomedTest);
	}

	if (testScenario.outsideScopeFailureGenerated) {
		throw ForcedSimulationEndExcep("an out-of-scope non-detected failure", perfomedTest);
	}

}

void IterationRunner::recordHistoricalFailureLog(bool noFaults, bool failureDetected, string logError)
{

	if (failureDetected) {

		ofstream simulationDataFile(
			simulationDir + "/HistoricalCaughtFailureMetricsLog.csv",
			std::ios_base::app);

		simulationDataFile << logError;

		simulationDataFile.close();

	}

	if (failureDetected || !noFaults) {

		ofstream simulationDataFile(
			simulationDir + "/AllHistoricalFailureLog.csv",
			std::ios_base::app);

		simulationDataFile << *iterationPointer << ",";

		simulationDataFile << boolStr[!noFaults] << ",";

		simulationDataFile << boolStr[failureDetected] << ",";

		simulationDataFile << testScenario.numberOfFailedComponents << ",";

		if (testScenario.numberOfFailedComponents != 0) simulationDataFile << failedComponentsListString() << ",";
		else simulationDataFile << "None" << ",";

		simulationDataFile << boolStr[testScenario.unsafeFailureGenerated] << ",";
		simulationDataFile << boolStr[testScenario.outsideScopeFailureGenerated] << ",";
		simulationDataFile << boolStr[testScenario.detectableFailureGenerated] << ",";
		simulationDataFile << boolStr[testScenario.impactlessFailureGenerated] << endl;

		simulationDataFile.close();
	}

}

string IterationRunner::failedComponentsListString()
{
	string listStr = "[";
	for (int& failedComponenteId : testScenario.failedComponentsIdArray) {
		listStr = listStr + componentsArray[failedComponenteId].getComponentName() + ";";
	}

	listStr.pop_back();

	listStr = listStr + "]";

	return listStr;
}

test IterationRunner::getNextTestToBePerfomed()
{
	test lastPerfomedTest = supervisorPointer->getLastPerfomedTest();
	if (lastPerfomedTest == keepPowerTest || lastPerfomedTest == none) {
		return fuseTest;
	}

	return keepPowerTest;
}

void IterationRunner::updateFailureEventsArray(bool failureDetected, test testName)
{
	int index = 0;
	FailureEventType failureEvent;

	for (FaultModeType*& newFaultModePointer : testScenario.newFaultModesArray) {
		int iterationOfFailure = componentsArray[newFaultModePointer->componentId].getIterationOnFailure();
		failureEvent.componentName = componentsArray[newFaultModePointer->componentId].getComponentName();
		failureEvent.iterationOnFailure = iterationOfFailure;
		failureEvent.faultMode = *newFaultModePointer;
		failureEvent.iteration = *iterationPointer;
		failureEvent.testName = testName;
		failureEvent.failureDetected = failureDetected;
		failureEvent.fuseTestResults = supervisorPointer->getFuseTestResults();
		failureEvent.keepPowerTestResults = supervisorPointer->getKeepPowerTestResults();
		failureEvent.forcedEnd = false;

		failureEventsArray.push_back(failureEvent);

		if (iterationOfFailure != *iterationPointer) {
			testScenario.newFaultModesArray.erase(testScenario.newFaultModesArray.begin() + index);
		}

		index++;

	}
}

void IterationRunner::updateTestScenarioFlags(test performedTest)
{
	if (testScenario.newFaultModesArray.size() > 0) {
		FaultModeType* pointerForLastFaultMode = testScenario.newFaultModesArray.back();
		fmDetectable fmDetectable = getFmDetectableForATest(pointerForLastFaultMode, performedTest);
		fmSafety fmSafety = pointerForLastFaultMode->fmSafety;

		if (fmDetectable == yes) testScenario.detectableFailureGenerated = true;
		if (fmDetectable == outsideScope) testScenario.outsideScopeFailureGenerated = true;
		if (fmDetectable == impactless) testScenario.impactlessFailureGenerated = true;
		if (fmSafety == unsafe) testScenario.unsafeFailureGenerated = true;
	}
}

fmDetectable IterationRunner::getFmDetectableForATest(FaultModeType* pointerForFaultMode, test nextTestToBePerfomed)
{
	if (nextTestToBePerfomed == fuseTest)
		return pointerForFaultMode->fmDetectableFuse;

	return pointerForFaultMode->fmDetectableKeepPow;
}


