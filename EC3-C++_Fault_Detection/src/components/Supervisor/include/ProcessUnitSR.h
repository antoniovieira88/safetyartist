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

private:
	AnalysisUnit& analysisUnit;
	DataHandler& dataHandlerFuseTest;
	DataHandler& dataHandlerKeepPowTest;
	Supervised* supervisedPointer;
	int& globalIteration;
	string simulationName;

	bool verboseMode;

	// fuseTest variables
	double fuseTest;
	double overallSilhouetteDecreaseToleranceFuseTest,
		silhouetteClustersDecreaseToleranceFuseTest,
		imbalanceClustersIncreaseToleranceFuseTest;
	colvec previousMetricsFuseTest, newMetricsFuseTest;

	// KeepPowTest
	int keepPower;
	double overallSilhouetteDecreaseToleranceKeepPowTest,
		silhouetteClustersDecreaseToleranceKeepPowTest,
		imbalanceClustersIncreaseToleranceKeepPowTest;
	colvec previousMetricsKeepPowTest, newMetricsKeepPowTest;

	faultDiagnosisType detectFailure(
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
};