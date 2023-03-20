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

struct FaultDiagnosisType {
	bool failure;
	vector<FailureMetricIndicatorType> failureIndicators;
	test perfomedTest;
};

struct FailureScenarioFuseType {
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
	FailureScenarioFuseType fuseFailureScenario;
	FailureScenarioKeepPowType  keepPowFailureScenario;
};

struct FaultModeType {
	int id;
	int componentId;
	string name;
	double probability;
	fmSafety fmSafety;
	fmDetectable fmDetectableFuse;
	fmDetectable fmDetectableKeepPow;
	classMultipleFaults classMultipleFaults;
	FailureScenarioType singleFailureScenario;
};

struct TestScenarioType {
	int numberOfFailedComponents;
	bool outsideScopeFailureGenerated;
	bool detectableFailureGenerated;
	bool unsafeFailureGenerated;
	bool impactlessFailureGenerated;
	vector<FaultModeType*> newFaultModesArray;
	vector<int> failedComponentsIdArray;
	FailureScenarioFuseType* fuseFailureScenarioPointer;
	FailureScenarioKeepPowType* keepPowFailureScenarioPointer;
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

struct MetricsFuseTestType {
	double silhouetteCluster1;
	double silhouetteCluster2;
	double numPointsCluster1;
	double numPointsCluster2;
	double overallSilhouette;
};

struct MetricsKeepPowerTestType {
	double numPointsCluster1;
	double numPointsCluster2;
};

struct FuseTestResultsType {
	FaultDiagnosisType faultDiagnosis;
	MetricsFuseTestType previousMetrics;
	MetricsFuseTestType newMetrics;
	double fuseResultBurn;
	double fuseResultNotBurn;
};

struct KeepPowerTestResultsType {
	FaultDiagnosisType faultDiagnosis;
	MetricsKeepPowerTestType previousMetrics;
	MetricsKeepPowerTestType newMetrics;
	int keepPowerReadbackOn;
	int keepPowerReadbackOff;
};

struct FaultModeAnalysisResultType {
	string componentName;
	FaultModeType faultMode;
	FuseTestResultsType fuseTestResult;
	KeepPowerTestResultsType keepPowerTestResult;
};

struct FailureEventType {
	string componentName;
	FaultModeType faultMode;
	double reliability;
	double randNumGeneratedInFailure;
	test testName;
	int iteration;
	int iterationOnFailure;
	bool failureDetected;
	bool forcedEnd;
	FuseTestResultsType fuseTestResults;
	KeepPowerTestResultsType keepPowerTestResults;
};

struct InjectedFailureType {
	int hitIteration;
	FaultModeType* injectedFautMode;
};