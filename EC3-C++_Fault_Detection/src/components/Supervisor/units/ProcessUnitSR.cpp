#include "../include/ProcessUnitSR.h"
#include <cmath>
#include <vector>

using namespace std;

/*

In this case, it was used the 'reference' cpp operator ('&') so that "ProcessUnitSR" class directly receives
the addresses of "analysisUnit" and "dataHandler" objetcs instantiated in the "Supervisor"
class - where "Process Unit" is also created. As a result, ProcessUnitSR stores references to "analysisUnit"
and "dataHandler" objetcs as class members

Obs.: When a variable of the type 'reference' is used, it is not necessary to preappend the pointer operator "*" to access
the pointed data - it is accessed simply by its name. If the operator '&' were not used,
an undesired copy of "analysisUnit" and "dataHandler" objetcs  would be created every time ProcessUnitSR constructor is called.
Moreover, reference members must be initialized using Initializer List.

*/

ProcessUnitSR::ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	double overallSilhouetteDecreaseTolerance, double silhouetteClustersDecreaseTolerance,
	double imbalanceClustersIncreaseTolerance) : analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnitSR::supervised = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseTolerance = overallSilhouetteDecreaseTolerance;
	ProcessUnitSR::silhouetteClustersDecreaseTolerance = silhouetteClustersDecreaseTolerance;
	ProcessUnitSR::imbalanceClustersIncreaseTolerance = imbalanceClustersIncreaseTolerance;

	initializeDataHandler();

	newMetrics = colvec(5, fill::zeros);
	verboseMode = false;
	keepPower = 0.0;
	fuseTest = (double NAN);
}

ProcessUnitSR::ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
	double overallSilhouetteDecreaseTolerance, double silhouetteClustersDecreaseTolerance,
	double imbalanceClustersIncreaseTolerance, bool verboseMode) : analysisUnit(analysisUnit), dataHandler(dataHandler)
{
	ProcessUnitSR::supervised = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseTolerance = overallSilhouetteDecreaseTolerance;
	ProcessUnitSR::silhouetteClustersDecreaseTolerance = silhouetteClustersDecreaseTolerance;
	ProcessUnitSR::imbalanceClustersIncreaseTolerance = imbalanceClustersIncreaseTolerance;
	ProcessUnitSR::verboseMode = verboseMode;

	initializeDataHandler();

	newMetrics = colvec(5, fill::zeros);
	keepPower = 0.0;
	fuseTest = (double NAN);

}

ProcessUnitSR::~ProcessUnitSR()
{
	dataHandler.saveNewMetrics();
	dataHandler.updateHistoricalData();

	if (verboseMode) {
		cout << endl << "Supervisor deactivated" << endl;
		cout << "HistoricalData.csv and HistoricalMetrics.csv updated in data memory" << endl;
	}
}

void ProcessUnitSR::attach(Supervised* supervised)
{
	ProcessUnitSR::supervised = supervised;
}

void ProcessUnitSR::newTest()
{
	arma::mat data;
	double fuseResultBurn = (double NAN);
	double fuseResultNotBurn = (double NAN);
	bool failure = false;

	if (verboseMode) {
		cout << "Begin of a new test " << endl;
		cout << "Iteration of the initiated test: " << *iterationPointer + 1 << endl;
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
	data = dataHandler.getHistoricalDataToCluster();

	analysisUnit.setDataToCluster(data);
	analysisUnit.cluster();

	previousMetrics = dataHandler.getOldMetrics();
	newMetrics = analysisUnit.getNewMetrics();

	dataHandler.insertNewMetrics(newMetrics);

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
		cout << "End of the test. No failure detected. " << endl;
		cout << "Iteration of the finished test: " << *iterationPointer << endl;
	}

}

faultDiagnosisType ProcessUnitSR::detectFailure()
{
	double silhouette1NewMetrics, silhouette2NewMetrics, imbalanceClustersNewMetrics, overallSilhouetteNewMetrics;
	double silhouette1PreviousMetrics, silhouette2PreviousMetrics, imbalanceClustersPreviousMetrics, overallSilhouettePreviousMetrics;
	double silhouetteCluster1Increase, silhouetteCluster2Increase, imbalanceClustersIncrease, overallSilhouetteIncrease;
	bool failure = false;
	vector<failureMetricIndicatorType> failureIndicators;

	if (verboseMode) {
		std::cout << "Failure Detection process initiated" << endl;
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
		std::cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
		std::cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
		std::cout << "Increase in cluster imbalance: " << imbalanceClustersIncrease << endl;
		std::cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;
	}

	// ! compare metrics to determine failure
	if (silhouetteCluster1Increase <= -silhouetteClustersDecreaseTolerance) {
		failure = true;
		failureMetricIndicatorType failureIndicator = { silhouetteCluster1, silhouetteCluster1Increase, silhouetteClustersDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}
	if (silhouetteCluster2Increase <= -silhouetteClustersDecreaseTolerance) {
		failure = true;
		failureMetricIndicatorType failureIndicator = { silhouetteCluster2, silhouetteCluster2Increase, silhouetteClustersDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	if (imbalanceClustersIncrease > imbalanceClustersIncreaseTolerance) {
		failure = true;
		failureMetricIndicatorType failureIndicator = { imbalanceNumPoints, imbalanceClustersIncrease, imbalanceClustersIncreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	if (overallSilhouetteIncrease <= -overallSilhouetteDecreaseTolerance) {
		failure = true;
		failureMetricIndicatorType failureIndicator = { overallSilhouette, overallSilhouetteIncrease, overallSilhouetteDecreaseTolerance, *iterationPointer };
		failureIndicators.push_back(failureIndicator);
	}

	faultDiagnosisType faultDiagnosis{ failure, failureIndicators };

	return faultDiagnosis;
}

void ProcessUnitSR::initializeDataHandler()
{
	dataHandler.loadHistoricalData();
	dataHandler.loadOldMetrics();

	previousMetrics = dataHandler.getOldMetrics();
	iterationPointer = dataHandler.getIterationPointer();

	if (verboseMode) {
		std::cout << "Data Handler initialized" << endl;
		std::cout << "Current Iteration: " << *iterationPointer << endl;
	}
}

void ProcessUnitSR::provideTestInput(double testInput)
{
	(*supervised).setTestInput(testInput);
}

double ProcessUnitSR::receiveTestOutput()
{
	return (*supervised).getTestOutput();
}

