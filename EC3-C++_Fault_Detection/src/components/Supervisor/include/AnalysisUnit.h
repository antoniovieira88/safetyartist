#include <mlpack/core.hpp>
#include "../../../utils/kmeans/include/KMeans.h"

using namespace arma;

class AnalysisUnit {
public:
	AnalysisUnit(int numberOfClusters, mat& initialCentroids);

	void cluster(bool allowEmptyClusters);
	void cluster();

	colvec getNewMetrics();

	void setDataToCluster(mat dataToCluster);

	mat getCentroids();
	Row<size_t> getAssignments();
	int getTotalNumberOfPoints();
	int getNumberOfClusters();

private:
	// Data related to KMeans clusters
	mat dataToCluster, centroids;
	Row<size_t> assignments;
	mat& initialCentroids;

	// Metrics for KMeans algorithm
	int numberOfClusters;
	int totalNumberOfPoints;
	double overallSilhouette;
	rowvec clusterSilhouettes;
	rowvec numberOfPointsPerCluster;
	colvec newMetrics;
};