#include "../../../include/MultiFailureRunner.h"

MultiFailureRunner::MultiFailureRunner(
	FailureController& failureController,
	TestScenarioType& testScenario,
	string& simulationName,
	vector<Component>& componentsArray,
	Supervisor* supervisorPointer,
	Supervised* supervisedPointer,
	string dataMemoryDir,
	string simulationMemoryDir,
	bool& verboseMode) :
	failureController(failureController),
	simulationFileHandler(dataMemoryDir, simulationMemoryDir),
	simulationName(simulationName),
	iterationPointer(iterationPointer),
	componentsArray(componentsArray),
	supervisedPointer(supervisedPointer),
	supervisorPointer(supervisorPointer),
	testScenario(testScenario),
	verboseMode(verboseMode)
{
	MultiFailureRunner::simulationsDir = simulationMemoryDir + "/Simulations";
	MultiFailureRunner::injectedFailuresArray = vector<InjectedFailureType>();
}

void MultiFailureRunner::run()
{
	char userOption = 0;

	cout << endl << "Multiple Failure Injection Test" << endl;

	cout << "Data from previous simulation cycles stored in the simulation"
		<< "directory will be lost. \n \n Are you sure you would like to continue ? " << endl;

	cout << endl << "Input [y/n]: ";

	cin.get(userOption);
	if (userOption == '\n') {
		cin.get(userOption);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (userOption == 'y') {
		cout << "Perform an experimental test over pre-determined injected failures. In order to inject a certain failure, "
			<< "enter the related specifications in a new line of the 'InjectedFailuresInput.csv' file following the format below: " << endl;
		cout << "'hitIteration','componentId','faultModeId'" << endl << endl;
		cout << "-> Example: 12,0,50" << endl;
		cout << "Important Note: The failures must be entered in the order correspondent to the hit iterations" << endl;

		cout << "Press 'c' to continue or 'q' to exit" << endl;

		cin.get(userOption);
		if (userOption == '\n') {
			cin.get(userOption);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (userOption == 'c') {
			collectInjectedFailures();
			if (injectedFailuresArray.size() > 0) {
				runSimulationCycleWithInjectedFailures();
			}
		}
	}
}

void MultiFailureRunner::collectInjectedFailures()
{
	fstream injectedFailureFiles;
	string line, word;

	int componentId, faultModeId, hitIteration;
	const string simulationDir = simulationsDir + "/" + simulationName;

	injectedFailureFiles.open(simulationDir + "/InjectedFailuresInput.csv", ios::in);
	if (injectedFailureFiles.fail()) {
		throw SimulatorFailureExcep(
			simulationsDir +
			"/InjectedFailuresInput.csv file could not be accessed",
			"SimulationController.ProcessUnit.MultiFailureRunner");
	}
	// the first line corresponds to the header, so it is ignored
	getline(injectedFailureFiles, line);

	// each subsequent line corresponds to a injected failure
	while (getline(injectedFailureFiles, line)) {
		stringstream strstream(line);

		// the first word of the line is considered to be the hit iteration
		getline(strstream, word, ',');
		hitIteration = stoi(word);

		// the second word of the line is considered to be the componentId
		getline(strstream, word, ',');
		componentId = stoi(word);

		// the third word of the line is considered to be the faultModeId
		getline(strstream, word, ',');
		faultModeId = stoi(word);

		FaultModeType* pointerForInjectedFm = componentsArray[componentId].getPointerForFaultMode(faultModeId);

		InjectedFailureType injectedFailure = { hitIteration, pointerForInjectedFm };

		injectedFailuresArray.push_back(injectedFailure);
	}

	injectedFailureFiles.close();
}

void MultiFailureRunner::runSimulationCycleWithInjectedFailures()
{
	int nextHitIteration;
	test nextTextToBePerfomed;
	const string simulationDir = simulationsDir + "/" + simulationName;
	bool injectionFailureTestEnd = false;

	int* iterationPointer = supervisorPointer->getIterationPointer();

	IterationRunner iterationRunner(
		supervisorPointer,
		supervisedPointer,
		componentsArray,
		testScenario,
		failureEventsArray,
		iterationPointer,
		simulationDir,
		verboseMode);

	restoreDefaultSimulationCondition();

	failureController.defineTestScenarioWithoutFailure();
	supervisedPointer->setTestScenario(testScenario);

	for (InjectedFailureType& injectedFailure : injectedFailuresArray) {
		nextHitIteration = injectedFailure.hitIteration;

		while (*iterationPointer < nextHitIteration - 1) {
			try {
				iterationRunner.runTest();
			}
			catch (exception& exp) {
				cout << endl << "Injection Test finished" << endl;
				injectionFailureTestEnd = true;
				break;
			}
		}

		if (!injectionFailureTestEnd) {
			FaultModeType* pointerForNewFaultMode = injectedFailure.injectedFautMode;
			int componentId = pointerForNewFaultMode->componentId;

			nextTextToBePerfomed = iterationRunner.getNextTestToBePerfomed();

			componentsArray[componentId].setIterationAtFailure(*iterationPointer + 1);
			failureController.addNewFailureToTestScenario(pointerForNewFaultMode, nextTextToBePerfomed);
		}

		else {
			break;
		}

	}

	if (!injectionFailureTestEnd) {
		try {
			iterationRunner.runTest();
		}
		catch (exception& exp) {
			cout << endl << "Injection Test finished" << endl;
		}
	}

	simulationFileHandler.exportFailureEventsHistoryJson(failureEventsArray, *iterationPointer, simulationName);
}

void MultiFailureRunner::restoreDefaultSimulationCondition()
{
	resetSupervisor();
	failureController.resetComponentsOperationalStates();
	simulationFileHandler.createLogAndStatusCSVFiles(simulationName);
	simulationFileHandler.createDataMemoryCSVFiles(simulationName);
}

void MultiFailureRunner::resetSupervisor()
{
	if (supervisorPointer) {
		supervisorPointer->reset();
	}
}
