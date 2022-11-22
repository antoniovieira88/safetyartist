// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/AnalysisUnit.h"
#include "./include/DataHandler.h"
#include "./include/CorrectOutputGenerator.h"
#include <string>

using namespace mlpack;
int main()
{
	arma::mat data, centroids, assignments;
	colvec newMetrics;

	std::cout << "CorrectOutputGenerator test started" << endl;

	int iteration;

	DataHandler dataHandler(1000);
	AnalysisUnit analysisUnit(2);
	CorrectOutputGenerator correctOutputGenerator(0.1, 0.9, 0.0, 0.3, 0.7, 1.0, 0.1, 0.01, 1);
	double correctOutputs[2];
	double fuseResultBurn, fuseResultNotBurn, fuseTest, stdDeviation;


	for (iteration = 1; iteration < 5; iteration++) {

		std::cout << "Begin of Iteration " << iteration << endl;

		dataHandler.loadHistoricalData();
		dataHandler.loadOldMetrics();
		
		fuseTest = 0.0;
		fuseResultBurn = correctOutputGenerator.generateOutput(fuseTest);
		stdDeviation = correctOutputGenerator.getStdDeviation();

		std::cout << "test_input = 0.0";
		std::cout << "standard_deviation_burn_test = " << stdDeviation << endl;
		std::cout << "fuse_result_burn_test = " << fuseResultBurn << endl;

		fuseTest = 1.0;
		fuseResultNotBurn = correctOutputGenerator.generateOutput(fuseTest);
		stdDeviation = correctOutputGenerator.getStdDeviation();

		std::cout << "test_input = 1.0";
		std::cout << "standard_deviation_not_burn_test = " << stdDeviation << endl;
		std::cout << "fuse_result_not_burn_test = " << fuseResultNotBurn << endl;

		dataHandler.insertNewHistoricalData(fuseResultBurn, fuseResultNotBurn);

		data = dataHandler.getHistoricalDataToCluster();

		analysisUnit.setDataToCluster(data);
		analysisUnit.cluster();
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

	std::cout << "CorrectOutputGenerator Test completed";

	return 0;
}