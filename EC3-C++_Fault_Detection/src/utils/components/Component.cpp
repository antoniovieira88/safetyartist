#include "include/Component.h"

using namespace std;


Component::Component(
	string name,
	int componentId,
	double faultRate,
	int*& iterationPointer,
	double& iterationEquivalentTime,
	mt19937& generator,
	string faultModesDir,
	bool& verboseMode
) :
	faultRate(faultRate),
	name(name), iterationPointer(iterationPointer),
	generator(generator),
	iterationEquivalentTime(iterationEquivalentTime),
	componentId(componentId), verboseMode(verboseMode)
{
	Component::countBetweenFailures = 0;
	Component::randNumGeneratedInFailure = NAN;
	Component::reliability = NAN;
	Component::isFaulty = false;

	// the -1 value for currentFailureMode means that the component is operating without any fault
	Component::currentFaultModeId = -1;

	loadFaultModes(faultModesDir);

	discrete_distribution<> discreteDist(faultModesWeightArray.begin(), faultModesWeightArray.end());
	Component::discreteDist = discreteDist;

	uniform_real_distribution<double> uniformDist{ 0.0, 1.0 };
	Component::uniformDist = uniformDist;

	Component::verboseMode = verboseMode;
	Component::iterationAtFailure = 0;
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
	int faultModeId = 0;
	try {
		while (getline(faultModesFile, line)) {
			// faultMode struct
			FaultModeType faultMode({ faultModeId, componentId });

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

			loadSingleFailureScenarioFromFile(strstream, word, faultMode, fileDir, faultModeId);

			getline(strstream, word, ',');
			faultMode.fmSafety = stringToFmSafetyEnum[word];

			getline(strstream, word, ',');
			faultMode.fmDetectableFuse = stringToFmDetectableEnum[word];

			getline(strstream, word, ',');
			faultMode.fmDetectableKeepPow = stringToFmDetectableEnum[word];

			getline(strstream, word, ',');
			faultMode.classMultipleFaults = stringToClassMultipleFaultsEnum[word];

			faultModesArray.push_back(faultMode);
			faultModeId++;
		}

		faultModesFile.close();
	}
	catch (invalid_argument& error) {
		throw SimulatorFailureExcep("Invalid parameter argument in " + fileDir + ".",
			" SimulationController.ComponentInstance<" + name + ">::faultModeId =" + to_string(faultModeId) + ". \n Argument : '" + word +
			"'.\n");
	}
}

void Component::loadSingleFailureScenarioFromFile(
	stringstream& strstream,
	string& word,
	FaultModeType& faultMode,
	string fileDir,
	int faultModeId)
{
	// failure scenario params expected for the occurrence
	// of a single fault mode in FuseTest
	FailureScenarioFuseType singleFailureScenarioFuseTest;

	double meanValueFuseResultBurn, meanValueFuseResultNotBurn;
	double minFuseResultBurn, maxFuseResultBurn;
	double minFuseResultNotBurn, maxFuseResultNotBurn;

	getline(strstream, word, ',');
	meanValueFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	meanValueFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	minFuseResultBurn = stod(word);

	getline(strstream, word, ',');
	maxFuseResultBurn = stod(word);

	if (!checkBoundsValidity(minFuseResultBurn, meanValueFuseResultBurn, maxFuseResultBurn)) {
		throw SimulatorFailureExcep("Invalid combination of fuseResultBurn bounds in " + fileDir,
			"SimulationController.ComponentInstance<" + name + ">::faultModeId = '" + to_string(faultModeId) + "'.\n");
	}

	getline(strstream, word, ',');
	minFuseResultNotBurn = stod(word);

	getline(strstream, word, ',');
	maxFuseResultNotBurn = stod(word);

	if (!checkBoundsValidity(minFuseResultNotBurn, meanValueFuseResultNotBurn, maxFuseResultNotBurn)) {
		throw SimulatorFailureExcep("Invalid combination of fuseResultNotBurn bounds in " + fileDir,
			"SimulationController.ComponentInstance<" + name + ">::FaultModeId = '" + to_string(faultModeId) + "'.\n");
	}

	singleFailureScenarioFuseTest = {
		meanValueFuseResultBurn,
		meanValueFuseResultNotBurn,
		minFuseResultBurn,
		maxFuseResultBurn,
		minFuseResultNotBurn,
		maxFuseResultNotBurn
	};

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

	faultMode.singleFailureScenario = singleFailureScenario;
}

void Component::repair()
{
	isFaulty = false;
	countBetweenFailures = 0;
	currentFaultModeId = -1;
	iterationAtFailure = 0;
	randNumGeneratedInFailure = NAN;
	reliability = NAN;

}

void Component::setCountBetweenFailures(int countBetweenFailures)
{
	Component::countBetweenFailures = countBetweenFailures;
}

void Component::setFaultMode(int faultModeId)
{
	if (!checkFaultModeIdValidity(faultModeId)) {
		throw AbortSimulationOpExcep("FaultModeId" +
			to_string(faultModeId) + " is out of bounds\n");;
	}
	currentFaultModeId = faultModeId;

	if (faultModeId == -1) {
		isFaulty = false;
		iterationAtFailure = -1;
	}
	else {
		isFaulty = true;
		countBetweenFailures = infinity;
		reliability = 0.0;
	}
}

void Component::setIterationAtFailure(int iteration)
{
	Component::iterationAtFailure = iteration;
}

void Component::calculateReliability()
{
	if (!isFaulty) reliability = exp(-countBetweenFailures * faultRate * iterationEquivalentTime);
	else reliability = 0.0;
}

/* Method to check if the component is fault based on an uniform distribution - generated pseudorandom number(prn)
 *
 * Basics of the method: In order to check whether a component is faulty by using a pseudorandom number 'prn' within [0; 1[,
 * 'prn' shall represent the component's failure distribution function (F(t) = 1-R(t) = 1-*e^(-lambda*t)). By letting 'prn'
 * equal to F(t), one can calculate the time 'tPRN' at which the component's failure distribution is reached by means of the
 * equation tPRN = -(1/lambda) * ln(1 - prn), since tPRN belongs to [0, +inf[.
 * See further information on https://www.eg.bucknell.edu/~xmeng/Course/CS6337/Note/master/node50.html.
 * 
 * With this definition, the state of the component is defined by comparing tPNG to the current simulation time (tSIM).
 * 
 * 1) If tSIM < tPRN, the component has not reached its failed state time and, thus, remains operational;
 * 2) If tSIM >= tPRN, the component has reached its failed state time and, thus, enters a failed state.
 * 
 * The function isComponentFaulty retrieves 'true' if the condition '1' is satisfied and 'false' otherwise.
 */
bool Component::isComponentFaulty(double prn)
{
	double tPRN = (-1 / faultRate) * (log(1 - prn));

	// Fault condition: iterationEquivalentTime >= tPRN
	if (iterationEquivalentTime >= tPRN)
		return true;

	else
		return false;
}

enum componentOpStatus Component::generateNewOperationalState()
{
	double pseudoRandomNumber;
	if (!isFaulty) {
		pseudoRandomNumber = uniformDist(generator);
		if (verboseMode) cout << "Pseudo random number generated: " << pseudoRandomNumber << endl;
		isFaulty = isComponentFaulty(pseudoRandomNumber);

		if (isFaulty) {
			randNumGeneratedInFailure = pseudoRandomNumber;
			iterationAtFailure = *iterationPointer + 1;
			currentFaultModeId = discreteDist(generator);
			countBetweenFailures = infinity;
			return newFault;
		}
		else {
			// the -1 value for currentFailureMode means that the component is operating without any fault
			currentFaultModeId = -1;
			countBetweenFailures++;
			return noFault;
		}
	}

	return previousFault;
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

double Component::getRandNumGeneratedInFailure()
{
	return randNumGeneratedInFailure;
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

	return &faultModesArray[currentFaultModeId].singleFailureScenario;
}

FailureScenarioType* Component::getPointerForSpecifFailureScenario(int faultModeId)
{
	return &faultModesArray[faultModeId].singleFailureScenario;
}

vector<FaultModeType>* Component::getPointerForFaultModesArray()
{
	return &faultModesArray;
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

int Component::getIterationOnFailure()
{
	return iterationAtFailure;
}

bool Component::checkFaultModeIdValidity(int id)
{
	int numberOfFaultModes = faultModesArray.size();
	return (id >= -1 && id < numberOfFaultModes);
}

bool Component::checkBoundsValidity(double min, double mean, double max)
{
	return (min <= mean && mean <= max);
};