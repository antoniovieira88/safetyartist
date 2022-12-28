#include <mlpack/core.hpp>

using namespace arma;
class DataHandler {
public:

	DataHandler(int maxNumberOfRegisters);

	int loadOldMetrics();

	void saveNewMetrics();

	void insertNewMetrics(colvec newMetrics);

	int loadHistoricalData();

	void reset();

	void insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn);

	void updateHistoricalData();

	void updateSimulationHistoricalData(mat newHistoricalData);

	void updateSimulationHistoricalMetrics(colvec newMetrics);

	mat getHistoricalDataToCluster();

	colvec getOldMetrics();

	int* getIterationPointer();


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