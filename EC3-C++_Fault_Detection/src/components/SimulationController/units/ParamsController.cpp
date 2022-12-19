#include "../include/ParamsController.h"

using namespace std;

ParamsController::ParamsController(double simulationStep, mt19937& generator) :
	simulationStep(simulationStep), generator(generator)
{
	numberOfComponents = 0;
	loadFailureSpecs();
}

vector<Component>& ParamsController::getComponentsArray()
{
	return componentsArray;
}


void ParamsController::loadFailureSpecs()
{
	string line, word, componentName;
	double faultRate = 0.0;
	int countBetweenFailures = 0;

	faultRatesFile.open("data/SimulationMemory/ComponentsFailureSpecs.csv", ios::in);

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
			faultRate,
			simulationStep,
			countBetweenFailures,
			generator);

		componentsArray.push_back(newComponent);
	}

	faultRatesFile.close();
}


