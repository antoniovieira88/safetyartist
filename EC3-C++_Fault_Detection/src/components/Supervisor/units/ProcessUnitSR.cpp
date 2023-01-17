#include "../include/ProcessUnitSR.h"
#include <cmath>
#include <vector>

using namespace std;

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
	AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	bool verboseMode) :
	analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnitSR::supervisedPointer = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseTolerance = NAN;
	ProcessUnitSR::silhouetteClustersDecreaseTolerance = NAN;
	ProcessUnitSR::imbalanceClustersIncreaseTolerance = NAN;
	ProcessUnitSR::verboseMode = verboseMode;

	newMetrics = colvec(5, fill::zeros);
	keepPower = 1.0;
	fuseTest = 1.0;
}

ProcessUnitSR::ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	double overallSilhouetteDecreaseTolerance, double silhouetteClustersDecreaseTolerance,
	double imbalanceClustersIncreaseTolerance, bool verboseMode = true) :
	analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnitSR::supervisedPointer = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseTolerance = overallSilhouetteDecreaseTolerance;
	ProcessUnitSR::silhouetteClustersDecreaseTolerance = silhouetteClustersDecreaseTolerance;
	ProcessUnitSR::imbalanceClustersIncreaseTolerance = imbalanceClustersIncreaseTolerance;
	ProcessUnitSR::verboseMode = verboseMode;

	newMetrics = colvec(5, fill::zeros);
	keepPower = 1.0;
	fuseTest = 1.0;

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
	arma::mat dataToCluster;
	double fuseResultBurn = (double NAN);
	double fuseResultNotBurn = (double NAN);
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new diagnostic test " << endl;
		cout << "Iteration of the initiated diagnostic test: " << *iterationPointer + 1 << endl;
	}

	keepPower = 1.0;
	fuseTest = 0.0;

	provideTestInput(fuseTest);
	fuseResultBurn = receiveTestOutput();

	if (verboseMode) {
		cout << "fuse_test = " << fuseTest << endl;
		cout << "fuse_result_burn = " << fuseResultBurn << endl;
	}

	fuseTest = 1.0;

	provideTestInput(fuseTest);
	fuseResultNotBurn = receiveTestOutput();

	if (verboseMode) {
		cout << "fuse_test = " << fuseTest << endl;
		cout << "fuse_result_not_burn = " << fuseResultNotBurn << endl;
	}

	dataHandler.insertNewHistoricalData(fuseResultBurn, fuseResultNotBurn);
	dataToCluster = dataHandler.getHistoricalDataToCluster();

	analysisUnit.setDataToCluster(dataToCluster);
	analysisUnit.cluster();


	newMetrics = analysisUnit.getNewMetrics();
	dataHandler.insertNewMetrics(newMetrics);

	previousMetrics = dataHandler.getPreviousMetrics();

	if (verboseMode) {
		cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
		cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		cout << "OverallSilhouette: " << newMetrics(overallSilhouette) << endl;
	}

	faultDiagnosisType faultDiagnosis = detectFailure();

	if (faultDiagnosis.failure) {
		keepPower = 0.0;
		throw FailureDetectedExcep(faultDiagnosis);
	}

	else if (verboseMode) {
		cout << "-> End of the diagnostic test. No failure detected. " << endl;
		cout << "Iteration of the finished diagnostic test: " << *iterationPointer << endl;
	}

}

void ProcessUnitSR::reset()
{
	dataHandler.reset();
}

faultDiagnosisType ProcessUnitSR::detectFailure()
{
	double silhouette1NewMetrics, silhouette2NewMetrics, imbalanceClustersNewMetrics, overallSilhouetteNewMetrics;
	double silhouette1PreviousMetrics, silhouette2PreviousMetrics, imbalanceClustersPreviousMetrics, overallSilhouettePreviousMetrics;
	double silhouetteCluster1Increase, silhouetteCluster2Increase, imbalanceClustersIncrease, overallSilhouetteIncrease;
	bool failure = false;
	vector<FailureMetricIndicatorType> failureIndicators;

	if (verboseMode) {
		cout << "Failure detection process initiated" << endl;
	}

	silhouette1NewMetrics = newMetrics[silhouetteCluster1]; // silhouette of cluster 1
	silhouette2NewMetrics = newMetrics[silhouetteCluster2]; // silhouette of cluster 2
	imbalanceClustersNewMetrics = abs(newMetrics[numPointsCluster1] - newMetrics[numPointsCluster2]); // |number of points in cluster 2 - number of points in cluster 1|
	overallSilhouetteNewMetrics = newMetrics[overallSilhouette]; // overall silhouette

	silhouette1PreviousMetrics = previousMetrics[silhouetteCluster1]; // silhouette of cluster 1
	silhouette2PreviousMetrics = previousMetrics[silhouetteCluster2]; // silhouette of cluster 2
	imbalanceClustersPreviousMetrics = abs(previousMetrics[numPointsCluster1] - previousMetrics[numPointsCluster2]); // |number of points in cluster 2 - number of points in cluster 1|
	overallSilhouettePreviousMetrics = previousMetrics[overallSilhouette]; // overall silhouette

	// ! calculate the improvement in the metrics
	silhouetteCluster1Increase = silhouette1NewMetrics - silhouette1PreviousMetrics;
	silhouetteCluster2Increase = silhouette2NewMetrics - silhouette2PreviousMetrics;

	imbalanceClustersIncrease = imbalanceClustersNewMetrics - imbalanceClustersPreviousMetrics;

	overallSilhouetteIncrease = overallSilhouetteNewMetrics - overallSilhouettePreviousMetrics;

	if (verboseMode) {
		cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
		cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
		cout << "Increase in cluster imbalance: " << imbalanceClustersIncrease << endl;
		cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;
	}

	// ! compare metrics to determine failure
	if (silhouetteCluster1Increase <= -silhouetteClustersDecreaseTolerance) {
		failure = true;
		FailureMetricIndicatorType failureIndicator = { silhouetteCluster1, silhouetteCluster1Increase, silhouetteClustersDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}
	if (silhouetteCluster2Increase <= -silhouetteClustersDecreaseTolerance) {
		failure = true;
		FailureMetricIndicatorType failureIndicator = { silhouetteCluster2, silhouetteCluster2Increase, silhouetteClustersDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	if (imbalanceClustersIncrease > imbalanceClustersIncreaseTolerance) {
		failure = true;
		FailureMetricIndicatorType failureIndicator = { imbalanceNumPoints, imbalanceClustersIncrease, imbalanceClustersIncreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	if (overallSilhouetteIncrease <= -overallSilhouetteDecreaseTolerance) {
		failure = true;
		FailureMetricIndicatorType failureIndicator = { overallSilhouette, overallSilhouetteIncrease, overallSilhouetteDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	faultDiagnosisType faultDiagnosis{ failure, failureIndicators };

	if (verboseMode) {
		cout << "Failure detection process finished" << endl;
	}

	return faultDiagnosis;
}

void ProcessUnitSR::initializeDataHandler(string simulationName)
{
	dataHandler.setSimulationName(simulationName);

	int numRowsHistoricalData = dataHandler.loadHistoricalData();
	int numRowsHistoricalMetrics = dataHandler.loadHistoricalMetrics();

	previousMetrics = dataHandler.getPreviousMetrics();
	iterationPointer = dataHandler.getIterationPointer();

	if (verboseMode) {
		cout << "Data Handler initialized" << endl;
		cout << "Simulation Name: " << simulationName << endl;
		cout << "Number of rows in HistoricalData.csv: " << numRowsHistoricalData << endl;
		cout << "Number of rows in HistoricalMetrics.csv: " << numRowsHistoricalMetrics << endl;
	}
}

void ProcessUnitSR::getReadyForNextSimulationCycle()
{
	dataHandler.updateHistoricalData();
	dataHandler.updateHistoricalMetrics();

	if (verboseMode) {
		cout << "HistoricalData.csv and HistoricalMetrics.csv updated in data memory" << endl;
	}
}

void ProcessUnitSR::setVerboseMode(bool verboseModeValue)
{
	ProcessUnitSR::verboseMode = verboseModeValue;
}

void ProcessUnitSR::setBasicParams(
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue)
{
	ProcessUnitSR::overallSilhouetteDecreaseTolerance = overallSilhouetteToleranceValue;
	ProcessUnitSR::silhouetteClustersDecreaseTolerance = silhouetteDiffToleranceValue;
	ProcessUnitSR::imbalanceClustersIncreaseTolerance = numberOfPointsPerClusterDiffToleranceValue;
}

void ProcessUnitSR::provideTestInput(double testInput)
{
	supervisedPointer->setTestInput(testInput);
}

double ProcessUnitSR::receiveTestOutput()
{
	return supervisedPointer->getTestOutput();
}

