#include <vector>
#include <algorithm>
#include "AnalysisUnit.h"
#include "DataHandler.h"
#include "../../Supervised/include/Supervised.h"
#include "../../../utils/structs/structs.h"
#include "../../../utils/exceptions/include/FailureDetectedExcep.h"

using namespace std;

class ProcessUnitSR {
public:
	ProcessUnitSR(
		AnalysisUnit& analysisUnit,
		DataHandler& dataHandlerFuseTest,
		DataHandler& dataHandlerKeepPowTest,
		Supervised* supervised,
		mat& nominalFuseResults,
		mat& nominalKeepPowReadbacks,
		int& globalIteration,
		bool verboseMode = true);

	~ProcessUnitSR();

	void attach(Supervised* supervisedPointer);
	void runTest();
	void reset();
	void getReadyForNextSimulationCycle();
	void initializeDataHandlers();

	void setVerboseMode(bool verboseModeValue);
	void setSimulationName(string simulationName);
	void setFuseTestBasicParams(
		double overallSilhouetteToleranceValue,
		double silhouetteDiffToleranceValue,
		double numberOfPointsPerClusterDiffToleranceValue);

	FuseTestResultsType getFuseTestResults();
	KeepPowerTestResultsType getKeepPowerTestResults();
	test getLastPerfomedTest();

	void deleteRecordsFromLatestIteration();

	void clearControlFlowProcessUnitSR();

private:
	AnalysisUnit& analysisUnit;
	DataHandler& dataHandlerFuseTest;
	DataHandler& dataHandlerKeepPowTest;
	Supervised* supervisedPointer;
	mat& nominalFuseResults;
	mat& nominalKeepPowReadbacks;
	int& globalIteration;
	string simulationName;
	FaultDiagnosisType faultDiagnosis;
	test lastPerfomedTest;

	bool verboseMode;

	// fuseTest variables
	double fuseTest;
	double fuseResultBurn;
	double fuseResultNotBurn;
	double overallSilhouetteDecreaseToleranceFuseTest,
		silhouetteClustersDecreaseToleranceFuseTest,
		imbalanceClustersIncreaseToleranceFuseTest;
	colvec previousMetricsFuseTest, newMetricsFuseTest;

	// KeepPowTest
	int keepPower;
	int keepPowerReadbackOn;
	int keepPowerReadbackOff;
	double overallSilhouetteDecreaseToleranceKeepPowTest,
		silhouetteClustersDecreaseToleranceKeepPowTest,
		imbalanceClustersIncreaseToleranceKeepPowTest;
	colvec previousMetricsKeepPowTest, newMetricsKeepPowTest;

	void detectFailure(
		colvec& previousMetrics,
		colvec& newMetrics,
		bool metricsToAnalyse[5],
		double imbalanceClustersIncreaseTolerance = 0.0,
		double silhouetteClustersDecreaseTolerance = 0.0,
		double overallSilhouetteDecreaseTolerance = 0.0);

	void runFuseTest();
	void runKeepPowTest();
	double calculateMetricVariation(
		colvec& previousMetrics,
		colvec& newMetrics,
		int metricIndex);

	double getFuseResult();
	int getKeepPowReadback();
	void setKeepPower(int keepPower);
	void setFuseTest(double fuseTest);

	MetricsFuseTestType getFuseTestMetricsStruct(colvec metricsArray);
	MetricsKeepPowerTestType getKeepPowerTestMetricsStruct(colvec metricsArray);

	// Control flow attributes - one attribute per method (except for the constructor)
	// False indicates that the method is not currently running; true indicates that a prior call is running
	bool controlFlowAttach;
	bool controlFlowRunTest;
	bool controlFlowReset;
	bool controlFlowGetReadyForNextSimulationCycle;
	bool controlFlowInitializeDataHandlers;
	bool controlFlowSetFuseTestBasicParams;
	bool controlFlowGetFuseTestResults;
	bool controlFlowGetKeepPowerTestResults;
	bool controlFlowGetLastPerfomedTest;
	bool controlFlowDeleteRecordsFromLatestIteration;
	bool controlFlowclearControlFlowProcessUnitSR;
	bool controlFlowDetectFailure;
	bool controlFlowRunFuseTest;
	bool controlFlowRunKeepPowTest;
	bool controlFlowCalculateMetricVariation;
	bool controlFlowGetFuseResult;
	bool controlFlowGetKeepPowReadback;
	bool controlFlowSetKeepPower;
	bool controlFlowSetFuseTest;
	bool controlFlowGetFuseTestMetricsStruct;
	bool controlFlowGetKeepPowerTestMetricsStruct;
};