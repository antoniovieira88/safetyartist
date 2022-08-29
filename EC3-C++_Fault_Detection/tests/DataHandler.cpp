#include "include/DataHandler.h"
#include <mlpack/core.hpp>

using namespace arma;

DataHandler::DataHandler()
{
	previousMetrics = colvec(5, fill::zeros);
	newMetrics= colvec(5, fill::zeros);

}

void DataHandler::loadOldMetrics()
{
	mlpack::data::Load("data/DataMemory/HistoricalMetrics.csv", historicalMetrics, true);
	iteration = historicalMetrics.n_cols;

	if (iteration > 0) {
		mat historicalMetricsView = historicalMetrics.submat(1, iteration - 1,5, iteration - 1);
		previousMetrics = colvec(historicalMetricsView);
	}

}

void DataHandler::saveNewMetrics()
{
	iteration = iteration + 1;
	colvec newHistoricalMetricsCol = {double(iteration)};
	newHistoricalMetricsCol.insert_rows(1, newMetrics);
	historicalMetrics.insert_cols(historicalMetrics.n_cols, newHistoricalMetricsCol);
	mlpack::data::Save("data/DataMemory/HistoricalMetrics.csv", historicalMetrics, true);
}

void DataHandler::setNewMetrics(rowvec clustersSilhouette, rowvec numberOfPointsPerCluster, double overallSilhouette) {
	rowvec newMetricsTransposed = join_rows(clustersSilhouette, numberOfPointsPerCluster);
	newMetricsTransposed.reshape(1, 5);
	newMetricsTransposed[4] = overallSilhouette;

	newMetrics = trans(newMetricsTransposed);
}
