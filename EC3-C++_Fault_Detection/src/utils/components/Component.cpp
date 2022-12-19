#include "include/Component.h"

using namespace std;

Component::Component(
	string name,
	double failureRate,
	double simulationStep,
	int countBetweenFailures,
	mt19937& generator) :
	faultRate(failureRate), name(name), generator(generator), simulationStep(simulationStep)
{
	Component::countBetweenFailures = countBetweenFailures;

	isFaulty = false;

	// the -1 value for currentFailureMode means that the component is operating without any fault
	currentFaultMode = -1;

	loadFailModes("data/SimulationMemory/FaultModes");

	discrete_distribution<> discreteDist(faultModesWeightArray.begin(), faultModesWeightArray.end());
	Component::discreteDist = discreteDist;

	uniform_real_distribution<double> uniformDist{ 0.0, 1.0 };
	Component::uniformDist = uniformDist;
}

void Component::loadFailModes(string dir)
{
	fstream faultModesFile;
	string line, word;

	int faultModeWeight;

	faultModesFile.open(dir + "/" + name + ".csv", ios::in);

	while (getline(faultModesFile, line)) {
		stringstream strstream(line);
		getline(strstream, word, ','); // the first word of the line is considered to be the failure mode name
		faultModesArray.push_back(word);
		getline(strstream, word, ','); // the second word of the line is considered to be the failure mode weight
		faultModeWeight = stod(word);
		faultModesWeightArray.push_back(faultModeWeight);
	}

	faultModesFile.close();
}

void Component::calculateReliability()
{
	reliability = exp(-countBetweenFailures * faultRate * simulationStep);
}

bool Component::generateNewOperationalState()
{
	if (!isFaulty) {
		isFaulty = uniformDist(generator) > reliability;

		if (isFaulty) {
			currentFaultMode = discreteDist(generator);
			countBetweenFailures = INFINITY;
		}
		else {
			// the -1 value for currentFailureMode means that the component is operating without any fault
			currentFaultMode = -1;
		}
	}

	return isFaulty;
}

int Component::getCurrentFaultMode()
{
	return currentFaultMode;
}

double Component::getReliability()
{
	return reliability;
}


