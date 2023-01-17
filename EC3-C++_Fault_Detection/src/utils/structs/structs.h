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

struct FailureScenarioType {
	double meanValueFuseResultBurn;
	double meanValueFuseResultNotBurn;
	double minFuseResultBurn;
	double maxFuseResultBurn;
	double minFuseResultNotBurn;
	double maxFuseResultNotBurn;
};

struct TestScenarioType {
	int numberOfFailedComponents;
	vector<int> faultModesArray;
	FailureScenarioType* failureScenarioPointer;
};


struct SimulationSpecificParamsType {
	// Simulation controller
	int simulationSeed;
	double iterationEquivalentTime;
	// Supervisor
	double overallSilhouetteTolerance;
	double numberOfPointsPerClusterDiffTolerance;
	double silhouetteDiffTolerance;
	// Supervised
	double minNominalFuseResultBurn;
	double maxNominalFuseResultBurn;
	double minNominalFuseResultNotBurn;
	double maxNominalFuseResultNotBurn;
};