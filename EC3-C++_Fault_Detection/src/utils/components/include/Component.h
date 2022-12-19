#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

class Component {
public:
	Component(
		string name,
		double failureRate,
		double simulationStep,
		int countBetweenFailures,
		mt19937& generator);

	void loadFailModes(string dir);

	void calculateReliability();

	bool generateNewOperationalState();

	int getCurrentFaultMode();
	double getReliability();

private:
	const string name;
	const double faultRate, simulationStep;

	mt19937& generator;
	discrete_distribution<> discreteDist;
	uniform_real_distribution<double> uniformDist;

	int countBetweenFailures;
	double reliability;
	bool isFaulty;

	vector<string> faultModesArray;
	vector<double> faultModesWeightArray;

	int currentFaultMode;



};