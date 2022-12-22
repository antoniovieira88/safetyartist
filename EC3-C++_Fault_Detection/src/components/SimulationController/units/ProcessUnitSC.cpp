#include "../include/ProcessUnitSC.h"

ProcessUnitSC::ProcessUnitSC(
	FailureController& failureController,
	ParamsController& paramsController,
	vector<int>& testScenario)
	:
	failureController(failureController),
	paramsController(paramsController),
	testScenario(testScenario)

{
	ProcessUnitSC::supervisorPointer = NULL;
	ProcessUnitSC::supervisedPointer = NULL;
	ProcessUnitSC::iterationPointer = NULL;

	initializeParamsController();
}

void ProcessUnitSC::attach(Supervisor* supervisorPointer, Supervised* supervisedPointer)
{
	ProcessUnitSC::supervisorPointer = supervisorPointer;
	ProcessUnitSC::supervisedPointer = supervisedPointer;

	ProcessUnitSC::iterationPointer = supervisorPointer->getIterationPointer();
}

void ProcessUnitSC::runSimulation(int duration)
{
	ofstream simulationDataFile;
	string logError;

	bool noFaults = true;
	bool failureDetected = false;

	while (duration > 0) {
		cout << endl << "Begin of the new iteration " << *iterationPointer + 1 << endl;

		failureController.defineNewTestScenario();

		noFaults = (failureController.getNumberOfFailedComponents() == 0);

		supervisedPointer->setTestScenario(!noFaults);

		try {
			supervisorPointer->newTest();
		}
		catch (FailureDetectedExcep& error) {
			failureDetected = true;

			cout << error.what() << endl;
			if (noFaults) cout << "Supervisor identified a failure that doens't exist" << endl;

			logError = error.getLogError();

			simulationDataFile.open("data/SimulationMemory/HistoricalFailureLog.csv", std::ios_base::app);

			simulationDataFile << logError;

			simulationDataFile.close();
		};

		if (noFaults ^ failureDetected) {
			cout << endl << "Supervisor misdiagnosed the supervised system" << endl;
		}
		else {
			cout << endl << "Supervisor correctly diagnosed the supervised system" << endl;
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


