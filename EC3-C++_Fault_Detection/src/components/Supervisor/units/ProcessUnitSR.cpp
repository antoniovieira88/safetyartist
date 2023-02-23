#include "../include/ProcessUnitSR.h"

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
	mat& nominalFuseResults,
	mat& nominalKeepPowReadbacks,
	int& globalIteration,
	bool verboseMode) :
	globalIteration(globalIteration),
	nominalFuseResults(nominalFuseResults),
	nominalKeepPowReadbacks(nominalKeepPowReadbacks),
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
	ProcessUnitSR::simulationName = "";
	ProcessUnitSR::lastPerfomedTest = test::none;

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

void ProcessUnitSR::runTest()
{
	globalIteration++;
	if (globalIteration % 2 == 1) {
		lastPerfomedTest = test::fuseTest;
		runFuseTest();
	}
	else {
		lastPerfomedTest = test::keepPowerTest;
		runKeepPowTest();
	}

}

void ProcessUnitSR::runFuseTest() {
	arma::mat dataToCluster;
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new diagnostic fuse test " << endl;
		cout << "Iteration of the initiated diagnostic test: " << globalIteration << endl;
	}

	keepPower = 1;
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

	analysisUnit.cluster(dataToCluster, nominalFuseResults);

	newMetricsFuseTest = analysisUnit.getNewMetrics();
	dataHandlerFuseTest.insertNewMetrics(newMetricsFuseTest);

	previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();

	if (verboseMode) {
		cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
		cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		cout << "OverallSilhouette: " << newMetricsFuseTest(overallSilhouette) << endl;
	}

	// all metrics are used in the FuseTest
	bool metricsToAnalyse[5];
	fill_n(metricsToAnalyse, 5, true);

	detectFailure(
		previousMetricsFuseTest,
		newMetricsFuseTest,
		metricsToAnalyse,
		imbalanceClustersIncreaseToleranceFuseTest,
		silhouetteClustersDecreaseToleranceFuseTest,
		overallSilhouetteDecreaseToleranceFuseTest);

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

void ProcessUnitSR::runKeepPowTest()
{
	arma::mat dataToCluster;
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new diagnostic keep power test " << endl;
		cout << "Iteration of the initiated diagnostic keep power test: " << globalIteration << endl;
	}

	fuseTest = 1.0;
	setFuseTest(fuseTest);

	keepPower = 1;

	setKeepPower(keepPower);
	keepPowerReadbackOn = getKeepPowReadback();

	if (verboseMode) {
		cout << "keep_power = " << keepPower << endl;
		cout << "keep_power_readback = " << keepPowerReadbackOn << endl;
	}

	keepPower = 0;
	setKeepPower(keepPower);
	keepPowerReadbackOff = getKeepPowReadback();

	if (verboseMode) {
		cout << "keep_power = " << keepPower << endl;
		cout << "keep_power_readback = " << keepPowerReadbackOff << endl;
	}

	keepPower = 1;
	setKeepPower(keepPower);

	mat keepPowerReadbacks = { {0, 1},
							  {double(keepPowerReadbackOff), double(keepPowerReadbackOn)} };

	dataHandlerKeepPowTest.insertNewHistoricalData(keepPowerReadbacks);
	dataToCluster = dataHandlerKeepPowTest.getHistoricalDataToCluster();

	analysisUnit.cluster(dataToCluster, nominalKeepPowReadbacks);

	bool metricsToAnalyse[5];
	fill_n(metricsToAnalyse, 5, false);
	// only the metrics below are used in KeepPowerTest.
	metricsToAnalyse[numPointsCluster1] = true;
	metricsToAnalyse[numPointsCluster2] = true;

	newMetricsKeepPowTest = analysisUnit.getNewMetrics(metricsToAnalyse);
	dataHandlerKeepPowTest.insertNewMetrics(newMetricsKeepPowTest);

	previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();

	if (verboseMode) {
		cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
		cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
	}

	detectFailure(
		previousMetricsKeepPowTest,
		newMetricsKeepPowTest,
		metricsToAnalyse,
		0.0,
		0.0,
		0);


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
	return supervisedPointer->getFuseResult();
}

int ProcessUnitSR::getKeepPowReadback()
{
	return supervisedPointer->getKeepPowReadback();
}

void ProcessUnitSR::reset()
{
	globalIteration = 0;
	dataHandlerFuseTest.reset();
	dataHandlerKeepPowTest.reset();
}

void ProcessUnitSR::detectFailure(
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
	bool anyMetricAnalysed = false;
	int metricIndex = 0;

	vector<FailureMetricIndicatorType> failureIndicators;

	if (verboseMode) {
		cout << "Failure detection process initiated" << endl;
	}

	// calculate the variation of each metric (the increase or decrease)
	// and then its compared to the tolerance value

	// silhouette of cluster 1
	if (metricsToAnalyse[silhouetteCluster1]) {
		anyMetricAnalysed = true;
		silhouetteCluster1Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
		metricIndex++;

		if (silhouetteCluster1Increase < -silhouetteClustersDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { silhouetteCluster1, silhouetteCluster1Increase, silhouetteClustersDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// silhouette of cluster 2
	if (metricsToAnalyse[silhouetteCluster2]) {
		anyMetricAnalysed = true;
		silhouetteCluster2Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
		metricIndex++;

		if (silhouetteCluster2Increase < -silhouetteClustersDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { silhouetteCluster2, silhouetteCluster2Increase, silhouetteClustersDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// |number of points in cluster 2 - number of points in cluster 1|
	if (metricsToAnalyse[numPointsCluster1] && metricsToAnalyse[numPointsCluster2]) {
		anyMetricAnalysed = true;
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
		anyMetricAnalysed = true;
		overallSilhouetteIncrease = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
		if (verboseMode) cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;

		if (overallSilhouetteIncrease < -overallSilhouetteDecreaseTolerance) {
			failure = true;
			FailureMetricIndicatorType failureIndicator = { overallSilhouette, overallSilhouetteIncrease, overallSilhouetteDecreaseTolerance, globalIteration };
			failureIndicators.push_back(failureIndicator);
		}
	}

	// it throws an exception if no metric has been analyzed
	if (!anyMetricAnalysed) throw exception();

	faultDiagnosis = { failure, failureIndicators, lastPerfomedTest };

	if (verboseMode) {
		cout << "Failure detection process finished" << endl;
	}
}

void ProcessUnitSR::initializeDataHandlers()
{
	if (verboseMode) cout << "Simulation Name: " << simulationName << endl;

	dataHandlerFuseTest.initializeDataHandler();
	dataHandlerKeepPowTest.initializeDataHandler();

	previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();
	int lastIterationFuseTest = dataHandlerFuseTest.getLastIterationInDataMemory();

	previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();
	int lastIterationKeepPowTest = dataHandlerKeepPowTest.getLastIterationInDataMemory();

	// the global iteration parameter is the maximum value between the iterations
	// values provided by the two dataHandler units

	globalIteration =
	{ lastIterationFuseTest > lastIterationKeepPowTest
		? lastIterationFuseTest
		: lastIterationKeepPowTest
	};
}

void ProcessUnitSR::getReadyForNextSimulationCycle()
{
	dataHandlerFuseTest.updateHistoricalData();
	dataHandlerFuseTest.updateHistoricalMetrics();


	dataHandlerKeepPowTest.updateHistoricalData();
	dataHandlerKeepPowTest.updateHistoricalMetrics();

	if (verboseMode) {
		cout << "HistoricalData.csv and HistoricalMetrics.csv for FuseTest and KeepPowerTest"
			<< "updated in data memory" << endl;
	}
}

void ProcessUnitSR::setVerboseMode(bool verboseModeValue)
{
	ProcessUnitSR::verboseMode = verboseModeValue;
}

void ProcessUnitSR::setSimulationName(string simulationName)
{
	ProcessUnitSR::simulationName = simulationName;
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

FuseTestResultsType ProcessUnitSR::getFuseTestResults()
{
	if (lastPerfomedTest == test::keepPowerTest) return {};

	MetricsFuseTestType newMetrics = getFuseTestMetricsStruct(newMetricsFuseTest);
	MetricsFuseTestType previousMetrics = getFuseTestMetricsStruct(previousMetricsFuseTest);

	return FuseTestResultsType({
		faultDiagnosis,
		previousMetrics,
		newMetrics,
		fuseResultBurn,
		fuseResultNotBurn });
}

KeepPowerTestResultsType ProcessUnitSR::getKeepPowerTestResults()
{
	if (lastPerfomedTest == test::fuseTest) return {};

	MetricsKeepPowerTestType newMetrics = getKeepPowerTestMetricsStruct(newMetricsKeepPowTest);
	MetricsKeepPowerTestType previousMetrics = getKeepPowerTestMetricsStruct(previousMetricsKeepPowTest);

	return KeepPowerTestResultsType(
		{ faultDiagnosis,
		previousMetrics,
		newMetrics,
		keepPowerReadbackOn,
		keepPowerReadbackOff });
}

test ProcessUnitSR::getLastPerfomedTest()
{
	return lastPerfomedTest;
}

void ProcessUnitSR::deleteRecordsFromLatestIteration()
{
	dataHandlerFuseTest.deleteRecordsFromLatestIteration();
	dataHandlerKeepPowTest.deleteRecordsFromLatestIteration();
	globalIteration -= 2;
}

void ProcessUnitSR::setKeepPower(int keepPower)
{
	supervisedPointer->setKeepPower(keepPower);
}

void ProcessUnitSR::setFuseTest(double fuseTest)
{
	supervisedPointer->setFuseTest(fuseTest);
}

MetricsFuseTestType ProcessUnitSR::getFuseTestMetricsStruct(colvec metricsArray)
{
	MetricsFuseTestType metricsStruct;
	metricsStruct.numPointsCluster1 = metricsArray[numPointsCluster1];
	metricsStruct.numPointsCluster2 = metricsArray[numPointsCluster2];
	metricsStruct.silhouetteCluster1 = metricsArray[silhouetteCluster1];
	metricsStruct.silhouetteCluster2 = metricsArray[silhouetteCluster2];
	metricsStruct.overallSilhouette = metricsArray[overallSilhouette];

	return metricsStruct;
}

MetricsKeepPowerTestType ProcessUnitSR::getKeepPowerTestMetricsStruct(colvec metricsArray) {
	MetricsKeepPowerTestType metricsStruct;
	metricsStruct.numPointsCluster1 = metricsArray[0];
	metricsStruct.numPointsCluster2 = metricsArray[1];

	return metricsStruct;
};