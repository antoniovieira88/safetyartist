#include "include/ProcessUnit.h"
#include <mlpack/core.hpp>
#include <cmath>

using namespace std;
ProcessUnit::ProcessUnit(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	double overallSilhouetteDecreaseTolerance, double silhouetteClustersDecreaseTolerance,
	double imbalanceClustersIncreaseTolerance): analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnit::supervised = supervised;

	ProcessUnit::overallSilhouetteDecreaseTolerance = overallSilhouetteDecreaseTolerance;
	ProcessUnit::silhouetteClustersDecreaseTolerance = silhouetteClustersDecreaseTolerance;
	ProcessUnit::imbalanceClustersIncreaseTolerance = imbalanceClustersIncreaseTolerance;

	initializeDataHandler();

	newMetrics = colvec(5, fill::zeros);
	verboseMode = false;
	keepPower = 0.0;
	fuseTest = NAN;
	silhouetteCluster1Increase = NAN;
	silhouetteCluster2Increase = NAN;
	imbalanceClustersIncrease = NAN;
	overallSilhouetteIncrease = NAN;
}

ProcessUnit::ProcessUnit(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	double overallSilhouetteDecreaseTolerance, double silhouetteClustersDecreaseTolerance,
	double imbalanceClustersIncreaseTolerance, bool verboseMode) : analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnit::supervised = supervised;

	ProcessUnit::overallSilhouetteDecreaseTolerance = overallSilhouetteDecreaseTolerance;
	ProcessUnit::silhouetteClustersDecreaseTolerance = silhouetteClustersDecreaseTolerance;
	ProcessUnit::imbalanceClustersIncreaseTolerance = imbalanceClustersIncreaseTolerance;
	ProcessUnit::verboseMode = verboseMode;

	initializeDataHandler();

	newMetrics = colvec(5, fill::zeros);
	keepPower = 0.0;
	fuseTest = NAN;
	silhouetteCluster1Increase = NAN;
	silhouetteCluster2Increase = NAN;
	imbalanceClustersIncrease = NAN;
	overallSilhouetteIncrease = NAN;

}

ProcessUnit::~ProcessUnit()
{
	dataHandler.saveNewMetrics();
	dataHandler.updateHistoricalData();

	if (verboseMode) {
		std::cout << endl << "Supervisor deactivated" << endl;
		std::cout << "HistoricalData.csv and HistoricalMetrics.csv updated in data menmory" << endl;
	}
}

void ProcessUnit::attach(Supervised* supervised)
{
	ProcessUnit::supervised = supervised;
}

void ProcessUnit::newTest()
{
	arma::mat data;
	double fuseResultBurn = NAN;
	double fuseResultNotBurn = NAN;
	bool failure = false;

	if (verboseMode) {
		std::cout << "Begin of a new test "  << endl;
		std::cout << "Iteration of the initiated test: " << iteration + 1 << endl;
	}

	keepPower = 1.0;
	fuseTest = 0.0;

	provideTestInput(fuseTest);
	fuseResultBurn = receiveTestOutput();

	if (verboseMode) {
		std::cout << "fuse_test = " << fuseTest;
		std::cout << "fuse_result_burn = " << fuseResultBurn << endl;
	}

	fuseTest = 1.0;

	provideTestInput(fuseTest);
	fuseResultNotBurn = receiveTestOutput();

	if (verboseMode) {
		std::cout << "fuse_test = " << fuseTest;
		std::cout << "fuse_result_not_burn = " << fuseResultBurn << endl;
	}

	dataHandler.insertNewHistoricalData(fuseResultBurn, fuseResultNotBurn);
	iteration = dataHandler.getIteration();
	data = dataHandler.getHistoricalDataToCluster();

	analysisUnit.setDataToCluster(data);
	analysisUnit.cluster();

	previousMetrics = dataHandler.getOldMetrics();
	newMetrics = analysisUnit.getNewMetrics();

	if (verboseMode) {
		std::cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints();
		std::cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		std::cout << "OverallSilhouette: " << newMetrics(4) << endl;
	}

	failure = detectFailure();

	if (failure) {
		exit(EXIT_FAILURE);
	}

	if (verboseMode) {
		std::cout << "End of the test. No failure detected. " << endl;
		std::cout << "Iteration of the finished test: " << iteration << endl;
	}

}

bool ProcessUnit::detectFailure()
{
	double silhouette1NewMetrics, silhouette2NewMetrics, imbalanceClustersNewMetrics, overallSilhouetteNewMetrics;
	double silhouette1PreviousMetrics, silhouette2PreviousMetrics, imbalanceClustersPreviousMetrics, overallSilhouettePreviousMetrics;
	bool failure = false;

	if (verboseMode) {
		std::cout << "Failure Detection process initiated" << endl;
	}

	silhouette1NewMetrics = newMetrics[0]; // silhouette of cluster 1
	silhouette2NewMetrics = newMetrics[1]; // silhouette of cluster 2
	imbalanceClustersNewMetrics = abs(newMetrics[3] - newMetrics[2]); // |number of points in cluster 2 - number of points in cluster 1|
	overallSilhouetteNewMetrics = newMetrics[4]; // overall silhouette

	silhouette1PreviousMetrics = previousMetrics[0]; // silhouette of cluster 1
	silhouette2PreviousMetrics = previousMetrics[1]; // silhouette of cluster 2
	imbalanceClustersPreviousMetrics = abs(previousMetrics[3] - previousMetrics[2]); // |number of points in cluster 2 - number of points in cluster 1|
	overallSilhouettePreviousMetrics = previousMetrics[4]; // overall silhouette

	// ! calculate the improvement in the metrics
	silhouetteCluster1Increase = silhouette1NewMetrics - silhouette1PreviousMetrics;
	silhouetteCluster2Increase = silhouette2NewMetrics - silhouette2PreviousMetrics;

	imbalanceClustersIncrease = imbalanceClustersNewMetrics - imbalanceClustersPreviousMetrics;

	overallSilhouetteIncrease = overallSilhouetteNewMetrics - overallSilhouettePreviousMetrics;

	if (verboseMode) {
		std::cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
		std::cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
		std::cout << "Increase in cluster imbalance: " << imbalanceClustersIncrease << endl;
		std::cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;
	}

	// ! compare metrics to determine failure
	if (silhouetteCluster1Increase <= -silhouetteClustersDecreaseTolerance) failure = true;
	if (silhouetteCluster2Increase <= -silhouetteClustersDecreaseTolerance) failure = true;

	if (imbalanceClustersIncrease >= imbalanceClustersIncreaseTolerance) failure = true;

	if (overallSilhouetteIncrease <= -overallSilhouetteDecreaseTolerance) failure = true;

	return failure;
}

void ProcessUnit::initializeDataHandler()
{
	dataHandler.loadHistoricalData();
	dataHandler.loadOldMetrics();

	previousMetrics = dataHandler.getOldMetrics();
	iteration = dataHandler.getIteration();

	if (verboseMode) {
		std::cout << "Data Handler initialized" << endl;
		std::cout << "Current Iteration: " << iteration << endl;
	}
}

void ProcessUnit::provideTestInput(double testInput)
{
	(*supervised).setTestInput(testInput);
}

double ProcessUnit::receiveTestOutput()
{
	return (*supervised).getTestOutput();
}

