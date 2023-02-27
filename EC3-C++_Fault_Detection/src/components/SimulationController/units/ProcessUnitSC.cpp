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

	SimulationFileHandler simulationFileHandler(dataMemoryDir, simulationMemoryDir);

	simulationFileHandler.createSimulationFiles(simulationName);

	SimulationSpecificParamsType simulationParams;

	collectNewSimulationParams(simulationParams, simulationName);

	simulationFileHandler.defineSimulationParamsFile(simulationParams, simulationName);
}

void ProcessUnitSC::selectSimulation()
{
	string name;
	cout << endl << "Enter the simulation name to select it" << endl;
	cout << "Input [string]: ";
	cin >> name;

	SimulationFileHandler simulationFileHandler(dataMemoryDir, simulationMemoryDir);
	bool simulationFound = simulationFileHandler.searchForSimulationDirectories(name);

	if (simulationFound) {
		ProcessUnitSC::simulationName = name;
		setSimulationParams();
		supervisorPointer->prepareForSimulation(); // here DataHandler is initialized
	}
	else {
		cout << endl << "Simulation was not found" << endl;
	}
}

void ProcessUnitSC::collectNewSimulationParams(SimulationSpecificParamsType& simulationParams, string simulationName)
{
	ofstream simulationParamsFile;
	string userInput;

	try {
		cout << endl << "2. Enter the supervisor system parameters" << endl;
		cout << "----------------------------------------" << endl;
		cout << "overallSilhouetteTolerance [double type]: ";
		cin >> userInput;
		simulationParams.overallSilhouetteTolerance = stod(userInput);
		cout << "silhouetteDiffTolerance [double type]: ";
		cin >> userInput;
		simulationParams.silhouetteDiffTolerance = stod(userInput);
		cout << "numberOfPointsPerClusterDiffTolerance [integer type]: ";
		cin >> userInput;
		simulationParams.numberOfPointsPerClusterDiffTolerance = stod(userInput);
		cout << "supervisorMaxNumberOfRegisters [positive integer type]: ";
		cin >> userInput;
		simulationParams.maxNumberOfRegisters = stoul(userInput);

		cout << endl << "3. Enter the supervised system parameters" << endl;
		cout << "----------------------------------------" << endl;

		cout << "nominalFuseResultBurn [double type]: " << endl;
		cin >> userInput;
		simulationParams.nominalFuseResultBurn = stod(userInput);
		cout << "nominalFuseResultNotBurn [double type]: " << endl;
		cin >> userInput;
		simulationParams.nominalFuseResultNotBurn = stod(userInput);

		cout << "minNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		simulationParams.minNominalFuseResultBurn = stod(userInput);
		if (simulationParams.minNominalFuseResultBurn > simulationParams.nominalFuseResultBurn) throw invalid_argument("Error: minNominalFuseResultBurn > nominalFuseResultBurn");
		cout << "maxNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		simulationParams.maxNominalFuseResultBurn = stod(userInput);
		if (simulationParams.maxNominalFuseResultBurn < simulationParams.nominalFuseResultBurn) throw invalid_argument("Error: maxNominalFuseResultBurn < nominalFuseResultBurn");
		cout << "minNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		simulationParams.minNominalFuseResultNotBurn = stod(userInput);
		if (simulationParams.minNominalFuseResultNotBurn > simulationParams.nominalFuseResultNotBurn) throw invalid_argument("Error: minNominalFuseResultNotBurn > nominalFuseResultNotBurn");
		cout << "maxNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		simulationParams.maxNominalFuseResultNotBurn = stod(userInput);
		if (simulationParams.maxNominalFuseResultNotBurn < simulationParams.nominalFuseResultNotBurn) throw invalid_argument("Error: maxNominalFuseResultNotBurn < nominalFuseResultNotBurn");

		cout << "maxStdDeviation [double type]: ";
		cin >> userInput;
		simulationParams.maxStdDeviation = stod(userInput);

		cout << endl << "4. Enter the simulation controller parameters" << endl;
		cout << "----------------------------------------" << endl;
		cout << "iteration equivalent time in hours [double type]: ";
		cin >> userInput;
		simulationParams.iterationEquivalentTime = stod(userInput);
		cout << "random generator seed " << endl;
		cout << "obs.: in order to generate a random seed every time"
			<< "a new cycle of iterations starts, enter 'r'" << endl;
		cout << "Input [positive integer type | 'r']: ";
		cin >> userInput;
		if (userInput == "r") {
			simulationParams.simulationSeed = generator.setRandSeed();
			cout << endl << "Random seed generated: " << simulationParams.simulationSeed << endl;
		}
		else simulationParams.simulationSeed = stoul(userInput);
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

test ProcessUnitSC::getNextTestToBePerfomed()
{
	test lastPerfomedTest = supervisorPointer->getLastPerfomedTest();
	if (lastPerfomedTest == keepPowerTest || lastPerfomedTest == none) {
		return fuseTest;
	}

	return keepPowerTest;
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
		SimulationFileHandler simulationFileHandler(dataMemoryDir, simulationMemoryDir);

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
			simulationFileHandler.resetCSVFiles(simulationName);
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

void ProcessUnitSC::avaliateComponentFaultModes(
	Component& component,
	vector<FaultModeAnalysisResultType>& faultModeAnalysisResultArray
)
{
	int faultModeId = 0;
	FaultModeType faultMode;

	FuseTestResultsType fuseTestResult;
	KeepPowerTestResultsType keepPowerTestResult;

	FaultModeAnalysisResultType faultModeAnalysisResult;
	string componentName = component.getComponentName();

	vector<FaultModeType>* faultModesArrayPointer = component.getPointerForFaultModesArray();

	for (FaultModeType& faultMode : *faultModesArrayPointer) {
		failureController.defineTestScenarioForSpecificSingleFaultMode(&faultMode);
		supervisedPointer->setTestScenario(testScenario);

		collectResultsFromSingleIteration(fuseTestResult, keepPowerTestResult);

		collectResultsFromSingleIteration(fuseTestResult, keepPowerTestResult);

		faultModeAnalysisResult = FaultModeAnalysisResultType({
			componentName,
			faultMode,
			fuseTestResult,
			keepPowerTestResult,
			});

		faultModeAnalysisResultArray.push_back(faultModeAnalysisResult);

		supervisorPointer->deleteRecordsFromLatestIteration();

		faultModeId++;
	}
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
	SimulationFileHandler simulationFileHandler(dataMemoryDir, simulationMemoryDir);

	cout << endl << "Reseting simulation..." << endl;
	resetSupervisor();
	resetComponentsOperationalStates();

	simulationFileHandler.resetCSVFiles(simulationName);
	const string faultModesAvaliationsDir = simulationFileHandler.createFaultModesAvaliationDir(simulationName);

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

	vector<FaultModeAnalysisResultType> faultModeAnalysisResultArray;

	for (Component& component : componentsArray) {

		componentJsonDestinyFilePath = simulationFileHandler.createLogFileForComponentAvaliation(
			component.getComponentName(),
			faultModesAvaliationsDir
		);

		// this array contains only the results for a specific component
		faultModeAnalysisResultArray.clear();

		avaliateComponentFaultModes(component, faultModeAnalysisResultArray);

		simulationFileHandler.exportJsonFaultModeAnalysisArray(faultModeAnalysisResultArray, componentJsonDestinyFilePath);
	}

	cout << endl << "Single-failure injection process completed" << endl;
	cout << "Results are available in " << faultModesAvaliationsDir << " directory." << endl;

	supervisorPointer->logFilesConfig(true);
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

	const string simulationDir = simulationsDir + "/" + simulationName;
	IterationRunner iterationRunner(
		supervisorPointer,
		supervisedPointer,
		componentsArray,
		testScenario,
		failureEventsArray,
		iterationPointer,
		simulationDir,
		verboseMode);

	while (duration > 0) {
		if (verboseMode) cout << endl << "Begin of the new iteration " << *iterationPointer + 1 << endl;

		test testName = getNextTestToBePerfomed();

		if (noFailuresMode) failureController.defineTestScenarioWithoutFailure();
		else failureController.defineNewRandomTestScenario(testName);

		supervisedPointer->setTestScenario(testScenario);

		try {
			iterationRunner.runTest();
			duration--;
		}
		catch (exception& excep) {
			duration = 0;
		}
	}

	cout << endl << "Cycle of iterations completed" << endl;

	SimulationFileHandler simulationFileHandler(dataMemoryDir, simulationMemoryDir);
	simulationFileHandler.exportFailureEventsHistoryJson(failureEventsArray, *iterationPointer, simulationName);
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
