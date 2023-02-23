#include "../include/ParamsController.h"

using namespace std;

ParamsController::ParamsController(
	string& simulationName,
	SimulationSpecificParamsType& simulationSpecificParams,
	mt19937& generator,
	vector<Component>& componentsArray,
	int*& iterationPointer,
	string simulationMemoryDir,
	bool verboseMode) :
	simulationName(simulationName), generator(generator), iterationPointer(iterationPointer),
	componentsArray(componentsArray), simulationSpecificParams(simulationSpecificParams),
	faultModesDir(simulationMemoryDir + "/FailureSpecs_EC3/FaultModes"),
	failureSpecsDir(simulationMemoryDir + "/FailureSpecs_EC3"),
	simulationsDir(simulationMemoryDir + "/Simulations")
{
	ParamsController::verboseMode = verboseMode;
	ParamsController::initialFaults = false;
	ParamsController::numberOfComponents = 0;
}

void ParamsController::loadFailureSpecs()
{
	string line, word, componentName;
	double faultRate = 0.0;
	int componentId = 0;
	fstream faultRatesFile;

	faultRatesFile.open(failureSpecsDir + "/ComponentsFaultRates.csv", ios::in);
	if (faultRatesFile.fail()) {
		throw SimulatorFailureExcep(
			failureSpecsDir +
			"/ComponentsFaultRates.csv file could not be accessed",
			"SimulationController.ParamsController");
	}
	// the first line corresponds to the header, so it is ignored
	getline(faultRatesFile, line);

	// each subsequent line corresponds to a component
	while (getline(faultRatesFile, line)) {
		stringstream strstream(line);

		// the first word of the line is considered to be the component name
		getline(strstream, word, ',');
		componentName = word;

		// the second word of the line is considered to be the failure rate
		getline(strstream, word, ',');
		faultRate = stod(word);

		// the component is instantiated with 'countBetweenFailures = 0' and 'isFaulty = false'
		Component newComponent(
			componentName,
			componentId,
			faultRate,
			iterationPointer,
			simulationSpecificParams.iterationEquivalentTime,
			generator,
			faultModesDir,
			verboseMode);

		componentId++;

		// the components are stored in the vector 'componentsArray', which is a class member
		componentsArray.push_back(newComponent);
	}

	faultRatesFile.close();
}

int ParamsController::setComponentsInitialOperationalState()
{
	fstream componentsOperationalStateFile;
	string line, word;
	int componentId = 0, faultModeId = -1, numberOfFaultyComponents = 0;
	int initialCountBetweenFailures = 0;
	int iterationAtFailure = -1;

	componentsOperationalStateFile.open(
		simulationsDir + "/" + simulationName
		+ "/ComponentsOperationalState.csv",
		ios::in);
	if (componentsOperationalStateFile.fail()) {
		componentsOperationalStateFile.close();
		throw AbortSimulationOpExcep(
			"ComponentsOperationalState.csv file for simulation '"
			+ simulationName + "' could not be accessed");
	}

	try {
		// the first line corresponds is a header, so it is ignored
		std::getline(componentsOperationalStateFile, line);

		// each subsequent line corresponds to a component
		while (std::getline(componentsOperationalStateFile, line)) {
			stringstream strstream(line);

			// the first word is considered to be the component id
			// in this loop, it is simply ignored, as the components list has already been defined when this function is called
			std::getline(strstream, word, ',');

			try {
				// the second word is considered to be the faultModeId from the last iteration
				std::getline(strstream, word, ',');
				faultModeId = stoi(word);
			}
			catch (invalid_argument& error) {
				throw AbortSimulationOpExcep("Invalid faultModeId parameter entered: "
					+ word + ".\n");
			}

			if (componentId >= componentsArray.size())
				throw AbortSimulationOpExcep("Incompatible number of components between the files: ComponentsOperationalState.csv and ComponentsFaultRates.csv");

			// if the faultMode is different from "-1", the initialCountBetweenFailures of
			// the component is automatically updated to zero when "setFaultModeId" is called
			//  -> obs.: "-1" indicates no fault. When it equals to "-1", the interationAtFailure 
			// of the component is automatically set to "-1" (no fault condition)
			componentsArray[componentId].setFaultMode(faultModeId);

			// only when there is no fault, it is necessary to retrieve the countBetweenFailures from the last iteration
			//  -> obs.: "-1" indicates no fault
			if (faultModeId == -1) {
				// the second word is considered to be the countBetweenFailures
				std::getline(strstream, word);
				initialCountBetweenFailures = stoi(word);
				componentsArray[componentId].setCountBetweenFailures(initialCountBetweenFailures);
				componentsArray[componentId].calculateReliability();
			}
			// only when there is a fault is necessary to retrieve the interationAtFailure from the previous failure
			else {
				try {
					// the second word is considered to be the countBetweenFailures.
					// In this case, this value is ignored (we already know it is set to infinity since
					// the component has a fault)
					std::getline(strstream, word, ',');

					// the third word is considered to be the iteration number at which the component first failed
					// -> obs.: "-1" indicates no fault
					std::getline(strstream, word, ',');
					iterationAtFailure = stoi(word);
					componentsArray[componentId].setIterationAtFailure(iterationAtFailure);

					// this is only a flag variable which helps restore the components states to a default initial condition
					// obs.: this flag is later used in SimulationController::ProcessUnitSC::userInputOptions as the return of
					// method ParamsController::isSurpervisedStartingWithFailure()
					initialFaults = true;
					numberOfFaultyComponents++;
				}
				catch (invalid_argument& error) {
					throw AbortSimulationOpExcep("Invalid parameter entered in  ComponentsOperationalState.csv, ComponentID = "
						+ to_string(componentId) + ".\n");
				}
			}

			componentId++;
		}

	}
	catch (AbortSimulationOpExcep& error) {
		componentsOperationalStateFile.close();
		throw;
	}

	return numberOfFaultyComponents;
}

// this method is called at the end of each iterations cycle (duration == 0). Its purpose is
// to update the ComponentsOperationalState.csv
void ParamsController::updateComponentsOperationalStateFile()
{
	fstream componentsOperationalStateFile;
	int componentFaultModeId = 0;

	componentsOperationalStateFile.open(
		simulationsDir + "/" + simulationName
		+ "/ComponentsOperationalState.csv",
		ios::out);
	if (componentsOperationalStateFile.fail()) {
		componentsOperationalStateFile.close();
		throw AbortSimulationOpExcep(
			"ComponentsOperationalState.csv file for simulation '"
			+ simulationName + "' could not be accessed");
	}

	// the header is written as the first line of the csv file
	componentsOperationalStateFile << "name,faultModeId,countBetweenFailures" << endl;

	for each (Component component in componentsArray)
	{
		componentFaultModeId = component.getCurrentFaultModeId();

		componentsOperationalStateFile
			<< component.getComponentName() << ","
			<< componentFaultModeId << ",";

		// if the component is in any faultMode, the string "inf" is written in the countBetweenFailures column.
		// Otherwise, the finite countBetweenFailures's value is written
		if (componentFaultModeId == -1) {
			componentsOperationalStateFile << component.getCountBetweenFailures() << ",";
		}
		else {
			componentsOperationalStateFile << "inf" << ",";
		}

		componentsOperationalStateFile << component.getIterationOnFailure() << endl;

	}

	if (verboseMode) {
		cout << "ComponentsOperationalState.csv file updated" << endl;
	}

	componentsOperationalStateFile.close();
}

bool ParamsController::isSurpervisedStartingWithFailure()
{
	return initialFaults;
}

// load the simulation specific params 
// (supervisor params, supervised params, simulationSeed
// and iterationEquivalentTime) to the 'simulationSpecificParams' struct,
// which is instantiated in Simulation Controller scope
void ParamsController::loadSimulationSpecificParams()
{
	fstream simulationParamsFile;
	string line, word;
	double doubleParamsType[11]; // there are 11 double-type parameters

	simulationParamsFile.open(
		simulationsDir + "/"
		+ simulationName + "/SimulationParams.csv",
		ios::in);
	if (simulationParamsFile.fail()) {
		simulationParamsFile.close();
		throw AbortSimulationOpExcep(
			"SimulationParams.csv file for simulation '"
			+ simulationName + "' could not be read");
	}

	try {
		stringstream strstream;

		// the first line corresponds to the header, so it's ignored
		getline(simulationParamsFile, line);

		// in this loop, all the 11 first params are collected from the first 11 lines of SimulationParams.csv file.
		// They are stored in 'double doubleParamsType[]' (they are all from the same data type: double).
		for (int i = 0; i < 11; i++) {
			getline(simulationParamsFile, line);
			strstream = stringstream(line);
			getline(strstream, word, ',');
			getline(strstream, word);
			doubleParamsType[i] = stod(word);
		}

		// load the integer-type parameters 'simulationSeed' and 'supervisorMaxNumberOfRegisters',
		// which are stored at the last two lines of 
		// the SimulationParams.csv file

		// simulationSeed
		getline(simulationParamsFile, line);
		strstream = stringstream(line);
		getline(strstream, word, ',');
		getline(strstream, word);
		simulationSpecificParams.simulationSeed = stoul(word);

		// supervisorMaxNumberOfRegisters
		getline(simulationParamsFile, line);
		strstream = stringstream(line);
		getline(strstream, word, ',');
		getline(strstream, word);
		simulationSpecificParams.maxNumberOfRegisters = stoul(word);

		simulationParamsFile.close();

	}
	catch (invalid_argument& error) {
		simulationParamsFile.close();
		throw AbortSimulationOpExcep(
			"Invalid simulation parameter in SimulationParams.csv file entered: "
			+ word + ".\n");
	}

	// the parameters below were read at the following order in SimulationParams.csv
	// note that the order below is the same as the one presented in
	// 'ProcessUnitSC::createSimulationParams'

	// Supervisor (doubles)
	simulationSpecificParams.overallSilhouetteTolerance = doubleParamsType[0];
	simulationSpecificParams.silhouetteDiffTolerance = doubleParamsType[1];
	simulationSpecificParams.numberOfPointsPerClusterDiffTolerance = doubleParamsType[2];
	// Supervised (doubles)
	simulationSpecificParams.nominalFuseResultBurn = doubleParamsType[3];
	simulationSpecificParams.nominalFuseResultNotBurn = doubleParamsType[4];
	simulationSpecificParams.minNominalFuseResultBurn = doubleParamsType[5];
	simulationSpecificParams.maxNominalFuseResultBurn = doubleParamsType[6];
	simulationSpecificParams.minNominalFuseResultNotBurn = doubleParamsType[7];
	simulationSpecificParams.maxNominalFuseResultNotBurn = doubleParamsType[8];
	simulationSpecificParams.maxStdDeviation = doubleParamsType[9];
	// Simulation Controller (doubles)
	simulationSpecificParams.iterationEquivalentTime = doubleParamsType[10];
}

void ParamsController::setVerboseMode(bool verboseModeValue)
{
	ParamsController::verboseMode = verboseModeValue;
}

