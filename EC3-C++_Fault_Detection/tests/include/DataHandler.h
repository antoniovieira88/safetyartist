#include <mlpack/core.hpp>

using namespace arma;
class DataHandler {
	public:

		DataHandler(int maxNumberOfRegisters);

		void loadOldMetrics();

		void saveNewMetrics();

		void insertNewMetrics(colvec newMetrics);

		void loadHistoricalData();

		void insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn);

		void updateHistoricalData();

		void updateSimulationHistoricalData(mat newHistoricalData);

		void updateSimulationHistoricalMetrics(colvec newMetrics);

		mat getHistoricalDataToCluster();

		colvec getOldMetrics();

		int getIteration();

	private:
		int iteration;
		int numberOfRegisters;
		int maxNumberOfRegisters;

		mat historicalMetrics;
		mat historicalData;
		mat historicalDataToCluster;
		colvec previousMetrics;
		colvec newMetrics;

};