#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <iostream>
#include <limits>
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
		double& iterationEquivalentTime,
		mt19937& generator,
		string faultModesDir,
		bool& verboseMode);

	void calculateReliability();
	void repair();
	bool generateNewOperationalState();

	void setCountBetweenFailures(int countBetweenFailures);
	void setFaultMode(int faultModeId);

	int getComponentId();
	int getCurrentFaultModeId();
	int getCountBetweenFailures();
	double getReliability();
	string getComponentName();
	string getCurrentFaultModeName();
	FailureScenarioType* getPointerForCurrentSingleFailureScenario();
	FailureScenarioType* getPointerForSpecifFailureScenario(int faultModeId);
	vector<FailureScenarioType>* getPointerForSingleFailureScenarioArray();
	string getFaultModeName(int faultModeId);


	bool checkFaultModeIdValidity(int id);

private:
	const string name;
	const double faultRate;
	const int componentId;
	const int infinity = numeric_limits<int>::max();

	int countBetweenFailures, currentFaultModeId;
	double reliability;
	bool isFaulty;
	bool& verboseMode;

	double& iterationEquivalentTime;

	mt19937& generator;
	discrete_distribution<> discreteDist;
	uniform_real_distribution<double> uniformDist;

	vector<string> faultModesArray;
	vector<double> faultModesWeightArray;
	vector<FailureScenarioType> singleFailureScenarioArray;


	void loadFaultModes(string dir);
	void loadSingleFailureScenarioFromFile(
		stringstream& strstream,
		string& word);
};