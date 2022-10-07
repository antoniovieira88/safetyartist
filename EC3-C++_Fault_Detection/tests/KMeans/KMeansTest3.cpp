// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/KMeans.h"
#include "./include/DataHandler.h"

// Convenience.
using namespace mlpack;
int KMeansTest3()
{
	arma::mat data, centroids;
	data::Load("tests/data/TestsKMeansSilhouette/Example3/data.csv", data, true);
	data::Load("tests/data/TestsKMeansSilhouette/Example3/centroids.csv", centroids, true);

	std::cout << "Test started" << endl;

	KMeans KClusters(data, 3, centroids, false);

	int totalNumberOfPoints = KClusters.getData().n_cols;
	int numberOfClusters = KClusters.getNumberOfClusters();
	double overallSilhouette = KClusters.getOverallSilhouette();
	rowvec clusterSilhouettes = KClusters.getClustersSilhouettes();
	rowvec numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();

	std::cout << "Number of clusters: " << numberOfClusters << endl;

	std::cout << "OverallSilhouette: " << overallSilhouette << endl;

	int i;

	for (i = 0; i < numberOfPointsPerCluster.n_cols; i++) {
		std::cout << "Number of points in cluster" << i << ": " << numberOfPointsPerCluster(i) << endl;
	}

	for (i = 0; i < clusterSilhouettes.n_cols; i++) {
		std::cout << "Silhouette of cluster" << i << ": " << clusterSilhouettes(i) << endl;
	}

	data::Save("tests/data/TestsKMeansSilhouette/Example3/assignments.csv", KClusters.getAssigments(), true);
	data::Save("tests/data/TestsKMeansSilhouette/Example3/newCentroids.csv", KClusters.getCentroids(), true);
	data::Save("tests/data/TestsKMeansSilhouette/Example3/SilhouetteIndividually.csv", KClusters.getIndividualSilhouette(), true);
	data::Save("tests/data/TestsKMeansSilhouette/Example3/SilhouetteClusters.csv", clusterSilhouettes, true);

	std::cout << "Test completed";

	return 0;
}