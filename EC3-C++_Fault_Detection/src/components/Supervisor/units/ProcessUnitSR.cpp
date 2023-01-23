#include "../include/ProcessUnitSR.h"
#include <vector>

/*

In this case, it was used the 'reference' cpp operator ('&') so that "ProcessUnitSR" class directly receives
the addresses of "analysisUnit" and "dataHandler" objects instantiated in the "Supervisor"
class - where "Process Unit" is also created. As a result, ProcessUnitSR stores references to "analysisUnit"
and "dataHandler" objects as class members

Obs.: When a variable of the type 'reference' is used, it is not necessary to append the pointer operator "*" to access
the pointed data - it is accessed simply by its name. If the operator '&' were not used,
an undesired copy of "analysisUnit" and "dataHandler" objects  would be created every time ProcessUnitSR constructor is called.
Moreover, reference members must be initialized using Initializer List.

*/
ProcessUnitSR::ProcessUnitSR(
	AnalysisUnit& analysisUnit,
	DataHandler& dataHandlerFuseTest,
	DataHandler& dataHandlerKeepPowTest,
	Supervised* supervised,
	int& globalIteration,
	bool verboseMode) :
	globalIteration(globalIteration),
	analysisUnit(analysisUnit),
	dataHandlerFuseTest(dataHandlerFuseTest),
	dataHandlerKeepPowTest(dataHandlerKeepPowTest)
{
	ProcessUnitSR::supervisedPointer = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseToleranceFuseTest = NAN;
	ProcessUnitSR::silhouetteClustersDecreaseToleranceFuseTest = NAN;
	ProcessUnitSR::imbalanceClustersIncreaseToleranceFuseTest = NAN;
	ProcessUnitSR::silhouetteClustersDecreaseToleranceKeepPowTest = NAN;
	ProcessUnitSR::imbalanceClustersIncreaseToleranceKeepPowTest = NAN;
	ProcessUnitSR::verboseMode = verboseMode;

	newMetricsFuseTest = colvec(dataHandlerFuseTest.getNumberOfMetrics(), fill::zeros);
	previousMetricsFuseTest = colvec(dataHandlerFuseTest.getNumberOfMetrics(), fill::zeros);

	newMetricsKeepPowTest = colvec(dataHandlerKeepPowTest.getNumberOfMetrics(), fill::zeros);
	previousMetricsKeepPowTest = colvec(dataHandlerKeepPowTest.getNumberOfMetrics(), fill::zeros);

	fuseTest = 1.0;
	keepPower = 0.0;
}

ProcessUnitSR::~ProcessUnitSR()
{
	if (verboseMode) {
		cout << endl << "Supervisor deactivated" << endl;
	}
}

void ProcessUnitSR::attach(Supervised* supervisedPointer)
{
	ProcessUnitSR::supervisedPointer = supervisedPointer;

	if (verboseMode) {
		cout << endl << "Supervised attached to supervisor" << endl;
	}
}

// ! it needs re-factor!
void ProcessUnitSR::runTest()
{
	globalIteration++;
	if (globalIteration % 2 == 1) {
		runFuseTest();
	}
	else {
		// runKeepPowTest();
	}

}

void ProcessUnitSR::runFuseTest() {
	arma::mat dataToCluster;
	double fuseResultBurn = (double NAN);
	double fuseResultNotBurn = (double NAN);
	double keepPower(double NAN);
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new diagnostic fuse test " << endl;
		cout << "Iteration of the initiated diagnostic test: " << globalIteration << endl;
	}

	keepPower = 1.0;
	setKeepPower(keepPower);

	fuseTest = 0.0;
	setFuseTest(fuseTest);

	fuseResultBurn = getFuseResult();

	if (verboseMode) {
		cout << "fuse_test = " << fuseTest << endl;
		cout << "fuse_result_burn = " << fuseResultBurn << endl;
	}

	fuseTest = 1.0;
	setFuseTest(fuseTest);

	fuseResultNotBurn = getFuseResult();

	if (verboseMode) {
		cout << "fuse_test = " << fuseTest << endl;
		cout << "fuse_result_not_burn = " << fuseResultNotBurn << endl;
	}

	mat fuseResults = { {0.0, 1.0},
					 {fuseResultBurn, fuseResultNotBurn} };

	dataHandlerFuseTest.insertNewHistoricalData(fuseResults);
	dataToCluster = dataHandlerFuseTest.getHistoricalDataToCluster();

	analysisUnit.setDataToCluster(dataToCluster);
	analysisUnit.cluster();


	newMetricsFuseTest = analysisUnit.getNewMetrics();
	dataHandlerFuseTest.insertNewMetrics(newMetricsFuseTest);

	previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();

	if (verboseMode) {
		cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
		cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		cout << "OverallSilhouette: " << newMetricsFuseTest(overallSilhouette) << endl;
	}

	bool metricsToAnalyse[5] = { true };
	faultDiagnosisType faultDiagnosis = detectFailure(
		previousMetricsFuseTest,
		newMetricsFuseTest,
		metricsToAnalyse,
		overallSilhouetteDecreaseToleranceFuseTest,
		silhouetteClustersDecreaseToleranceFuseTest,
		imbalanceClustersIncreaseToleranceFuseTest);

	if (faultDiagnosis.failure) {
		keepPower = 0.0;
		setKeepPower(keepPower);
		throw FailureDetectedExcep(faultDiagnosis);
	}

	else if (verboseMode) {
		cout << "-> End of the diagnostic fuse test. No failure detected. " << endl;
		cout << "Iteration of the finished diagnostic fuse test: " << globalIteration << endl;
	}
}

// ! not completed yet!!
void ProcessUnitSR::runKeepPowTest()
{
	arma::mat dataToCluster;
	double keepPowerReadbackOn = (double NAN);
	double keepPowerReadbackOff = (double NAN);
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new diagnostic keep power test " << endl;
		cout << "Iteration of the initiated diagnostic keep power test: " << globalIteration << endl;
	}

	fuseTest = 1.0;
	setFuseTest(fuseTest);

	keepPower = 1.0;

	setKeepPower(keepPower);
	keepPowerReadbackOn = getKeepPowReadback();

	if (verboseMode) {
		cout << "keep_power = " << fuseTest << endl;
		cout << "keep_power_readback = " << keepPowerReadbackOn << endl;
	}

	keepPower = 0.0;
	setKeepPower(keepPower);
	keepPowerReadbackOff = getKeepPowReadback();

	if (verboseMode) {
		cout << "keep_power = " << keepPower << endl;
		cout << "keep_power_readback = " << keepPowerReadbackOff << endl;
	}

	mat keepPowerReadbacks = { {1.0, 0.0},
							  {keepPowerReadbackOn, keepPowerReadbackOff} };

	dataHandlerKeepPowTest.insertNewHistoricalData(keepPowerReadbacks);
	dataToCluster = dataHandlerKeepPowTest.getHistoricalDataToCluster();

	analysisUnit.setDataToCluster(dataToCluster);
	analysisUnit.cluster();


	newMetricsKeepPowTest = analysisUnit.getNewMetrics();
	dataHandlerKeepPowTest.insertNewMetrics(newMetricsKeepPowTest);

	previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();

	if (verboseMode) {
		cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
		cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		cout << "SilhouetteCluster2 (keep_power_readback = 1): " << newMetricsKeepPowTest(silhouetteCluster2) << endl;
	}

	bool metricsToAnalyse[5] = { false };
	metricsToAnalyse[numPointsCluster1]
		= metricsToAnalyse[numPointsCluster2]
		= metricsToAnalyse[silhouetteCluster2] = true;

	// ! it needs to change!!
	faultDiagnosisType faultDiagnosis = detectFailure(
		previousMetricsKeepPowTest,
		newMetricsKeepPowTest,
		metricsToAnalyse,
		overallSilhouetteDecreaseToleranceFuseTest,
		silhouetteClustersDecreaseToleranceFuseTest,
		imbalanceClustersIncreaseToleranceFuseTest);

	if (faultDiagnosis.failure) {
		fuseTest = 0.0;
		setFuseTest(fuseTest);
		throw FailureDetectedExcep(faultDiagnosis);
	}

	else if (verboseMode) {
		cout << "-> End of the diagnostic keep power test. No failure detected. " << endl;
		cout << "Iteration of the finished diagnostic keep power test: " << globalIteration << endl;
	}
}

double ProcessUnitSR::calculateMetricVariation(
	colvec& previousMetrics,
	colvec& newMetrics,
	int metricIndex)
{
	return newMetrics[metricIndex] - previousMetrics[metricIndex];
}

double ProcessUnitSR::getFuseResult()
{
	return supervisedPointer->runFuseTest();
}

double ProcessUnitSR::getKeepPowReadback()
{
	return supervisedPointer->runKeepPowTest();
}


void ProcessUnitSR::reset()
{
	globalIteration = 0;
	dataHandlerFuseTest.reset();
	dataHandlerKeepPowTest.reset();
}

faultDiagnosisType ProcessUnitSR::detectFailure(
	colvec& previousMetrics,
	colvec& newMetrics,
	bool metricsToAnalyse[5],
	double imbalanceClustersIncreaseTolerance,
	double silhouetteClustersDecreaseTolerance,
	double overallSilhouetteDecreaseTolerance
)
{
	double imbalanceClustersNewMetrics, imbalanceClustersPreviousMetrics;
	double silhouetteCluster1Increase, silhouetteCluster2Increase,
		imbalanceClustersIncrease, overallSilhouetteIncrease;
	bool failure = false;
	int metricIndex = 0;

	vector<FailureMetricIndicatorType> failureIndicators;

	if (verboseMode) {
		cout << "Failure detection process initiated" << endl;
	}

	// calculate the variation of each metric (the increase or decrease)
	// and then its compared to the tolerance value

	// silhouette of cluster 1
	if (metricsToAnalyse[silhouetteCluster1]) {
		silhouetteCluster1Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
		metricIndex++;

		if (silhouetteCluster1Increase <= -silhouetteClustersDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { silhouetteCluster1, silhouetteCluster1Increase, silhouetteClustersDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// silhouette of cluster 2
	if (metricsToAnalyse[silhouetteCluster2]) {
		silhouetteCluster2Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
		metricIndex++;

		if (silhouetteCluster2Increase <= -silhouetteClustersDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { silhouetteCluster2, silhouetteCluster2Increase, silhouetteClustersDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// |number of points in cluster 2 - number of points in cluster 1|
	if (metricsToAnalyse[numPointsCluster1] && metricsToAnalyse[numPointsCluster2]) {
		imbalanceClustersNewMetrics = abs(newMetrics[metricIndex + 1] - newMetrics[metricIndex]);
		imbalanceClustersPreviousMetrics = abs(previousMetrics[metricIndex + 1] - previousMetrics[metricIndex]);
		imbalanceClustersIncrease = imbalanceClustersNewMetrics - imbalanceClustersPreviousMetrics;
		if (verboseMode) cout << "Increase in cluster imbalance: " << imbalanceClustersIncrease << endl;
		metricIndex += 2;

		if (imbalanceClustersIncrease > imbalanceClustersIncreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { imbalanceNumPoints, imbalanceClustersIncrease, imbalanceClustersIncreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// overall silhouette
	if (metricsToAnalyse[overallSilhouette]) {
		overallSilhouetteIncrease = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;

		if (overallSilhouetteIncrease <= -overallSilhouetteDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { overallSilhouette, overallSilhouetteIncrease, overallSilhouetteDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	faultDiagnosisType faultDiagnosis{ failure, failureIndicators };

	if (verboseMode) {
		cout << "Failure detection process finished" << endl;
	}

	return faultDiagnosis;
}

// ! modify here later
void ProcessUnitSR::initializeDataHandler(string simulationName)
{
	if (verboseMode) cout << "Simulation Name: " << simulationName << endl;

	dataHandlerFuseTest.initializeDataHandler(simulationName);
	// ! uncomment only after the KeepPowTest feature be added
	/*dataHandlerKeepPowTest.initializeDataHandler(simulationName);*/

	previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();
	int lastIterationFuseTest = dataHandlerFuseTest.getLastIterationInDataMemory();

	// ! uncomment only after the KeepPowTest feature be added
	/*previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();
	int lastIterationKeepPowTest = dataHandlerKeepPowTest.getLastIterationInDataMemory();*/

	// the global iteration parameter is the maximum value between the iterations
	// values provided by the two dataHandler units

	// ! uncomment only after the KeepPowTest feature be added
	/*globalIteration = { lastIterationFuseTest > lastIterationKeepPowTest
		? lastIterationFuseTest
		: lastIterationKeepPowTest };*/

	globalIteration = lastIterationFuseTest;
}

// ! modify here later
void ProcessUnitSR::getReadyForNextSimulationCycle()
{
	dataHandlerFuseTest.updateHistoricalData();
	dataHandlerFuseTest.updateHistoricalMetrics();


	/*dataHandlerKeepPowTest.updateHistoricalData();
	dataHandlerKeepPowTest.updateHistoricalMetrics();*/

	// ! modify here later
	if (verboseMode) {
		cout << "HistoricalData.csv and HistoricalMetrics.csv for Fuse Test"
			<< "updated in data memory" << endl;
	}
}

void ProcessUnitSR::setVerboseMode(bool verboseModeValue)
{
	ProcessUnitSR::verboseMode = verboseModeValue;
}

void ProcessUnitSR::setFuseTestBasicParams(
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue)
{
	ProcessUnitSR::overallSilhouetteDecreaseToleranceFuseTest = overallSilhouetteToleranceValue;
	ProcessUnitSR::silhouetteClustersDecreaseToleranceFuseTest = silhouetteDiffToleranceValue;
	ProcessUnitSR::imbalanceClustersIncreaseToleranceFuseTest = numberOfPointsPerClusterDiffToleranceValue;
}

void ProcessUnitSR::setKeepPower(double keepPower)
{
	supervisedPointer->setKeepPower(keepPower);
}

void ProcessUnitSR::setFuseTest(double fuseTest)
{
	supervisedPointer->setFuseTest(fuseTest);
}
