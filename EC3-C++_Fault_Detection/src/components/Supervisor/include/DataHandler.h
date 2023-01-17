#include <mlpack/core.hpp>
#include <string>
#include <fstream>
#include "../../../utils/exceptions/include/IncompatibleIterationExcep.h"
#include "../../../utils/exceptions/include/RegistersOverflowExcep.h"
#include "../../../utils/exceptions/include/SimulatorFailureExcep.h"

using namespace arma;
class DataHandler {
public:

	DataHandler(
		int maxNumberOfRegisters,
		std::string dataMemoryDir = "data/DataMemory",
		std::string simulationMemoryDir = "data/SimulationMemory");

	int loadHistoricalMetrics();

	void updateHistoricalMetrics();

	void insertNewMetrics(colvec newMetrics);

	int loadHistoricalData();

	void reset();

	void insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn);

	void updateHistoricalData();

	void updateSimulationHistoricalData(mat newHistoricalData);

	void updateSimulationHistoricalMetrics(colvec newMetrics);

	mat getHistoricalDataToCluster();

	colvec getPreviousMetrics();

	int* getIterationPointer();

	void setSimulationName(std::string simulationName);


private:
	int iteration;
	int numberOfRegisters;
	int maxNumberOfRegisters;

	const std::string dataMemoryDir;
	const std::string simulationsDir;

	mat historicalMetrics;
	mat historicalData;
	mat historicalDataToCluster;
	colvec previousMetrics;
	colvec newMetrics;

	std::string simulationName;

};