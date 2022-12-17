#include <mlpack/core.hpp>

using namespace arma;
class AnalysisUnit {
	public:
		AnalysisUnit(int numberOfClusters);

		void cluster(mat initialCentroids, bool allowEmptyClusters);
		void cluster(mat initialCentroids);
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

		// Metrics for KMeans algorithm
		int numberOfClusters;
		int totalNumberOfPoints;
		double overallSilhouette;
		rowvec clusterSilhouettes;
		rowvec numberOfPointsPerCluster;
		colvec newMetrics;
};