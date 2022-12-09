#include "include/ParamsController.h"

using namespace std;

ParamsController::ParamsController()
{
	loadFailureSpecs();
}

vector<double> ParamsController::getFailureRateArray()
{
	return failureRateArray;
}

vector<int>* ParamsController::getCountBetweenFailuresArray() {
	return &countBetweenFailuresArray;
}

vector<double> ParamsController::getReliabiabilityArray()
{
	double reliability, failureRate = 0.0;
	int countBetweenFailures = 0;
	for (int i = 0; i < numberOfComponents; i++) {
		reliability = exp(-countBetweenFailures * failureRate);
		reliabiabilityArray.push_back(reliability);
	}
	return reliabiabilityArray;
}


void ParamsController::loadFailureSpecs()
{
	failureRateArray.clear();
	countBetweenFailuresArray.clear();
	failureRatesFile.open("data/SimulationMemory/ComponentsFailureSpecs.csv", ios::in);
	string line, word;
	double failureRate = 0.0;
	int countBetweenFailures = 0;
	while (getline(failureRatesFile, line)) {
		stringstream strstream(line);
		getline(strstream, word, ','); // the first word of the line is considered to be the component
		componentsArray.push_back(word);
		getline(strstream, word, ','); // the second word of the line is considered to be the failure rate
		failureRate = stod(word);
		failureRateArray.push_back(failureRate);
		getline(strstream, word, ','); // the third word of the line is considered to be the countBetweenFailures value
		countBetweenFailures = stoi(word);
		countBetweenFailuresArray.push_back(countBetweenFailures);
	}
	numberOfComponents = failureRateArray.size();
	failureRatesFile.close();
}


