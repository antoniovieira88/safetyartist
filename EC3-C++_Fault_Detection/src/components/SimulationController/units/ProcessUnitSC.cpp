#include "../include/ProcessUnitSC.h"

ProcessUnitSC::ProcessUnitSC(
	FailureController& failureController,
	ParamsController& paramsController,
	FuseTestScenarioType& testScenario,
	vector<Component>& componentsArray,
	SimulationSpecificParamsType& simulationSpecificParams,
	MtRandEngine& generator,
	string& simulationName,
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	simulationSpecificParams(simulationSpecificParams), nominalFuseResults({ 0.1, 0.9 }),
	simulationName(simulationName), dataMemoryDir(dataMemoryDir),
	simulationsDir(simulationMemoryDir + "/Simulations"),
	defaultComponentsOperationStateFilePath(simulationMemoryDir + "/FailureSpecs_EC3/ComponentsInitialState.csv"),
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
	ProcessUnitSC::nominalFuseResults = supervisedPointer->getNominalFuseResults();
}

void ProcessUnitSC::run()
{
	int duration;
	char userOption = 0;

	while (userOption != 'e') {
		cout << endl << "***********************";
		cout << endl << "EC3 Fault Detection C++";
		cout << endl << "***********************";
		cout << endl << endl << "Main Menu" << endl << endl;
		printVerboseMode();
		if (simulationName != "") {
			cout << "Current selected simulation: '" << simulationName << "'" << endl;
			cout << "Simulation seed: "
				<< simulationSpecificParams.simulationSeed << endl;
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
		cout << " e) Exit program" << endl << endl;

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
		supervisorPointer->prepareForSimulation(name);
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
	// supervised
	double minNominalFuseResultBurn, maxNominalFuseResultBurn,
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

		cout << endl << "3. Enter the supervised system parameters" << endl;
		cout << "-> nominalFuseResultBurn: " << nominalFuseResults[0] << endl;
		cout << "-> nominalFuseResultNotBurn: " << nominalFuseResults[1] << endl;
		cout << "----------------------------------------" << endl;
		cout << "minNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		minNominalFuseResultBurn = stod(userInput);
		if (minNominalFuseResultBurn > nominalFuseResults[0]) throw invalid_argument("Error: minNominalFuseResultBurn > nominalFuseResultBurn");
		cout << "maxNominalFuseResultBurn [double type]: ";
		cin >> userInput;
		maxNominalFuseResultBurn = stod(userInput);
		if (maxNominalFuseResultBurn < nominalFuseResults[0]) throw invalid_argument("Error: maxNominalFuseResultBurn < nominalFuseResultBurn");
		cout << "minNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		minNominalFuseResultNotBurn = stod(userInput);
		if (minNominalFuseResultNotBurn > nominalFuseResults[1]) throw invalid_argument("Error: minNominalFuseResultNotBurn > nominalFuseResultNotBurn");
		cout << "maxNominalFuseResultNotBurn [double type]: ";
		cin >> userInput;
		maxNominalFuseResultNotBurn = stod(userInput);
		if (maxNominalFuseResultNotBurn < nominalFuseResults[1]) throw invalid_argument("Error: maxNominalFuseResultNotBurn < nominalFuseResultNotBurn");
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
		simulationParamsFile << "overallSilhouetteTolerance:" << overallSilhouetteTolerance << endl;
		simulationParamsFile << "silhouetteDiffTolerance:" << silhouetteDiffTolerance << endl;
		simulationParamsFile << "numberOfPointsPerClusterDiffTolerance:" << numberOfPointsPerClusterDiffTolerance << endl;
		simulationParamsFile << "minNominalFuseResultBurn:" << minNominalFuseResultBurn << endl;
		simulationParamsFile << "maxNominalFuseResultBurn:" << maxNominalFuseResultBurn << endl;
		simulationParamsFile << "minNominalFuseResultNotBurn:" << minNominalFuseResultNotBurn << endl;
		simulationParamsFile << "maxNominalFuseResultNotBurn:" << maxNominalFuseResultNotBurn << endl;
		simulationParamsFile << "maxStdDeviation:" << maxStdDeviation << endl;
		simulationParamsFile << "iterationEquivalentTime:" << iterationEquivalentTime << endl;
		simulationParamsFile << "simulationSeed:" << simulationSeed;
		simulationParamsFile.close();
	}
	catch (invalid_argument& error) {
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
	supervisorPointer->setBasicParams(
		simulationSpecificParams.overallSilhouetteTolerance,
		simulationSpecificParams.silhouetteDiffTolerance,
		simulationSpecificParams.numberOfPointsPerClusterDiffTolerance
	);

	supervisedPointer->setMtEngineSrcFile(srcFilesMtEngineStateDir + "/SupervisedMtEngine");
	supervisedPointer->setBasicParams(
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
	fstream simulationDataFile;
	string const dirSM = simulationsDir + "/" + simulationName;

	simulationDataFile.open(dirSM + "/HistoricalCaughtFailureMetricsLog.csv", std::ios::out);
	simulationDataFile << "iteration,metric,tolerance,variation" << endl;
	simulationDataFile.close();

	simulationDataFile.open(dirSM + "/AllHistoricalFailureLog.csv", std::ios::out);
	simulationDataFile << "iteration,failureOccurred,failureCaught,unsafe" << endl;
	simulationDataFile.close();

	simulationDataFile.open(dirSM + "/HistoricalDataFullLog.csv", std::ios::out);
	simulationDataFile << "iteration,input_fuse_test,output_fuse_result" << endl;
	simulationDataFile.close();

	simulationDataFile.open(dirSM + "/HistoricalMetricsFullLog.csv", std::ios::out);
	simulationDataFile << "iteration,silhouette_cluster1,silhouette_cluster2,n_points_cluster1,n_points_cluster2,overall_silhouette1" << endl;
	simulationDataFile.close();

	filesystem::path paramsFileTargetPath(dirSM + "/ComponentsOperationalState.csv");
	filesystem::copy_file(defaultComponentsOperationStateFilePath, paramsFileTargetPath, filesystem::copy_options::overwrite_existing);
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

		if (noFaults)  simulationDataFile << "F" << ",";
		else simulationDataFile << "T" << ",";

		if (failureDetected)  simulationDataFile << "T" << ",";
		else simulationDataFile << "F" << ",";

		simulationDataFile << '-' << endl;
		simulationDataFile.close();
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
	ofstream simulationDataFile;

	string const dirSM = simulationsDir + "/" + simulationName;

	bool success = filesystem::create_directory(dirSM);

	if (success) {
		if (verboseMode) {
			cout << endl << "New simulation output directory successfully created: " << dirSM << endl;
		}
		createLogAndStatusCSVFiles(simulationName);
	}

	string const dirSD = dataMemoryDir + "/" + simulationName;
	success = filesystem::create_directory(dirSD);

	if (success) {
		if (verboseMode) {
			cout << "New simulation output directory successfully created: " << dirSD << endl;
		}

		simulationDataFile.open(dirSD + "/HistoricalData.csv", std::ios::app);
		simulationDataFile.close();

		simulationDataFile.open(dirSD + "/HistoricalMetrics.csv", std::ios::app);
		simulationDataFile.close();
	}
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

void ProcessUnitSC::runSimulationCycle(int duration)
{
	ofstream simulationDataFile;
	string logError;

	bool noFaults = true;

	cout << endl << "New cycle of iterations started" << endl;
	cout << endl << "Current number of faulty components: " << testScenario.numberOfFailedComponents << endl;
	cout << "Duration: from iteration '" << *iterationPointer << "' until '" << *iterationPointer + duration << "'" << endl;
	cout << "Each simulation iteration is equivalent to: " << simulationSpecificParams.iterationEquivalentTime << " hours" << endl;
	cout << "Total time to be simulated: " << simulationSpecificParams.iterationEquivalentTime * (duration - 1) << " hours" << endl;
	cout << endl << "wait until the cycle is completed..." << endl;

	while (duration > 0) {
		bool failureDetected = false;
		logError = "";

		if (verboseMode) cout << endl << "Begin of the new iteration " << *iterationPointer + 1 << endl;

		failureController.defineNewTestScenario();

		noFaults = (testScenario.numberOfFailedComponents == 0);

		supervisedPointer->setFuseTestScenario(testScenario);

		try {
			supervisorPointer->runTest();
			failureDetected = false;
			if (noFaults) cout << endl << "-> No failure in the supervised system. Supervisor didn't detect any fault" << endl;
			else {
				cout << endl << "-> There was a fault in the supervised system"
					<< " but supervisor didn't detect it" << endl;
				recordHistoricalFailureLog(noFaults, failureDetected);
			}
			duration--;
		}
		catch (FailureDetectedExcep& error) {
			failureDetected = true;

			if (verboseMode) cout << error.what() << endl;
			if (noFaults && verboseMode) cout << "-> Supervisor identified a failure that doesn't exist (misdiagnose)" << endl;

			logError = error.getLogError();
			recordHistoricalFailureLog(noFaults, failureDetected, logError);
			duration = 0;
			cout << endl << "Simulation finished: keepPower set off in Fuse Test" << endl;;
		};

	}

	if (verboseMode) {
		cout << "End of iteration " << *iterationPointer << endl;
		cout << " " << endl;
	}
	cout << endl << "Cycle of iterations completed" << endl;
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

	testScenario.numberOfFailedComponents = 0;
}

void ProcessUnitSC::resetSupervisor()
{
	if (supervisorPointer) {
		supervisorPointer->reset();
	}
}

