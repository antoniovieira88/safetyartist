#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

#pragma once
class Component {
public:
	Component(
		string name,
		int componentId,
		double failureRate,
		double simulationStep,
		int countBetweenFailures,
		mt19937& generator,
		string dirFaultModes);

	Component(
		string name,
		int componentId,
		double failureRate,
		double simulationStep,
		int countBetweenFailures,
		mt19937& generator,
		string dirFaultModes,
		bool verboseMode);

	void calculateReliability();
	void repair();

	bool generateNewOperationalState();

	int getComponentId();
	int getCurrentFaultModeId();
	double getReliability();
	string getComponentName();
	string getCurrentFaultModeName();


private:
	const string name;
	const double faultRate, simulationStep;
	const int componentId;
	const int infinity = numeric_limits<int>::max();

	mt19937& generator;
	discrete_distribution<> discreteDist;
	uniform_real_distribution<double> uniformDist;

	int countBetweenFailures;
	double reliability;
	bool isFaulty, verboseMode;

	vector<string> faultModesArray;
	vector<double> faultModesWeightArray;

	int currentFaultModeId;

	void loadFailModes(string dir);
};