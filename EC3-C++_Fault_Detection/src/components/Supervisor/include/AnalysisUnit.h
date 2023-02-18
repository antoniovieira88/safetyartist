#include "../../../utils/kmeans/include/KMeans.h"
#include "../../../utils/enumerators/include/enum.h"

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
	mat dataToCluster, centroids;
	Row<size_t> assignments;
	mat initialCentroids;

	// Metrics for KMeans algorithm
	int numberOfClusters;
	int totalNumberOfPoints;
	double overallSilhouette;
	rowvec clusterSilhouettes;
	rowvec numberOfPointsPerCluster;
	colvec newMetrics;

	void appendMetric(colvec& newMetrics, double metric);
};