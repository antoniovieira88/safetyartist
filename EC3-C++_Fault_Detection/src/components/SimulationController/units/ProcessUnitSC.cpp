#include "../include/ProcessUnitSC.h"

using namespace std;

ProcessUnitSC::ProcessUnitSC(
	FailureController& failureController,
	ParamsController& paramsController,
	TestScenarioType& testScenario,
	vector<Component>& componentsArray,
	double simulationStep,
	bool verboseMode)
	:
	failureController(failureController),
	paramsController(paramsController),
	testScenario(testScenario),
	componentsArray(componentsArray)

{
	ProcessUnitSC::supervisorPointer = nullptr;
	ProcessUnitSC::supervisedPointer = nullptr;
	ProcessUnitSC::iterationPointer = nullptr;
	ProcessUnitSC::verboseMode = verboseMode;
	ProcessUnitSC::simulationStep = simulationStep;

	initializeParamsController();
}

ProcessUnitSC::~ProcessUnitSC()
{
	paramsController.updateComponentsOperationalStateFile();

	if (verboseMode) {
		cout << endl << "Simulation Controller deactivated" << endl;
		cout << "ComponentsOperationalState.csv file updated in data memory" << endl;
	}
}

void ProcessUnitSC::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	ProcessUnitSC::supervisorPointer = supervisorPointer;
	ProcessUnitSC::supervisedPointer = supervisedPointer;

	ProcessUnitSC::iterationPointer = supervisorPointer->getIterationPointer();
}

void ProcessUnitSC::initialUserOptions()
{
	string userInput;
	if (*iterationPointer > 0) {
		cout << "Previous iterations were found in DataMemory" << endl;
		cout << "Last iteration: " << *iterationPointer << endl;
		cout << "Current operational states of the components: " << endl;
		for (Component& component : componentsArray) {
			cout << " - " << component.getComponentName() << endl;
			cout << "  Fault  Mode = " << component.getCurrentFaultModeName() << endl;
			cout << "  Reliability = " << component.getReliability() << endl;
		}
		cout << endl << "Would you like to continue from the last iteration recorded?" << endl;
		cout << "If not, a new simulation will start from the default initial conditions (no failures and reliability = 1)." << endl;
		cout << "Warning: the start of a new simulation will cause the deletion of all data stored in HistoricalData.csv and HistoricalMetrics.csv." << endl;
		cout << "Input [y/n]: ";
		cin >> userInput;
		if (userInput == "n") {
			cout << endl << "Simulation restarted" << endl;
			resetSupervisor();
			resetComponentsOperationalStates();
		}
		else {
			cout << endl << "Simulation continues from iteration " << *iterationPointer << endl;
		}
	}
	else {

		cout << "No previous iterations were found in DataMemory" << endl;
		cout << endl << "A new simulation will start from the default initial conditions (no failures and reliability = 1)" << endl;
		cout << "Would you like to continue?" << endl;
		cout << "Input [y/n]: ";
		cin >> userInput;
		if (userInput == "n") {
			exit(EXIT_SUCCESS);
		}
		else if (paramsController.isSurpervisedStartingWithFailure()) {
			// it checks if components were initialized with failures by ComponentsOperationalState.csv.
			// In this case, since the default initial conditions consider that all components have no failure,
			// the reset of the components must be done
			resetComponentsOperationalStates();
		}
	}
}

void ProcessUnitSC::runSimulation(int duration)
{
	ofstream simulationDataFile;
	string logError;

	bool noFaults = true;

	initialUserOptions();

	if (verboseMode) {
		cout << endl << "New simulation started" << endl;
		cout << "Duration: " << duration << " steps" << endl;
		cout << "Simulation step: " << simulationStep << " seconds" << endl;
	}


	while (duration > 0) {
		bool failureDetected = false;

		cout << endl << "Begin of the new iteration " << *iterationPointer + 1 << endl;

		failureController.defineNewTestScenario();

		noFaults = (testScenario.numberOfFailedComponents == 0);

		supervisedPointer->setTestScenario(testScenario);

		try {
			supervisorPointer->runTest();
		}
		catch (FailureDetectedExcep& error) {
			failureDetected = true;

			cout << error.what() << endl;
			if (noFaults) cout << "-> Supervisor identified a failure that doesn't exist" << endl;

			logError = error.getLogError();

			simulationDataFile.open("data/SimulationMemory/HistoricalFailureLog.csv", std::ios_base::app);

			simulationDataFile << logError;

			simulationDataFile.close();
		};

		if (noFaults ^ failureDetected) {
			cout << endl << "-> Supervisor correctly diagnosed the supervised system" << endl;
		}
		else {
			cout << endl << "-> Supervisor misdiagnosed the supervised system" << endl;
		}


		cout << "End of Iteration " << *iterationPointer << endl;
		cout << " " << endl;

		duration--;
	}
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
}

void ProcessUnitSC::resetSupervisor()
{
	if (supervisorPointer) {
		supervisorPointer->reset();
	}
}

