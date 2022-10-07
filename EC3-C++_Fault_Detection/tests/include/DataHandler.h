#include <mlpack/core.hpp>

using namespace arma;
class DataHandler {
	public:

		DataHandler();

		void loadOldMetrics();

		void saveNewMetrics();

		void insertNewMetrics(rowvec clustersSilhouette, rowvec numberOfPointsPerCluster, double OverallSilhouette);

		void loadHistoricalData();

		void insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn);

		void updateHistoricalData();

		mat getHistoricalDataToCluster();

		colvec getOldMetrics();

	private:
		int iteration = 0;
		int number_of_registers = 0;

		mat historicalMetrics;
		mat historicalData;
		mat historicalDataToCluster;
		colvec previousMetrics;
		colvec newMetrics;

};