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
		int faultModeId = 0;
		while (getline(faultModesFile, line)) {
			// faultMode struct
			FaultModeType faultMode({ faultModeId });

			stringstream strstream(line);

			// the first word of the line is considered to be the fault mode id.
			// in the file, it serves only as an indicator showing the user which id
			// the system will consider for that fault mode. it has no impact in
			// program's operation
			getline(strstream, word, ',');

			// the second word of the line is considered to be the fault mode name
			getline(strstream, word, ',');
			faultMode.name = word;

			// the third word of the line is considered to be the fault mode weight
			getline(strstream, word, ',');
			faultModeWeight = stod(word);
			faultModesWeightArray.push_back(faultModeWeight);
			faultMode.probability = faultModeWeight;

			loadSingleFailureScenarioFromFile(strstream, word);

			getline(strstream, word, ',');
			faultMode.fmSafety = stringToFmSafetyEnum[word];

			getline(strstream, word, ',');
			faultMode.fmDetectableFuse = stringToFmDetectableEnum[word];

			getline(strstream, word, ',');
			faultMode.fmDetectableKeepPow = stringToFmDetectableEnum[word];

			getline(strstream, word, ',');
			faultMode.classMultipleFaults = stringToClassMultipleFaultsEnum[word];

			faultModesArray.push_back(faultMode);
		}

		faultModesFile.close();
	}
	catch (invalid_argument& error) {
		throw SimulatorFailureExcep("Invalid parameter argument in " + fileDir + ".",
			" SimulationController.ComponentInstance<" + name + ">. \n Argument: '" + word + "'.\n");
	}
}

void Component::loadSingleFailureScenarioFromFile(
	stringstream& strstream,
	string& word)
{
	// failure scenario params expected for the occurrence
	// of a single fault mode in FuseTest
	FailureScenarioFuseTestType singleFailureScenarioFuseTest;

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.meanValueFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.meanValueFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.minFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.maxFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.minFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	singleFailureScenarioFuseTest.maxFuseResultNotBurn = stod(word);

	// failure scenario params expected for the occurrence
	// of a single fault mode in KeepPowerTest
	FailureScenarioKeepPowType singleFailureScenarioKeepPowTest;

	getline(strstream, word, ',');
	singleFailureScenarioKeepPowTest.keepPowerReadbackOffValue = stoi(word);

	getline(strstream, word, ',');
	singleFailureScenarioKeepPowTest.keepPowerReadbackOnValue = stoi(word);

	// joining both tests params in singleFailureScenario struct;
	FailureScenarioType singleFailureScenario = { singleFailureScenarioFuseTest ,
		singleFailureScenarioKeepPowTest };

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
	bool test = checkFaultModeIdValidity(faultModeId);
	if (!test) {
		throw AbortSimulationOpExcep("FaultModeId" +
			to_string(faultModeId) + " is out of bounds\n");;
	}
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

	return faultModesArray[currentFaultModeId].name;

}

FailureScenarioType* Component::getPointerForCurrentSingleFailureScenario()
{
	if (currentFaultModeId == -1) return nullptr;

	return &singleFailureScenarioArray[currentFaultModeId];
}

FailureScenarioType* Component::getPointerForSpecifFailureScenario(int faultModeId)
{
	return &singleFailureScenarioArray[faultModeId];
}

vector<FailureScenarioType>* Component::getPointerForSingleFailureScenarioArray()
{
	return &singleFailureScenarioArray;
}

FaultModeType* Component::getPointerForFaultMode(int faultModeId)
{
	return &faultModesArray[faultModeId];
}

FaultModeType Component::getFaultModeStruct(int faultModeId)
{
	return faultModesArray[faultModeId];
}

string Component::getFaultModeName(int faultModeId)
{
	return faultModesArray[faultModeId].name;
}

bool Component::checkFaultModeIdValidity(int id)
{
	int numberOfFaultModes = faultModesArray.size();
	return (id >= -1 && id < numberOfFaultModes);
}

