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
		int& iteration,
		unsigned int maxNumberOfRegisters,
		int numberOfMetrics,
		std::string testName,
		bool& verboseMode,
		std::string dataMemoryDir = "data/DataMemory",
		std::string simulationMemoryDir = "data/SimulationMemory"
	);

	void initializeDataHandler();

	void loadHistoricalMetrics();

	void updateHistoricalMetrics();

	void insertNewMetrics(colvec newMetrics);

	void loadHistoricalData();

	void reset();

	void insertNewHistoricalData(mat newData);

	void updateHistoricalData();

	void updateSimulationHistoricalData(mat newHistoricalData);

	void updateSimulationHistoricalMetrics(colvec newMetrics);

	mat getHistoricalDataToCluster();

	colvec getPreviousMetrics();

	int getLastIterationInDataMemory();
	int getNumberOfMetrics();

	void setSimulationName(std::string simulationName);
	void setMaxNumberOfRegisters(unsigned int maxNumberOfRegisters);

	void deleteRecordsFromOldestIteration();
	void deleteRecordsFromLatestIteration();
	void logFilesConfig(bool enable);


private:
	int& globalIteration;
	int lastIterationInDataMemory, numberOfRegisters;
	unsigned int maxNumberOfRegisters;
	const int numberOfMetrics;
	bool& verboseMode;
	bool allowLogFiles;

	// the following variables are fixed for all simulations.
	// they correspond to parameters set at the moment of the instantiation
	// of the objects dataHandlerFuseTest and dataHandlerKeepPowTest
	const std::string dataMemoryDir;
	const std::string simulationsDir;
	const std::string testName;

	mat historicalMetrics;
	mat historicalData;
	mat historicalDataToCluster;
	colvec previousMetrics;
	colvec newMetrics;

	std::string simulationName;

	// Control flow attributes - one attribute per method (except for the constructor)
	// False indicates that the method is not currently running; true indicates that a prior call is running
	bool controlFlowInitializeDataHandler;
	bool controlFlowLoadHistoricalMetrics;
	bool controlFlowUpdateHistoricalMetrics;
	bool controlFlowInsertNewMetrics;
	bool controlFlowLoadHistoricalData;
	bool controlFlowReset;
	bool controlFlowInsertNewHistoricalData;
	bool controlFlowUpdateHistoricalData;
	bool controlFlowUpdateSimulationHistoricalData;
	bool controlFlowUpdateSimulationHistoricalMetrics;
	bool controlFlowGetHistoricalDataToCluster;
	bool controlFlowGetPreviousMetrics;
	bool controlFlowGetLastIterationInDataMemory;
	bool controlFlowGetNumberOfMetrics;
	bool controlFlowSetSimulationName;
	bool controlFlowSetMaxNumberOfRegisters;
	bool controlFlowDeleteRecordsFromOldestIteration;
	bool controlFlowDeleteRecordsFromLatestIteration;
	bool controlFlowLogFilesConfig;

};