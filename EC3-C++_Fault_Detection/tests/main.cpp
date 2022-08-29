// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/KMeans.h"
#include "./include/DataHandler.h"

// Convenience.
using namespace mlpack;
int main()
{
	arma::mat data;
	data::Load("data/data.csv", data, true);

	std::cout << "Test started" << endl;

	KMeans KClusters(data, 2);

	int totalNumberOfPoints = KClusters.getData().n_cols;
	int numberOfClusters = KClusters.getNumberOfClusters();
	double overallSilhouette = KClusters.getOverallSilhouette();
	rowvec clusterSilhouettes = KClusters.getClustersSilhouettes();
	rowvec numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();

	DataHandler dataHandler;

	std::cout << "Number of clusters: " << numberOfClusters << endl;

	std::cout << "OverallSilhouette: " << overallSilhouette << endl;

	int i;

	for (i = 0; i < numberOfPointsPerCluster.n_cols; i++) {
		std::cout << "Number of points in cluster" << i << ": " << numberOfPointsPerCluster(i) << endl;
	}

	for (i = 0; i < clusterSilhouettes.n_cols; i++) {
		std::cout << "Silhouette of cluster" << i << ": " << clusterSilhouettes(i) << endl;
	}

	dataHandler.loadOldMetrics();
	dataHandler.setNewMetrics(clusterSilhouettes, numberOfPointsPerCluster, overallSilhouette);
	dataHandler.saveNewMetrics();


	data::Save("data/assignments.csv", KClusters.getAssigments(), true);
	data::Save("data/newCentroids.csv", KClusters.getCentroids(), true);
	data::Save("data/SilhouetteIndividually.csv", KClusters.getIndividualSilhouette(), true);
	data::Save("data/SilhouetteClusters.csv", clusterSilhouettes, true);

	std::cout << "Test completed";

	return 0;
}