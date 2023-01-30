#include "../enumerators/enum.h"
#include <vector>

#pragma once
using namespace std;

struct FailureMetricIndicatorType {
	metrics metric;
	double variation;
	double tolerance;
	int iteration;
};

struct FailureScenarioFuseTestType {
	double meanValueFuseResultBurn;
	double meanValueFuseResultNotBurn;
	double minFuseResultBurn;
	double maxFuseResultBurn;
	double minFuseResultNotBurn;
	double maxFuseResultNotBurn;
};

struct FailureScenarioKeepPowType {
	int keepPowerReadbackOffValue;
	int keepPowerReadbackOnValue;
};

struct FailureScenarioType {
	FailureScenarioFuseTestType fuseTestFailureScenario;
	FailureScenarioKeepPowType  keepPowFailureScenario;
};

struct TestScenarioType {
	int numberOfFailedComponents;
	vector<int> faultModesArray;
	FailureScenarioType* failureScenarioPointer;
};


struct SimulationSpecificParamsType {
	// Simulation controller
	unsigned int simulationSeed;
	double iterationEquivalentTime;
	// Supervisor
	double nominalFuseResultBurn;
	double nominalFuseResultNotBurn;
	double overallSilhouetteTolerance;
	double numberOfPointsPerClusterDiffTolerance;
	double silhouetteDiffTolerance;
	unsigned int maxNumberOfRegisters;
	// Supervised
	double minNominalFuseResultBurn;
	double maxNominalFuseResultBurn;
	double minNominalFuseResultNotBurn;
	double maxNominalFuseResultNotBurn;
	double maxStdDeviation;
};