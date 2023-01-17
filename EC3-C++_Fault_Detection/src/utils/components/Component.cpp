#include "include/Component.h"

using namespace std;


Component::Component(
	string name,
	int componentId,
	double faultRate,
	double& iterationEquivalentTime,
	mt19937& generator,
	string faultModesDir,
	bool& verboseMode
) :
	faultRate(faultRate),
	name(name),
	generator(generator),
	iterationEquivalentTime(iterationEquivalentTime),
	componentId(componentId), verboseMode(verboseMode)
{
	Component::countBetweenFailures = 0;

	Component::isFaulty = false;

	// the -1 value for currentFailureMode means that the component is operating without any fault
	Component::currentFaultModeId = -1;

	loadFaultModes(faultModesDir);

	discrete_distribution<> discreteDist(faultModesWeightArray.begin(), faultModesWeightArray.end());
	Component::discreteDist = discreteDist;

	uniform_real_distribution<double> uniformDist{ 0.0, 1.0 };
	Component::uniformDist = uniformDist;

	Component::verboseMode = verboseMode;
}

void Component::loadFaultModes(string dir)
{
	fstream faultModesFile;
	string line, word;
	const string fileDir = dir + "/" + name + ".csv";

	double faultModeWeight;

	faultModesFile.open(fileDir, ios::in);
	if (faultModesFile.fail()) {
		throw SimulatorFailureExcep(name + "'s fault modes file '" + fileDir + "' could not be accessed.",
			"SimulationController.ComponentInstance<" + name + ">");
	}

	// the first line corresponds to the header, so it is ignored
	getline(faultModesFile, line);
	try {
		while (getline(faultModesFile, line)) {
			stringstream strstream(line);

			// the first word of the line is considered to be the fault mode id.
			// in the file, it serves only as an indicator showing the user which id
			// the system will consider for that fault mode. it has no impact in
			// program's operation
			getline(strstream, word, ',');

			// the second word of the line is considered to be the fault mode name
			getline(strstream, word, ',');
			faultModesArray.push_back(word);

			// the third word of the line is considered to be the fault mode weight
			getline(strstream, word, ',');
			faultModeWeight = stod(word);
			faultModesWeightArray.push_back(faultModeWeight);

			loadSingleFailureScenarioFromFile(strstream, word);
		}

		faultModesFile.close();
	}
	catch (invalid_argument& error) {
		throw SimulatorFailureExcep("Invalid parameter argument in " + fileDir + ".",
			"SimulationController.ComponentInstance<" + name + ">");
	}
}

void Component::loadSingleFailureScenarioFromFile(
	stringstream& strstream,
	string& word)
{
	//failure scenario params expected for the occurrence of a single fault mode
	FailureScenarioType singleFailureScenario;

	getline(strstream, word, ',');
	singleFailureScenario.meanValueFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenario.meanValueFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenario.minFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenario.maxFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenario.minFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenario.maxFuseResultNotBurn = stod(word);

	singleFailureScenarioArray.push_back(singleFailureScenario);
}

void Component::repair()
{
	isFaulty = false;
	countBetweenFailures = 0;
	currentFaultModeId = -1;
}

void Component::setCountBetweenFailures(int countBetweenFailures)
{
	Component::countBetweenFailures = countBetweenFailures;
}

void Component::setFaultMode(int faultModeId)
{
	currentFaultModeId = faultModeId;

	if (faultModeId == -1) {
		isFaulty = false;
	}
	else {
		isFaulty = true;
		countBetweenFailures = infinity;
		reliability = 0.0;
	}
}

void Component::calculateReliability()
{
	if (!isFaulty) reliability = exp(-countBetweenFailures * faultRate * iterationEquivalentTime);
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

int Component::getCountBetweenFailures()
{
	return countBetweenFailures;
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

FailureScenarioType* Component::getSingleFailureScenarioPointer()
{
	if (currentFaultModeId == -1) return nullptr;

	return &singleFailureScenarioArray[currentFaultModeId];
}

