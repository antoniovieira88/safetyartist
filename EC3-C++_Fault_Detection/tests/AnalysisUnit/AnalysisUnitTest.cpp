// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/AnalysisUnit.h"
#include "./include/DataHandler.h"
#include <string>

using namespace mlpack;
int AnalysisUnitTest()
{
	arma::mat data, centroids, assignments;
	colvec newMetrics;

	std::cout << "Data Memory test started" << endl;

	int iteration;

	DataHandler dataHandler(10);
	AnalysisUnit analysisUnit(2);

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

		analysisUnit.setDataToCluster(data);
		analysisUnit.cluster(true);
		newMetrics = analysisUnit.getNewMetrics();

		int totalNumberOfPoints = analysisUnit.getTotalNumberOfPoints();
		int numberOfClusters = analysisUnit.getNumberOfClusters();

		newMetrics = analysisUnit.getNewMetrics();

		double overallSilhouette = newMetrics(4);

		std::cout << "Number of clusters: " << numberOfClusters << endl;
		std::cout << "OverallSilhouette: " << overallSilhouette << endl;

		std::string path = "tests/data/TestsDataMemory/Iteration" + std::to_string(iteration);

		data::Save(path + "/assignments.csv", analysisUnit.getAssignments(), true);
		data::Save(path + "/centroids.csv", analysisUnit.getCentroids(), true);

		dataHandler.insertNewMetrics(newMetrics);

		dataHandler.saveNewMetrics();
		dataHandler.updateHistoricalData();

		std::cout << "End of Iteration " << iteration << endl;
		std::cout << " " << endl;

	}

	std::cout << "Data Memory Test completed";

	return 0;
}