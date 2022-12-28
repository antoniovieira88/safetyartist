#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <limits>
#include "../../structs/structs.h"

using namespace std;

#pragma once
class Component {
public:
	Component(
		string name,
		int componentId,
		double failureRate,
		double simulationStep,
		mt19937& generator,
		string dirFaultModes);

	Component(
		string name,
		int componentId,
		double failureRate,
		double simulationStep,
		mt19937& generator,
		string dirFaultModes,
		bool verboseMode);

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

	FailureScenarioType* getSingleFailureScenarioPointer();

private:
	const string name;
	const double faultRate, simulationStep;
	const int componentId;
	const int infinity = numeric_limits<int>::max();

	int countBetweenFailures, currentFaultModeId;
	double reliability;
	bool isFaulty, verboseMode;

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