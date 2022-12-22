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
	ParamsController::numberOfComponents = 0;
}

void ParamsController::loadFailureSpecs()
{
	string line, word, componentName;
	double faultRate = 0.0;
	int countBetweenFailures = 0, componentId = 0;

	faultRatesFile.open(dirFailureSpecs + "/ComponentsFailureSpecs.csv", ios::in);

	while (getline(faultRatesFile, line)) {
		stringstream strstream(line);
		// the first word of the line is considered to be the component
		getline(strstream, word, ',');
		componentName = word;
		// the second word of the line is considered to be the failure rate
		getline(strstream, word, ',');
		faultRate = stod(word);
		// the third word of the line is considered to be the countBetweenFailures value
		getline(strstream, word, ',');
		countBetweenFailures = stoi(word);

		Component newComponent(
			componentName,
			componentId,
			faultRate,
			simulationStep,
			countBetweenFailures,
			generator,
			dirFaultModes,
			verboseMode);

		componentId++;

		componentsArray.push_back(newComponent);
	}

	faultRatesFile.close();
}


