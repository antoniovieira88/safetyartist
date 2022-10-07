// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/KMeans.h"
#include "./include/DataHandler.h"
#include <string>

// Convenience.
using namespace mlpack;
int DataHandlerTest()
{
	arma::mat data, centroids, assignments;

	std::cout << "Data Memory test started" << endl;

	int iteration;

	DataHandler dataHandler;

	for (iteration = 1; iteration < 6; iteration++) {

		std::cout << "Begin of Iteration " << iteration << endl;

		dataHandler.loadHistoricalData();
		dataHandler.loadOldMetrics();

		double fuse_result_burn_test = 0.05 * (iteration - 3) + 0.25;
		double fuse_result_not_burn_test = fuse_result_burn_test + 0.5;
		std::cout << "fuse_result_burn_test = " << fuse_result_burn_test << endl;
		std::cout << "fuse_result_not_burn_test = " << fuse_result_not_burn_test << endl;

		dataHandler.insertNewHistoricalData(fuse_result_burn_test, fuse_result_not_burn_test);

		data = dataHandler.getHistoricalDataToCluster();

		KMeans KClusters(data, 2, true);

		int totalNumberOfPoints = KClusters.getData().n_cols;
		int numberOfClusters = KClusters.getNumberOfClusters();
		double overallSilhouette = KClusters.getOverallSilhouette();
		rowvec clusterSilhouettes = KClusters.getClustersSilhouettes();
		rowvec numberOfPointsPerCluster = KClusters.getNumberOfPointsPerCluster();

		std::cout << "Number of clusters: " << numberOfClusters << endl;
		std::cout << "OverallSilhouette: " << overallSilhouette << endl;

		std::string path = "tests/data/TestsDataMemory/Iteration" + std::to_string(iteration);

		data::Save(path + "/assignments.csv", KClusters.getAssigments(), true);
		data::Save(path + "/centroids.csv", KClusters.getCentroids(), true);

		dataHandler.insertNewMetrics(clusterSilhouettes, numberOfPointsPerCluster, overallSilhouette);

		dataHandler.saveNewMetrics();
		dataHandler.updateHistoricalData();

		std::cout << "End of Iteration " << iteration << endl;
		std::cout << " " << endl;

	}

	std::cout << "Data Memory Test completed";

	return 0;
}