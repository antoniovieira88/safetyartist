#include "../../structs/structs.h"
#include "../../exceptions/include/AbortSimulationOpExcep.h"
#include "../../exceptions/include/SimulatorFailureExcep.h"

#pragma once
class Component {
public:

	Component(
		string name,
		int componentId,
		double failureRate,
		int*& iterationPointer,
		double& iterationEquivalentTime,
		mt19937& generator,
		string faultModesDir,
		bool& verboseMode);

	void calculateReliability();
	void repair();
	enum componentOpStatus generateNewOperationalState();

	void setCountBetweenFailures(int countBetweenFailures);
	void setFaultMode(int faultModeId);
	void setIterationAtFailure(int iteration);

	int getComponentId();
	int getCurrentFaultModeId();
	int getCountBetweenFailures();
	double getReliability();
	string getComponentName();
	string getCurrentFaultModeName();
	FaultModeType getFaultModeStruct(int faultModeId);
	FailureScenarioType* getPointerForCurrentSingleFailureScenario();
	FailureScenarioType* getPointerForSpecifFailureScenario(int faultModeId);
	vector<FaultModeType>* getPointerForFaultModesArray();
	FaultModeType* getPointerForFaultMode(int faultModeId);
	string getFaultModeName(int faultModeId);
	int getIterationOnFailure();

	bool checkFaultModeIdValidity(int id);

private:
	const string name;
	const double faultRate;
	const int componentId;
	const int infinity = numeric_limits<int>::max();


	int countBetweenFailures, currentFaultModeId, iterationAtFailure;
	double reliability;
	bool isFaulty;

	bool& verboseMode;

	int*& iterationPointer;

	double& iterationEquivalentTime;

	mt19937& generator;
	discrete_distribution<> discreteDist;
	uniform_real_distribution<double> uniformDist;

	vector<FaultModeType> faultModesArray;
	vector<double> faultModesWeightArray;

	void loadFaultModes(string dir);
	void loadSingleFailureScenarioFromFile(
		stringstream& strstream,
		string& word,
		FaultModeType& faultMode,
		string fileDir,
		int faultModeId);

	bool checkBoundsValidity(double min, double mean, double max);
};