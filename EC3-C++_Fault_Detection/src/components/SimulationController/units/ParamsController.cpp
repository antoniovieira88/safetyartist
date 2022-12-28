#include "../include/ParamsController.h"

using namespace std;

ParamsController::ParamsController(
	double simulationStep,
	mt19937& generator,
	vector<Component>& componentsArray,
	string dirFailureSpecs,
	string dirFaultModes) :
	simulationStep(simulationStep), generator(generator), componentsArray(componentsArray),
	dirFaultModes(dirFaultModes), dirFailureSpecs(dirFailureSpecs)
{
	ParamsController::verboseMode = false;
	ParamsController::initialFaults = false;
	ParamsController::numberOfComponents = 0;

}

ParamsController::ParamsController(
	double simulationStep,
	mt19937& generator,
	vector<Component>& componentsArray,
	string dirFailureSpecs,
	string dirFaultModes,
	bool verboseMode) :
	simulationStep(simulationStep), generator(generator), componentsArray(componentsArray),
	dirFaultModes(dirFaultModes), dirFailureSpecs(dirFailureSpecs)
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

	faultRatesFile.open(dirFailureSpecs + "/ComponentsFaultRates.csv", ios::in);

	// the first line corresponds to the header, so it is ignored
	getline(faultRatesFile, line);

	// each subsequent line corresponds to a component
	while (getline(faultRatesFile, line)) {
		stringstream strstream(line);

		// the first word of the line is considered to be the component
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
			simulationStep,
			generator,
			dirFaultModes,
			verboseMode);

		componentId++;

		// the components are stored in the vector 'componentsArray', which is a class member
		componentsArray.push_back(newComponent);
	}

	faultRatesFile.close();

	setComponentsInitialOperationalState();
}

void ParamsController::setComponentsInitialOperationalState()
{
	fstream componentsOperationalStateFile;
	string line, word;
	int countBetweenFailures = 0, componentId = 0, faultModeId = -1;

	componentsOperationalStateFile.open("data/SimulationMemory/ComponentsOperationalState.csv", ios::in);

	// the first line corresponds to the header, so it is ignored
	getline(componentsOperationalStateFile, line);

	// each subsequent line corresponds to a component
	while (getline(componentsOperationalStateFile, line)) {
		stringstream strstream(line);

		// the first word is considered to be the component id
		// in this loop, it is simply ignored, as the components list has already been defined when this function is called
		getline(strstream, word, ',');

		// the second word is considered to be the faultModeId from the last iteration
		getline(strstream, word, ',');
		faultModeId = stoi(word);

		// if the faultMode is different from "-1", the countBetweenFailures of
		// the component is automatically updated to infinity when "setFaultModeId" is called
		//  -> obs.: "-1" indicates no fault
		componentsArray[componentId].setFaultMode(faultModeId);

		// only when there is no fault, it is necessary to retrieve the last finite countBetweenFailures
		//  -> obs.: "-1" indicates no fault
		if (faultModeId == -1) {
			getline(strstream, word, ',');
			countBetweenFailures = stoi(word);
			componentsArray[componentId].setCountBetweenFailures(countBetweenFailures);
		}
		else {
			initialFaults = true;
		}

		componentId++;
	}

}

void ParamsController::updateComponentsOperationalStateFile()
{
	fstream componentsOperationalStateFile;
	string componentName;
	int componentFaultModeId;

	componentsOperationalStateFile.open("data/SimulationMemory/ComponentsOperationalState.csv", ios::out);

	// the header is written as the first line of the csv file
	componentsOperationalStateFile << "name,faultModeId,countBetweenFailures" << endl;

	for each (Component component in componentsArray)
	{
		componentName = component.getComponentName();
		componentFaultModeId = component.getCurrentFaultModeId();

		componentsOperationalStateFile << component.getComponentName() << "," << componentFaultModeId << ",";

		// if the component is in any faultMode, the string "inf" is written in the countBetweenFailures column.
		// Otherwise, the finite countBetweenFailures's value is written
		if (componentFaultModeId == -1) {
			componentsOperationalStateFile << component.getCountBetweenFailures() << endl;
		}
		else {
			componentsOperationalStateFile << "inf" << endl;
		}
	}

	componentsOperationalStateFile.close();
}

bool ParamsController::isSurpervisedStartingWithFailure()
{
	return initialFaults;
}


