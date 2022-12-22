#include "include/Component.h"

using namespace std;

Component::Component(
	string name,
	int componentId,
	double faultRate,
	double simulationStep,
	int initialCountBetweenFailures,
	mt19937& generator,
	string dirFaultModes
) :
	faultRate(faultRate),
	name(name),
	generator(generator),
	simulationStep(simulationStep),
	componentId(componentId)
{
	Component::countBetweenFailures = initialCountBetweenFailures;

	Component::isFaulty = false;

	// the -1 value for currentFailureMode means that the component is operating without any fault
	Component::currentFaultModeId = -1;

	loadFailModes(dirFaultModes);

	discrete_distribution<> discreteDist(faultModesWeightArray.begin(), faultModesWeightArray.end());
	Component::discreteDist = discreteDist;

	uniform_real_distribution<double> uniformDist{ 0.0, 1.0 };
	Component::uniformDist = uniformDist;

	Component::verboseMode = false;


}

Component::Component(
	string name,
	int componentId,
	double faultRate,
	double simulationStep,
	int initialCountBetweenFailures,
	mt19937& generator,
	string dirFaultModes,
	bool verboseMode
) :
	faultRate(faultRate),
	name(name),
	generator(generator),
	simulationStep(simulationStep),
	componentId(componentId)
{
	Component::countBetweenFailures = initialCountBetweenFailures;

	Component::isFaulty = false;

	// the -1 value for currentFailureMode means that the component is operating without any fault
	Component::currentFaultModeId = -1;

	loadFailModes(dirFaultModes);

	discrete_distribution<> discreteDist(faultModesWeightArray.begin(), faultModesWeightArray.end());
	Component::discreteDist = discreteDist;

	uniform_real_distribution<double> uniformDist{ 0.0, 1.0 };
	Component::uniformDist = uniformDist;

	Component::verboseMode = verboseMode;
}

void Component::loadFailModes(string dir)
{
	fstream faultModesFile;
	string line, word;

	double faultModeWeight;

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

void Component::repair()
{
	isFaulty = false;
	countBetweenFailures = 0;
}

void Component::calculateReliability()
{
	if (!isFaulty) reliability = exp(-countBetweenFailures * faultRate * simulationStep);
	else reliability = 0.0;
}

bool Component::generateNewOperationalState()
{
	double pseudoRandomNumber;
	if (!isFaulty) {
		pseudoRandomNumber = uniformDist(generator);
		if (verboseMode) cout << "Pseudo random number generated: " << pseudoRandomNumber << endl;
		isFaulty = pseudoRandomNumber > reliability;

		if (isFaulty) {
			currentFaultModeId = discreteDist(generator);
			countBetweenFailures = infinity;
		}
		else {
			// the -1 value for currentFailureMode means that the component is operating without any fault
			currentFaultModeId = -1;
			countBetweenFailures++;
		}
	}

	return isFaulty;
}

int Component::getComponentId()
{
	return componentId;
}

int Component::getCurrentFaultModeId()
{
	return currentFaultModeId;
}

double Component::getReliability()
{
	return reliability;
}

string Component::getComponentName()
{
	return name;
}

string Component::getCurrentFaultModeName()
{
	if (currentFaultModeId == -1) return "No fault";

	return faultModesArray[currentFaultModeId];

}

