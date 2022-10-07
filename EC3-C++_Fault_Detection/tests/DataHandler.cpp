#include "include/DataHandler.h"
#include "../src/utils/exceptions/include/IncompatibleIterationExcep.h"
#include <mlpack/core.hpp>

using namespace arma;

DataHandler::DataHandler()
{
	previousMetrics = colvec(5, fill::zeros);
	newMetrics= colvec(5, fill::zeros);

}

void DataHandler::loadOldMetrics()
{
	try {
		mlpack::data::Load("data/DataMemory/HistoricalMetrics.csv", historicalMetrics, true);
		int size = historicalMetrics.n_cols;

		if (size > 0) {
			int iterationInHistoricalMetrics = historicalMetrics(0, size - 1);

			if (iterationInHistoricalMetrics != iteration) {
				throw IncompatibleIterationExcep(iterationInHistoricalMetrics, iteration);
			}

			mat historicalMetricsView = historicalMetrics.submat(1, size - 1, 5, size - 1);
			previousMetrics = colvec(historicalMetricsView);
		}
	}
	catch (IncompatibleIterationExcep& error) {
		std::cout << error.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (const std::exception& error) {
		std::cout << error.what() << endl;
		historicalMetrics = mat();
	}

}

void DataHandler::saveNewMetrics()
{
	colvec newHistoricalMetricsCol = {double(iteration)};
	newHistoricalMetricsCol.insert_rows(1, newMetrics);
	historicalMetrics.insert_cols(historicalMetrics.n_cols, newHistoricalMetricsCol);


	previousMetrics = colvec(newMetrics);

	mlpack::data::Save("data/DataMemory/HistoricalMetrics.csv", historicalMetrics, true);
}

void DataHandler::insertNewMetrics(rowvec clustersSilhouette, rowvec numberOfPointsPerCluster, double overallSilhouette) {
	rowvec newMetricsTransposed = join_rows(clustersSilhouette, numberOfPointsPerCluster);
	newMetricsTransposed.reshape(1, 5);
	newMetricsTransposed[4] = overallSilhouette;

	newMetrics = trans(newMetricsTransposed);
}

colvec DataHandler::getOldMetrics() {
	return previousMetrics;
}

void DataHandler::loadHistoricalData() {
	try {
		mlpack::data::Load("data/DataMemory/HistoricalData.csv", historicalData, true);
		int size = historicalData.n_cols;
		if (size > 0) {
			iteration = historicalData(0, size - 1);
			historicalDataToCluster = historicalData.submat(2, 0, 2, size - 1);
		}
	}
	catch (const std::runtime_error& error) {
		std::cout << error.what() << endl;
		historicalData = mat();
	}
}

void DataHandler::insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn) {
	iteration++;
	mat newHistoricalData = { {double(iteration),  double(iteration)},
								{0.0, 1.0}, 
								{fuse_result_burn, fuse_result_not_burn},
							};

	historicalData.insert_cols(historicalData.n_cols, newHistoricalData);

	historicalDataToCluster = historicalData.submat(2, 0, 2, historicalData.n_cols - 1);

}

void DataHandler::updateHistoricalData() {
	mlpack::data::Save("data/DataMemory/HistoricalData.csv", historicalData, true);
};

mat DataHandler::getHistoricalDataToCluster() {
	return historicalDataToCluster;
}