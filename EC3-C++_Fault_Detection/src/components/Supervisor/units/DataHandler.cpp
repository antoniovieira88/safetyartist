#include "../include/DataHandler.h"

using namespace arma;

DataHandler::DataHandler(
	int maxNumberOfRegisters,
	std::string dataMemoryDir,
	std::string simulationMemoryDir) :
	dataMemoryDir(dataMemoryDir), simulationsDir(simulationMemoryDir + "/Simulations"),
	historicalData(), historicalMetrics(),
	historicalDataToCluster(), previousMetrics(5, fill::zeros),
	newMetrics(colvec(5, fill::zeros))
{
	DataHandler::iteration = 0;
	DataHandler::numberOfRegisters = 0;
	DataHandler::maxNumberOfRegisters = maxNumberOfRegisters;
	DataHandler::simulationName = "";
}

int DataHandler::loadHistoricalMetrics()
{
	int size = 0;
	try {
		mlpack::data::Load(
			dataMemoryDir + "/" + simulationName + "/HistoricalMetrics.csv",
			historicalMetrics,
			false,
			true,
			file_type::csv_ascii);
		size = historicalMetrics.n_cols;

		if (size > maxNumberOfRegisters / 2) {
			throw RegistersOverflowExcep(size, maxNumberOfRegisters / 2);
		}

		if (size > 0) {
			int iterationInHistoricalMetrics = historicalMetrics(0, size - 1);

			if (iterationInHistoricalMetrics != iteration) {
				throw IncompatibleIterationExcep(iterationInHistoricalMetrics, iteration);
			}

			mat historicalMetricsView = historicalMetrics.submat(1, size - 1, 5, size - 1);
			previousMetrics = colvec(historicalMetricsView);
			newMetrics = previousMetrics;
		}
	}
	catch (const std::exception& error) {
		throw SimulatorFailureExcep(error.what(), "Supervisor.DataHandler");
	}

	return size;
}

void DataHandler::updateHistoricalMetrics()
{
	mlpack::data::Save(
		dataMemoryDir + "/"
		+ simulationName + "/HistoricalMetrics.csv",
		historicalMetrics, true);
}

void DataHandler::insertNewMetrics(colvec newMetrics) {
	DataHandler::previousMetrics = colvec(DataHandler::newMetrics);
	DataHandler::newMetrics = newMetrics;

	colvec newHistoricalMetricsCol = { double(iteration) };
	newHistoricalMetricsCol.insert_rows(1, newMetrics);
	if (historicalMetrics.n_cols == maxNumberOfRegisters / 2) {
		historicalMetrics.shed_col(0);
	}
	historicalMetrics.insert_cols(historicalMetrics.n_cols, newHistoricalMetricsCol);

	updateSimulationHistoricalMetrics(newMetrics);
}

colvec DataHandler::getPreviousMetrics() {
	return previousMetrics;
}

int DataHandler::loadHistoricalData() {
	int size = 0;
	try {
		mlpack::data::Load(
			dataMemoryDir + "/" + simulationName + "/HistoricalData.csv",
			historicalData,
			false,
			true,
			file_type::csv_ascii
		);
		size = historicalData.n_cols;

		if (size > maxNumberOfRegisters) {
			throw RegistersOverflowExcep(size, maxNumberOfRegisters);
		}

		numberOfRegisters = size;

		if (numberOfRegisters > 0) {
			// here the iteration is updated for the entire application
			iteration = historicalData(0, numberOfRegisters - 1);
			historicalDataToCluster = historicalData.submat(2, 0, 2, numberOfRegisters - 1);
		}
	}
	catch (const std::exception& error) {
		throw SimulatorFailureExcep(error.what(), "Supervisor.DataHandler");
	}

	return size;
}

void DataHandler::reset()
{
	iteration = 0;
	numberOfRegisters = 0;
	previousMetrics = colvec(5, fill::zeros);
	newMetrics = colvec(5, fill::zeros);
	historicalData = mat();
	historicalMetrics = mat();
}

void DataHandler::insertNewHistoricalData(double fuse_result_burn, double fuse_result_not_burn) {
	// here the iteration is updated for the entire application
	iteration++;

	if (numberOfRegisters == maxNumberOfRegisters) {
		historicalData.shed_cols(0, 1);
	}

	mat newHistoricalData = { {double(iteration),  double(iteration)},
								{0.0, 1.0},
								{fuse_result_burn, fuse_result_not_burn},
	};

	historicalData.insert_cols(historicalData.n_cols, newHistoricalData);

	updateSimulationHistoricalData(newHistoricalData);

	numberOfRegisters = historicalData.n_cols;

	historicalDataToCluster = historicalData.submat(2, 0, 2, historicalData.n_cols - 1);

}

void DataHandler::updateHistoricalData() {
	mlpack::data::Save(
		dataMemoryDir + "/"
		+ simulationName + "/HistoricalData.csv",
		historicalData, true);
};

mat DataHandler::getHistoricalDataToCluster() {
	return historicalDataToCluster;
}

void DataHandler::updateSimulationHistoricalData(mat newHistoricalData) {
	std::ofstream simulationDataFile;

	int numberOfColumns = newHistoricalData.n_cols;
	int numberOfRows = newHistoricalData.n_rows;
	double element;

	simulationDataFile.open(
		simulationsDir + "/" +
		simulationName + "/HistoricalDataFullLog.csv",
		std::ios_base::app);

	for (int j = 0; j < numberOfColumns; j++) {
		for (int i = 0; i < numberOfRows - 1; i++) {
			element = newHistoricalData(i, j);
			simulationDataFile << element << ',';
		}
		element = newHistoricalData(numberOfRows - 1, j);
		simulationDataFile << element << endl;
	}

	simulationDataFile.close();
}

void DataHandler::updateSimulationHistoricalMetrics(colvec newMetrics) {
	std::ofstream simulationDataFile;

	int numberOfRows = newMetrics.n_rows;
	double element;

	simulationDataFile.open(
		simulationsDir + "/"
		+ simulationName + "/HistoricalMetricsFullLog.csv",
		std::ios_base::app);
	simulationDataFile << iteration << ',';
	for (int i = 0; i < numberOfRows - 1; i++) {
		element = newMetrics(i);
		simulationDataFile << element << ',';
	}
	element = newMetrics(numberOfRows - 1);
	simulationDataFile << element << endl;

	simulationDataFile.close();
}

int* DataHandler::getIterationPointer() {
	return &iteration;
}

void DataHandler::setSimulationName(std::string simulationName)
{
	DataHandler::simulationName = simulationName;
}
