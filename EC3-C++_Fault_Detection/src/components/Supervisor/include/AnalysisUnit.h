#include "../../../utils/kmeans/include/KMeans.h"
#include "../../../utils/enumerators/enum.h"
#include "../../../utils/exceptions/include/SimulatorFailureExcep.h"

using namespace arma;

class AnalysisUnit {
public:
	AnalysisUnit(int numberOfClusters);

	void cluster(mat& dataToCluster, mat& initialCentroids, bool allowEmptyClusters = true);

	colvec getNewMetrics();
	colvec getNewMetrics(bool metricsToAnalyse[5]);

	mat getCentroids();
	Row<size_t> getAssignments();
	int getTotalNumberOfPoints();
	int getNumberOfClusters();

private:
	// Data related to KMeans clusters
	mat centroids;
	Row<size_t> assignments;
	mat initialCentroids;

	// Metrics for KMeans algorithm
	int numberOfClusters;
	int totalNumberOfPoints;
	double overallSilhouette;
	rowvec clusterSilhouettes;
	rowvec numberOfPointsPerCluster;
	colvec newMetrics;

	// Method to append new metrics to metrics history for DataHandler
	void appendMetric(colvec& newMetrics, double metric);

	// Control flow attributes - one attribute per method (except for the constructor)
	// False indicates that the method is not currently running; true indicates that a prior call is running
	bool controlFlowCluster;
	bool controlFlowGetNewMetricsEmptyAttributes;
	bool controlFlowGetNewMetricsWithAttributes;
	bool controlFlowGetCentroids;
	bool controlFlowGetAssignments;
	bool controlFlowGetTotalNumberOfPoints;
	bool controlFlowGetNumberOfClusters;
	bool controlFlowAppendMetric;
};