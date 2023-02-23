#include "../include/ProcessUnitSC.h"

ProcessUnitSC::ProcessUnitSC(
	FailureController& failureController,
	ParamsController& paramsController,
	TestScenarioType& testScenario,
	vector<Component>& componentsArray,
	SimulationSpecificParamsType& simulationSpecificParams,
	MtRandEngine& generator,
	string& simulationName,
	int*& iterationPointer,
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	simulationSpecificParams(simulationSpecificParams),
	simulationName(simulationName), iterationPointer(iterationPointer),
	dataMemoryDir(dataMemoryDir), simulationMemoryDir(simulationMemoryDir),
	simulationsDir(simulationMemoryDir + "/Simulations"),
	failureController(failureController),
	paramsController(paramsController),
	testScenario(testScenario),
	componentsArray(componentsArray),
	generator(generator)
{
	ProcessUnitSC::supervisorPointer = nullptr;
	ProcessUnitSC::supervisedPointer = nullptr;
	ProcessUnitSC::iterationPointer = nullptr;
	ProcessUnitSC::verboseMode = verboseMode;
	ProcessUnitSC::failureEventsArray = vector<FailureEventType>();

	// load the constant failure specifications: faultRates, componentsList,
	// failureModes, etc.
	initializeParamsController();
}

ProcessUnitSC::~ProcessUnitSC()
{
	if (verboseMode) {
		cout << endl << "Simulation Controller deactivated" << endl;
	}
}

void ProcessUnitSC::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	ProcessUnitSC::supervisorPointer = supervisorPointer;
	ProcessUnitSC::supervisedPointer = supervisedPointer;

	ProcessUnitSC::iterationPointer = supervisorPointer->getIterationPointer();
}

void ProcessUnitSC::run()
{
	int duration;
	char userOption = 0;

	while (userOption != 'g') {
		cout << endl << "***********************";
		cout << endl << "EC3 Fault Detection C++";
		cout << endl << "***********************";
		cout << endl << endl << "Main Menu" << endl << endl;
		printVerboseMode();
		if (simulationName != "") {
			cout << "Current selected simulation: '" << simulationName << "'" << endl;
			cout << "Simulation seed: "
				<< simulationSpecificParams.simulationSeed << endl;
			cout << "Nominal values for FuseResult: " << simulationSpecificParams.nominalFuseResultBurn
				<< " " << simulationSpecificParams.nominalFuseResultNotBurn << endl;
			cout << "Last iteration performed: " << *iterationPointer << endl;
			cout << "Iteration equivalent time: " << simulationSpecificParams.iterationEquivalentTime << " hour(s)" << endl;
			cout << "Current number of faulty components: " << testScenario.numberOfFailedComponents << endl;
		}
		else {
			cout << "Current selected simulation: <None>" << endl;
		}
		cout << endl << "Options available:" << endl;
		cout << " a) Select simulation from SimulationMemory" << endl;
		cout << " b) Run a cycle of iterations in the current selected simulation" << endl;
		cout << " c) Create a new simulation in SimulationMemory" << endl;
		cout << " d) Set verbose mode " << endl;
		cout << " e) Run single failure injection test" << endl;
		cout << " f) Run multiple failure injection test" << endl;
		cout << " g) Exit program" << endl << endl;

		cout << "Type an option to continue: " << endl;
		cout << "Input: ";

		cin.get(userOption);
		if (userOption == '\n') {
			cin.get(userOption);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (userOption)
		{
		case 97:
			// option a)
			try {
				selectSimulation();
			}
			catch (AbortSimulationOpExcep& error) {
				cout << endl << error.what() << endl;
			}
			break;
		case 98:
			// option b)
			if (simulationName != "") {
				try {
					duration = userSimulationCycleParamsOptions();
					if (duration > 0) {
						runSimulationCycle(duration);
						getReadyForNextSimulationCycle();
					}
				}
				catch (AbortSimulationOpExcep& error) {
					cout << endl << error.what() << endl;
				}

			}
			else {
				cout << endl << "Operation aborted. Error: You must select a simulation first." << endl;
			}
			break;
		case 99:
			// option c)
			try {
				createNewSimulation();
			}
			catch (AbortSimulationOpExcep& error) {
				cout << endl << error.what() << endl;
			}
			break;
		case 100:
			// option d)
			chooseVerboseMode();
			break;
		case 101:
			// option e)
			if (simulationName != "") {
				try {
					singleFailureInjectionOption();
				}
				catch (AbortSimulationOpExcep& error) {
					cout << endl << error.what() << endl;
				}

			}
			else {
				cout << endl << "Operation aborted. Error: You must select a simulation first." << endl;
			}
			break;
		case 102:
			// option f)
			multipleFailuresTestOption();
			break;
		case 103:
			// option g)
			cout << endl << "Exiting program..." << endl;
			break;
		default:
			cout << endl << "Invalid option" << endl;
			break;
		}
	}
}

void ProcessUnitSC::updateFailureEventsArray(bool failureDetected, test testName)
{
	FailureEventType failureEvent;
	for (FaultModeType*& newFaultModePointer : testScenario.newFaultModesArray) {

		failureEvent.componentName = componentsArray[newFaultModePointer->componentId].getComponentName();
		failureEvent.faultMode = *newFaultModePointer;
		failureEvent.iteration = *iterationPointer;
		failureEvent.testName = testName;
		failureEvent.failureDetected = failureDetected;
		failureEvent.fuseTestResults = supervisorPointer->getFuseTestResults();
		failureEvent.keepPowerTestResults = supervisorPointer->getKeepPowerTestResults();

		failureEventsArray.push_back(failureEvent);
	}

	testScenario.newFaultModesArray.clear();
}

void ProcessUnitSC::chooseVerboseMode()
{
	char userInput;
	cout << endl << "Verbose mode options:" << endl;
	cout << "0 - Set to 'False'" << endl;
	cout << "1 - Set to 'True'" << endl;
	cout << "Type an option to continue: " << endl;
	cout << "Input: ";
	cin.get(userInput);
	if (userInput == '\n') {
		cin.get(userInput);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (userInput)
	{
	case 48:
		setVerboseMode(false);
		break;
	case 49:
		setVerboseMode(true);
		break;
	default:
		cout << endl << "Invalid option" << endl;
		break;
	}
}

void ProcessUnitSC::createNewSimulation()
{
	string simulationName;
	cout << "Creation of a new simulation" << endl;
	cout << "Simulations always starts from the default initial conditions: no failures and reliability equals 1." << endl;
	cout << endl << "1. Enter the simulation name." << endl;
	cout << "----------------------------------------" << endl;
	cout << "Warning: new directories for the referred simulation will be created in '"
		<< simulationsDir << "' and '"
		<< dataMemoryDir << "' with the informed name. "
		<< "Avoid entering a simulation name that already exists."
		<< endl;
	cout << "Input [string]: ";
	cin >> simulationName;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	createSimulationFiles(simulationName);
	createSimulationParams(simulationName);
}

void ProcessUnitSC::selectSimulation()
{
	string name;
	cout << endl << "Enter the simulation name to select it" << endl;
	cout << "Input [string]: ";
	cin >> name;

	bool simulationFound = searchForSimulationDirectories(name);

	if (simulationFound) {
		ProcessUnitSC::simulationName = name;
		setSimulationParams();
		supervisorPointer->prepareForSimulation(); // here DataHandler is initialized
	}
	else {
		cout << endl << "Simulation was not found" << endl;
	}
}

void ProcessUnitSC::createSimulationParams(string simulationName)
{
	ofstream simulationParamsFile;
	string userInput;

	// supervisor
	double overallSilhouetteTolerance, silhouetteDiffTolerance,
		numberOfPointsPerClusterDiffTolerance;
	unsigned int maxNumberOfRegisters;
	// supervised
	double nominalFuseResultBurn, nominalFuseResultNotBurn,
		minNominalFuseResultBurn, maxNominalFuseResultBurn,
		minNominalFuseResultNotBurn, maxNominalFuseResultNotBurn,
		maxStdDeviation;
	// simulation controller
	unsigned int simulationSeed;
	double iterationEquivalentTime;

	try {
		cout << endl << "2. Enter the supervisor system parameters" << endl;
		cout << "----------------------------------------" << endl;
		cout << "overallSilhouetteTolerance [double type]: ";
		cin >> userInput;
		overallSilhouetteTolerance = stod(userInput);
		cout << "silhouetteDiffTolerance [double type]: ";
		cin >> userInput;
		silhouetteDiffTolerance = stod(userInput);
		cout << "numberOfPointsPerClusterDiffTolerance [integer type]: ";
		cin >> userInput;
		numberOfPointsPerClusterDiffTolerance = stod(userInput);
		cout << "supervisorMaxNumberOfRegisters [positive integer type]: ";
		cin >> userInput;
		maxNumberOfRegisters = stoul(userInput);

		cout << endl << "3. Enter the supervised system parameters" << endl;
		cout << "----------------------------------------" << endl;

		cout << "nominalFuseResultBurn [double type]: " << endl;
		cin >> userInput;
		nominalFuseResultBurn = stod(userInput);
		cout << "nominalFuseResultNotBurn [double type]: " << endl;
		cin >> userInput;
		nominalFuseResultNotBurn = stod(userInput);

		cout << "minNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		minNominalFuseResultBurn = stod(userInput);
		if (minNominalFuseResultBurn > nominalFuseResultBurn) throw invalid_argument("Error: minNominalFuseResultBurn > nominalFuseResultBurn");
		cout << "maxNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		maxNominalFuseResultBurn = stod(userInput);
		if (maxNominalFuseResultBurn < nominalFuseResultBurn) throw invalid_argument("Error: maxNominalFuseResultBurn < nominalFuseResultBurn");
		cout << "minNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		minNominalFuseResultNotBurn = stod(userInput);
		if (minNominalFuseResultNotBurn > nominalFuseResultNotBurn) throw invalid_argument("Error: minNominalFuseResultNotBurn > nominalFuseResultNotBurn");
		cout << "maxNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		maxNominalFuseResultNotBurn = stod(userInput);
		if (maxNominalFuseResultNotBurn < nominalFuseResultNotBurn) throw invalid_argument("Error: maxNominalFuseResultNotBurn < nominalFuseResultNotBurn");

		cout << "maxStdDeviation [double type]: ";
		cin >> userInput;
		maxStdDeviation = stod(userInput);

		cout << endl << "4. Enter the simulation controller parameters" << endl;
		cout << "----------------------------------------" << endl;
		cout << "iteration equivalent time in hours [double type]: ";
		cin >> userInput;
		iterationEquivalentTime = stod(userInput);
		cout << "random generator seed " << endl;
		cout << "obs.: in order to generate a random seed every time"
			<< "a new cycle of iterations starts, enter 'r'" << endl;
		cout << "Input [positive integer type | 'r']: ";
		cin >> userInput;
		if (userInput == "r") {
			simulationSeed = generator.setRandSeed();
			cout << endl << "Random seed generated: " << simulationSeed << endl;
		}
		else simulationSeed = stoul(userInput);

		simulationParamsFile.open(simulationsDir + "/" + simulationName + "/SimulationParams.csv", std::ios::app);

		// header of the file
		simulationParamsFile << "parameter,value" << endl;

		// Supervisor (doubles)
		simulationParamsFile << "overallSilhouetteTolerance," << overallSilhouetteTolerance << endl;
		simulationParamsFile << "silhouetteDiffTolerance," << silhouetteDiffTolerance << endl;
		simulationParamsFile << "numberOfPointsPerClusterDiffTolerance," << numberOfPointsPerClusterDiffTolerance << endl;
		// Supervised (doubles)
		simulationParamsFile << "nominalFuseResultBurn," << nominalFuseResultBurn << endl;
		simulationParamsFile << "nominalFuseResultNotBurn," << nominalFuseResultNotBurn << endl;
		simulationParamsFile << "minNominalFuseResultBurn," << minNominalFuseResultBurn << endl;
		simulationParamsFile << "maxNominalFuseResultBurn," << maxNominalFuseResultBurn << endl;
		simulationParamsFile << "minNominalFuseResultNotBurn," << minNominalFuseResultNotBurn << endl;
		simulationParamsFile << "maxNominalFuseResultNotBurn," << maxNominalFuseResultNotBurn << endl;
		simulationParamsFile << "maxStdDeviation," << maxStdDeviation << endl;
		// Simulation Controller (doubles)
		simulationParamsFile << "iterationEquivalentTime," << iterationEquivalentTime << endl;
		// integers
		simulationParamsFile << "simulationSeed," << simulationSeed << endl;
		simulationParamsFile << "supervisorMaxNumberOfRegisters," << maxNumberOfRegisters;

		simulationParamsFile.close();
	}
	catch (invalid_argument& error) {
		// undo the creation of the simulation directories if any parameter is entered in invalid format
		filesystem::remove_all(simulationsDir + "/" + simulationName);
		filesystem::remove_all(dataMemoryDir + "/" + simulationName);
		cout << endl << error.what() << endl;
		cout << "Simulation directories for " + simulationName + " deleted" << endl;
		throw AbortSimulationOpExcep("Invalid simulation parameter entered: " + userInput + ".\n");

	}
}

void ProcessUnitSC::setSimulationParams()
{
	// set the parameters in the simulation controller (update
	// the values stored in 'simulationSpecificParams' struct)
	loadSimulation();
	// set the simulation controller current state 
	testScenario.numberOfFailedComponents = paramsController.setComponentsInitialOperationalState();
	string srcFilesMtEngineStateDir = simulationsDir + "/" + simulationName;
	generator.setFileDir(srcFilesMtEngineStateDir + "/SimulationControllerMtEngine");
	generator.seed(simulationSpecificParams.simulationSeed);

	// update the collected parameters in the other units

	// supervisor
	supervisorPointer->setBasicParams(
		simulationSpecificParams.nominalFuseResultBurn,
		simulationSpecificParams.nominalFuseResultNotBurn,
		simulationSpecificParams.overallSilhouetteTolerance,
		simulationSpecificParams.silhouetteDiffTolerance,
		simulationSpecificParams.numberOfPointsPerClusterDiffTolerance,
		simulationSpecificParams.maxNumberOfRegisters,
		simulationName
	);

	// supervised
	supervisedPointer->setMtEngineSrcFile(srcFilesMtEngineStateDir + "/SupervisedMtEngine");
	supervisedPointer->setBasicParams(
		simulationSpecificParams.nominalFuseResultBurn,
		simulationSpecificParams.nominalFuseResultNotBurn,
		simulationSpecificParams.minNominalFuseResultBurn,
		simulationSpecificParams.maxNominalFuseResultBurn,
		simulationSpecificParams.minNominalFuseResultNotBurn,
		simulationSpecificParams.maxNominalFuseResultNotBurn,
		simulationSpecificParams.maxStdDeviation,
		10 * simulationSpecificParams.simulationSeed
	);
}

void ProcessUnitSC::createLogAndStatusCSVFiles(string simulationName)
{
	string const dirSM = simulationsDir + "/" + simulationName;
	string const dirSpecs = simulationMemoryDir + "/FailureSpecs_EC3";

	FileSysHandler::createCSVFile(
		"InjectedFailuresInput",
		dirSM,
		{ "hitIteration", "componentId", "failureId" });

	FileSysHandler::createCSVFile(
		"HistoricalCaughtFailureMetricsLog",
		dirSM,
		{ "iteration", "testName", "metric", "tolerance", "variation" });

	FileSysHandler::createCSVFile(
		"AllHistoricalFailureLog",
		dirSM,
		{ "iteration", "failureOccurred", "failureCaught", "numberOfFailedComponents", "failedComponentsList",
		"unsafeFailureGenerated", "outsideScopeFailureGenerated",
		"detectableFailureGenerated", "impactlessFailureGenerated" });

	FileSysHandler::createCSVFile(
		"HistoricalDataFullLog",
		dirSM + "/FuseTest",
		{ "iteration", "fuseTest", "fuseResult" });
	FileSysHandler::createCSVFile(
		"HistoricalDataFullLog",
		dirSM + "/KeepPowerTest",
		{ "iteration", "keepPower", "keepPowerReadback" });


	FileSysHandler::createCSVFile(
		"HistoricalMetricsFullLog",
		dirSM + "/FuseTest",
		{ "iteration", "silhouetteCluster1", "silhouetteCluster2", "numPointsCluster1", "numPointsCluster2", "overallSilhouette" });
	FileSysHandler::createCSVFile(
		"HistoricalMetricsFullLog",
		dirSM + "/KeepPowerTest",
		{ "iteration", "numPointsCluster1", "numPointsCluster2" });

	FileSysHandler::copyFileOverwrite("ComponentsInitialState.csv", "ComponentsOperationalState.csv", dirSpecs, dirSM);
}

void ProcessUnitSC::createDataMemoryCSVFiles(string simulationName)
{
	const string fuseTestDir = dataMemoryDir + "/" + simulationName + "/FuseTest";

	FileSysHandler::createCSVFile("HistoricalMetrics", fuseTestDir);
	FileSysHandler::createCSVFile("HistoricalData", fuseTestDir);

	const string keepPowerTestDir = dataMemoryDir + "/" + simulationName + "/KeepPowerTest";

	FileSysHandler::createCSVFile("HistoricalMetrics", keepPowerTestDir);
	FileSysHandler::createCSVFile("HistoricalData", keepPowerTestDir);
}

void ProcessUnitSC::printVerboseMode()
{
	cout << "Verbose mode: ";
	if (verboseMode) {
		cout << "'True'" << endl;
	}
	else {
		cout << "'False'" << endl;
	}
}

void ProcessUnitSC::recordHistoricalFailureLog(bool noFaults, bool failureDetected, string logError)
{
	string dir = simulationsDir + "/" + (simulationName)+"/";

	if (failureDetected) {

		ofstream simulationDataFile(
			dir + "HistoricalCaughtFailureMetricsLog.csv",
			std::ios_base::app);

		simulationDataFile << logError;

		simulationDataFile.close();

	}

	if (failureDetected || !noFaults) {

		ofstream simulationDataFile(
			dir + "AllHistoricalFailureLog.csv",
			std::ios_base::app);

		simulationDataFile << *iterationPointer << ",";

		simulationDataFile << boolStr[noFaults] << ",";

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

string ProcessUnitSC::failedComponentsListString()
{
	string listStr = "[";
	for (int& failedComponenteId : testScenario.failedComponentsIdArray) {
		listStr = listStr + componentsArray[failedComponenteId].getComponentName() + ";";
	}

	listStr.pop_back();

	listStr = listStr + "]";

	return listStr;
}

string ProcessUnitSC::createLogFileForComponentAvaliation(string componentName, string faultModesAvaliationsDir)
{
	string filename = componentName + "_AnalysisResult";
	return FileSysHandler::createJsonFile(filename, faultModesAvaliationsDir);
}

string ProcessUnitSC::createFaultModesAvaliationDir()
{
	const string faultModesAvaliationsBaseDir = simulationsDir + "/" + simulationName;
	FileSysHandler::createDirectories(faultModesAvaliationsBaseDir, { "FaultModesAnalysis" });
	return faultModesAvaliationsBaseDir + "/FaultModesAnalysis";
}

void ProcessUnitSC::collectResultsFromSingleIteration(FuseTestResultsType& fuseTestResult, KeepPowerTestResultsType& keepPowerTestResult)
{
	try {
		supervisorPointer->runTest();
	}
	catch (exception& error) {};

	test lastPerfomedTest = supervisorPointer->getLastPerfomedTest();

	if (lastPerfomedTest == fuseTest) {
		fuseTestResult = supervisorPointer->getFuseTestResults();
	}
	else {
		keepPowerTestResult = supervisorPointer->getKeepPowerTestResults();
	}
}

void ProcessUnitSC::exportJsonFaultModeAnalysisArray(vector<FaultModeAnalysisResultType>& faultModeDataArray, string destinyFilePath)
{
	json faultModeDataJson = json(faultModeDataArray);

	ofstream simulationJsonDataFile(
		destinyFilePath,
		std::ios_base::out);

	simulationJsonDataFile << faultModeDataJson.dump(4, ' ');

	simulationJsonDataFile.close();

}

test ProcessUnitSC::getNextTestToBePerfomed()
{
	test lastPerfomedTest = supervisorPointer->getLastPerfomedTest();
	if (lastPerfomedTest == keepPowerTest || lastPerfomedTest == none) {
		return fuseTest;
	}

	return keepPowerTest;
}

void ProcessUnitSC::verifyTestScenarioForSimulationEnd(test perfomedTest)
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

void ProcessUnitSC::exportFailureEventsHistoryJson()
{
	json failureEventsHistoryJson = json(failureEventsArray);
	const string destinyFilePath = simulationsDir + "/" + simulationName +
		"/FailureEventsHistory" + to_string(*iterationPointer) + ".json";

	ofstream simulationJsonDataFile(
		destinyFilePath,
		std::ios_base::out);

	simulationJsonDataFile << failureEventsHistoryJson.dump(4, ' ');

	simulationJsonDataFile.close();
}

void ProcessUnitSC::multipleFailuresTestOption()
{
	if (simulationName != "") {
		MultiFailureRunner multiFailureRunner(
			failureController,
			testScenario,
			simulationName,
			componentsArray,
			supervisorPointer,
			supervisedPointer,
			dataMemoryDir,
			simulationMemoryDir,
			verboseMode);

		multiFailureRunner.run();
	}

	else {
		cout << endl << "Operation aborted. Error: You must select a simulation first." << endl;
	}

}

int ProcessUnitSC::userSimulationCycleParamsOptions() {
	int duration = 0;
	bool exit = false;
	string userInput;
	char userOption;

	if (*iterationPointer > 0) {
		cout << endl << "Previous results from '" + simulationName + "' were found" << endl;
		cout << endl << "Would you like to perform a new cycle of iterations starting from iteration " << *iterationPointer << "?" << endl;
		cout << "Options: "
			<< endl << " a) continue from last performed iteration"
			<< endl << " b) reset the simulation"
			<< endl << " c) cancel operation" << endl;
		cout << "Warning: the restart of the simulation will cause the deletion of all the current data stored in 'DataMemory/"
			<< simulationName << "' and the log files present in 'SimulationMemory/" << simulationName << "'" << endl;
		cout << "Type an option to continue: " << endl;
		cout << "Input: ";

		cin.get(userOption);
		if (userOption == '\n') {
			cin.get(userOption);
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (userOption)
		{
		case 97:
			// option a)
			loadMtRandEngines();
			cout << endl << "Simulation " + simulationName
				<< " will later continue from iteration "
				<< *iterationPointer << endl;
			break;
		case 98:
			// option b)
			cout << endl << "Simulation restarting..." << endl;
			resetSupervisor();
			resetComponentsOperationalStates();
			createLogAndStatusCSVFiles(simulationName);
			createDataMemoryCSVFiles(simulationName);
			break;
		case 99:
			// option c)
			cout << endl << "Operation canceled" << endl;
			exit = true;
			break;
		default:
			cout << endl << "Invalid Option" << endl;
			cout << "Operation canceled" << endl;
			exit = true;
			break;
		}
	}

	if (!exit) {
		try {
			cout << "Set the number of new iterations (N) to be performed in this cycle"
				<< "(starting from " << *iterationPointer << ")" << endl;
			cout << "obs.: the total duration of the new cycle will be (N - 1) x "
				<< simulationSpecificParams.iterationEquivalentTime << " hours" << endl;
			cout << "Input [integer type]: ";
			cin >> userInput;
			duration = stoi(userInput);
			cout << endl << endl;
		}
		catch (invalid_argument& error) {
			throw AbortSimulationOpExcep("Invalid number of iterations entered: " + userInput + ".\n");
		}
	}

	return duration;
}

void ProcessUnitSC::getReadyForNextSimulationCycle()
{
	supervisorPointer->getReadyForNextSimulationCycle();
	paramsController.updateComponentsOperationalStateFile();
	saveMtRandEngines();
}

void ProcessUnitSC::loadMtRandEngines()
{
	generator.loadState(verboseMode);
	supervisedPointer->loadMtEngineState();
}

void ProcessUnitSC::saveMtRandEngines()
{
	if (simulationSpecificParams.simulationSeed >= 0) {
		generator.saveState(verboseMode);
		supervisedPointer->saveMtEngineState();
	}
}

void ProcessUnitSC::createSimulationFiles(string simulationName)
{

	const string relativeDirFuseTest = simulationName + "/FuseTest";
	const string relativeDirKeepPowerTest = simulationName + "/KeepPowerTest";

	bool success = FileSysHandler::createDirectories(simulationsDir, { relativeDirFuseTest, relativeDirKeepPowerTest });

	if (success) {
		if (verboseMode) {
			cout << endl << "New simulation output directories successfully created" << endl;
		}

		createLogAndStatusCSVFiles(simulationName);
	}

	success = FileSysHandler::createDirectories(dataMemoryDir, { relativeDirFuseTest, relativeDirKeepPowerTest });


	if (success) {
		if (verboseMode) {
			cout << "New data memory output directories successfully created" << endl;
		}

		createDataMemoryCSVFiles(simulationName);
	}
}

void ProcessUnitSC::avaliateComponentFaultModes(Component& component, string componentJsonDestinyFilePath)
{
	int faultModeId = 0;
	FaultModeType faultMode;

	FuseTestResultsType fuseTestResult;
	KeepPowerTestResultsType keepPowerTestResult;

	FaultModeAnalysisResultType faultModeAnalysisResult;
	vector<FaultModeAnalysisResultType> faultModeAnalysisResultArray;

	vector<FaultModeType>* faultModesArrayPointer = component.getPointerForFaultModesArray();

	for (FaultModeType& faultMode : *faultModesArrayPointer) {
		failureController.defineTestScenarioForSpecificSingleFaultMode(&faultMode);
		supervisedPointer->setTestScenario(testScenario);

		collectResultsFromSingleIteration(fuseTestResult, keepPowerTestResult);

		collectResultsFromSingleIteration(fuseTestResult, keepPowerTestResult);

		faultModeAnalysisResult = FaultModeAnalysisResultType({
			faultMode,
			fuseTestResult,
			keepPowerTestResult,
			});

		faultModeAnalysisResultArray.push_back(faultModeAnalysisResult);

		supervisorPointer->deleteRecordsFromLatestIteration();

		faultModeId++;
	}

	exportJsonFaultModeAnalysisArray(faultModeAnalysisResultArray, componentJsonDestinyFilePath);
}

void ProcessUnitSC::singleFailureInjectionOption()
{
	char userOption = 0;

	cout << endl << "Single Failure Injection Test" << endl;

	int duration = simulationSpecificParams.maxNumberOfRegisters - 2;

	cout << "All fault modes of each component is about to be tested individually over a non-faulty "
		<< duration << "-register database. Data from previous simulation cycles stored in the under test"
		<< "directory will be lost. \n \n Are you sure you would like to continue ? " << endl;


	cout << endl << "Input [y/n]: ";

	cin.get(userOption);
	if (userOption == '\n') {
		cin.get(userOption);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (userOption == 'y') {
		singleFailureInjectionTest();
	}
}

void ProcessUnitSC::singleFailureInjectionTest()
{
	string componentJsonDestinyFilePath;
	int duration = simulationSpecificParams.maxNumberOfRegisters - 2;

	cout << endl << "Reseting simulation..." << endl;
	resetSupervisor();
	resetComponentsOperationalStates();
	createLogAndStatusCSVFiles(simulationName);

	const string faultModesAvaliationsDir = createFaultModesAvaliationDir();

	cout << endl << "Results from Single Failure Injection Test will be available in "
		<< faultModesAvaliationsDir << " directory." << endl;

	setVerboseMode(false);

	cout << "Cycle of " << duration << "-non-faulty iterations starting..." << endl;

	runSimulationCycle(duration, true);
	getReadyForNextSimulationCycle();

	supervisorPointer->logFilesConfig(false);

	cout << "Cycle of " << duration << "-non-faulty iterations completed" << endl;

	cout << endl << "Single-failure injection process started" << endl;
	cout << "Wait until all possible fault modes had been tested." << endl;

	for (Component& component : componentsArray) {

		componentJsonDestinyFilePath = createLogFileForComponentAvaliation(
			component.getComponentName(),
			faultModesAvaliationsDir
		);

		avaliateComponentFaultModes(component, componentJsonDestinyFilePath);
	}

	cout << endl << "Single-failure injection process completed" << endl;
	cout << "Results are available in " << faultModesAvaliationsDir << " directory." << endl;

	supervisorPointer->logFilesConfig(true);
}

bool ProcessUnitSC::searchForSimulationDirectories(string simulationName)
{
	string dirSM = simulationsDir + "/" + simulationName;
	string dirSD = dataMemoryDir + "/" + simulationName;
	bool dirsFound = filesystem::exists(dirSM) && filesystem::exists(dirSD);

	return dirsFound;
}

// load the simulation specific params 
// (supervisor params, supervised params, simulationSeed
// and iterationEquivalentTime) to the 'simulationSpecificParams' struct
void ProcessUnitSC::loadSimulation()
{
	try {
		paramsController.loadSimulationSpecificParams();
	}
	catch (AbortSimulationOpExcep& error) {
		simulationName = "";
		throw;
	}
}

void ProcessUnitSC::setVerboseMode(bool verboseModeValue)
{
	ProcessUnitSC::verboseMode = verboseModeValue;
	paramsController.setVerboseMode(verboseModeValue);
	failureController.setVerboseMode(verboseModeValue);
	supervisorPointer->setVerboseMode(verboseModeValue);
}

void ProcessUnitSC::runSimulationCycle(int duration, bool noFailuresMode)
{
	ofstream simulationDataFile;
	string failureLog;

	// it indicates whenever there is a failed component or not
	bool noFaults = true;

	cout << endl << "New cycle of iterations started" << endl;
	cout << endl << "Current number of faulty components: " << testScenario.numberOfFailedComponents << endl;
	cout << "Duration: from iteration '" << *iterationPointer << "' until '" << *iterationPointer + duration << "'" << endl;
	cout << "Each simulation iteration is equivalent to: " << simulationSpecificParams.iterationEquivalentTime << " hours" << endl;
	cout << "Total time to be simulated: " << simulationSpecificParams.iterationEquivalentTime * (duration - 1) << " hours" << endl;
	cout << endl << "wait until the cycle is completed..." << endl;

	while (duration > 0) {
		bool failureDetected = false;
		failureLog = "";

		if (verboseMode) cout << endl << "Begin of the new iteration " << *iterationPointer + 1 << endl;

		test testName = getNextTestToBePerfomed();

		if (noFailuresMode) failureController.defineTestScenarioWithoutFailure();
		else failureController.defineNewRandomTestScenario(testName);

		// 'noFaults' indicates whenever there is a failed component or not
		noFaults = (testScenario.numberOfFailedComponents == 0);

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

				recordHistoricalFailureLog(noFaults, failureDetected);
				updateFailureEventsArray(failureDetected, testName);

				verifyTestScenarioForSimulationEnd(testName);

			}

			duration--;
		}
		catch (FailureDetectedExcep& excep) {
			failureDetected = true;

			cout << excep.what() << endl;
			if (noFaults) cout << "-> Supervisor identified a failure that doesn't exist (misdiagnose) in " << endl;

			failureLog = excep.getFailureLog();
			recordHistoricalFailureLog(noFaults, failureDetected, failureLog);
			updateFailureEventsArray(failureDetected, testName);

			duration = 0;
			cout << endl << "Simulation finished in " << testStr[testName] << endl;
		}
		catch (ForcedSimulationEndExcep& excep) {
			cout << excep.what() << endl;
			updateFailureEventsArray(failureDetected, testName);
			duration = 0;
			cout << endl << "Simulation finished in " << testStr[testName] << endl;
		}

		if (verboseMode) cout << "End of iteration " << *iterationPointer << endl << endl;

	}

	cout << endl << "Cycle of iterations completed" << endl;
	exportFailureEventsHistoryJson();
}

void ProcessUnitSC::initializeParamsController()
{
	paramsController.loadFailureSpecs();
}

void ProcessUnitSC::resetComponentsOperationalStates()
{
	for (Component& component : componentsArray) {
		component.repair();
	}

	if (verboseMode) cout << "Components restored to normal operational states" << endl;

	failureController.reset();
}

void ProcessUnitSC::resetSupervisor()
{
	if (supervisorPointer) {
		supervisorPointer->reset();
	}
}
