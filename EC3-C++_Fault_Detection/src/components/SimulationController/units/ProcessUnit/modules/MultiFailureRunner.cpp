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
	MultiFailureRunner::outputFilename = "";
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
		cout << endl << "In order to perform an experimental test over pre-determined injected failures, "
			<< "follow these steps: " << endl << endl;
		cout << "1. Create a new file '[my-test-name]_input.csv' in 'MultipleFaultModesAnalysis/Results' directory."
			<< endl << "-> Example: my-test_input.csv " << endl;
		cout << "2. Insert the csv header 'hitIteration,componentId,faultModeId' in the first line of the file." << endl
			<< "For each failure to be injected, write a new line with the specifications indicated in the header." << endl
			<< "Use commas to separate the information. " << endl;
		cout << "-> Example: 12,0,50" << endl << endl;
		cout << "Important Note: The failures must be entered in the order correspondent to the hit iterations" << endl << endl;

		cout << "Press 'c' if you have accomplished the previous steps or 'q' to exit" << endl;

		cin.get(userOption);
		if (userOption == '\n') {
			cin.get(userOption);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (userOption == 'c') {
			chooseOption();
		}
	}
}

void MultiFailureRunner::chooseOption()
{
	char userOption = 0;
	string testNameInput;

	const string resultsDir = simulationsDir + "/" + simulationName + "/MultipleFaultModesAnalysis/Results";

	cout << endl << "Options available:" << endl;
	cout << " a) Run all the test input files available in 'MultipleFaultModesAnalysis/Results' directory" << endl;
	cout << " b) Run a specific test input file" << endl;
	cout << " c) Cancel operation" << endl;

	cout << "Type an option to continue " << endl;
	cout << "Input: ";

	cin.get(userOption);
	if (userOption == '\n') {
		cin.get(userOption);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (userOption) {
	case 'a':
		runAllTests(resultsDir);
		break;
	case 'b':
		testNameInput = readTestName();
		runSpecificTest(testNameInput + "_input.csv", resultsDir);
		break;
	case 'c':
		cout << "Operation canceled" << endl;
		break;
	default:
		cout << "Invalid option" << endl;
		cout << "Operation canceled" << endl;
		break;
	}
}

void MultiFailureRunner::runAllTests(string srcDir)
{
	vector<string> inputFilesList;

	FileSysHandler::listAllFiles(srcDir, inputFilesList, "(input\\.csv)");

	for (string& inputFilename : inputFilesList) {
		runSpecificTest(inputFilename, srcDir);
	}
}

void MultiFailureRunner::runSpecificTest(string inputFilename, string srcDir)
{
	collectInjectedFailures(inputFilename, srcDir);
	if (injectedFailuresArray.size() > 0) {
		string testName = extractTestName(inputFilename);
		runSimulationCycleWithInjectedFailures(testName);
	}
}

void MultiFailureRunner::collectInjectedFailures(string inputFilename, string srcDir)
{
	fstream injectedFailureFile;
	string line, word;

	int componentId, faultModeId, hitIteration;

	injectedFailuresArray.clear();

	injectedFailureFile.open(srcDir + "/" + inputFilename, ios::in);

	if (injectedFailureFile.fail()) {
		throw SimulatorFailureExcep(
			simulationsDir +
			"/InjectedFailuresInput.csv file could not be accessed",
			"SimulationController.ProcessUnit.MultiFailureRunner");
	}
	// the first line corresponds to the header, so it is ignored
	getline(injectedFailureFile, line);

	// each subsequent line corresponds to a injected failure
	while (getline(injectedFailureFile, line)) {
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

	injectedFailureFile.close();
}

void MultiFailureRunner::runSimulationCycleWithInjectedFailures(string testName)
{
	int nextHitIteration;
	test nextTextToBePerfomed;
	bool injectionFailureTestEnd = false;

	const string outputLogBaseDir = simulationsDir + "/" + simulationName + "/MultipleFaultModesAnalysis/Logs";
	const string outputResultsDir = simulationsDir + "/" + simulationName + "/MultipleFaultModesAnalysis/Results";
	const string outputLogDir = outputLogBaseDir + "/" + testName;

	simulationFileHandler.createMultiFailureOutputLogCSVFiles(outputLogBaseDir, testName);

	int* iterationPointer = supervisorPointer->getIterationPointer();

	failureEventsArray.clear();

	IterationRunner iterationRunner(
		supervisorPointer,
		supervisedPointer,
		componentsArray,
		testScenario,
		failureEventsArray,
		iterationPointer,
		outputLogDir,
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
		for (int i = 0; i < 2; i++) {
			try {
				iterationRunner.runTest();
			}
			catch (exception& exp) {
				break;
			}
		}
	}

	cout << endl << "Injection Test finished" << endl;
	const string outputResultFilePath = outputResultsDir + "/" + testName + "_output.json";
	simulationFileHandler.exportFailureEventsHistoryJson(failureEventsArray, outputResultFilePath);
}

void MultiFailureRunner::restoreDefaultSimulationCondition()
{
	resetSupervisor();
	failureController.resetComponentsOperationalStates();
	simulationFileHandler.resetCSVFiles(simulationName);
}

void MultiFailureRunner::resetSupervisor()
{
	if (supervisorPointer) {
		supervisorPointer->reset();
	}
}

string MultiFailureRunner::readTestName()
{
	string testName;
	cout << endl << "Enter a name correspondent to the desired test" << endl;
	cout << "Input [string]: ";
	cin >> testName;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return testName;
}

string MultiFailureRunner::extractTestName(string inputFilename)
{
	int separatorNameIndex = inputFilename.find('_');
	return inputFilename.substr(0, separatorNameIndex);
}
