// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "../../src/utils/kmeans/include/KMeans.h"
#include "../../src/components/Supervisor/include/DataHandler.h"

// Convenience.
using namespace std;
int KMeansTest3()
{
	arma::mat data, centroids;
	mlpack::data::Load("tests/data/TestsKMeansSilhouette/Example3/data.csv", data, true);
	mlpack::data::Load("tests/data/TestsKMeansSilhouette/Example3/centroids.csv", centroids, true);

	cout << "Test started" << endl;

	KMeansEC KClusters(data, 3, centroids, false);

	int totalNumberOfPoints = KClusters.getData().n_cols;
	int numberOfClusters = KClusters.getNumberOfClusters();
	double overallSilhouette = KClusters.getOverallSilhouette();
	arma::rowvec clusterSilhouettes = KClusters.getClustersSilhouettes();
	arma::rowvec numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();

	cout << "Number of clusters: " << numberOfClusters << endl;

	cout << "OverallSilhouette: " << overallSilhouette << endl;

	int i;

	for (i = 0; i < numberOfPointsPerCluster.n_cols; i++) {
		cout << "Number of points in cluster" << i << ": " << numberOfPointsPerCluster(i) << endl;
	}

	for (i = 0; i < clusterSilhouettes.n_cols; i++) {
		cout << "Silhouette of cluster" << i << ": " << clusterSilhouettes(i) << endl;
	}

	mlpack::data::Save("tests/data/TestsKMeansSilhouette/Example3/assignments.csv", KClusters.getAssigments(), true);
	mlpack::data::Save("tests/data/TestsKMeansSilhouette/Example3/newCentroids.csv", KClusters.getCentroids(), true);
	mlpack::data::Save("tests/data/TestsKMeansSilhouette/Example3/SilhouetteIndividually.csv", KClusters.getIndividualSilhouette(), true);
	mlpack::data::Save("tests/data/TestsKMeansSilhouette/Example3/SilhouetteClusters.csv", clusterSilhouettes, true);

	cout << "Test completed";

	return 0;
}