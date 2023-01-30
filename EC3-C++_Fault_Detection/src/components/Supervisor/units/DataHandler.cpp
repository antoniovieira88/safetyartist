#include "../include/DataHandler.h"

using namespace arma;

DataHandler::DataHandler(
	int& iteration,
	unsigned int maxNumberOfRegisters,
	int numberOfMetrics,
	std::string testName,
	bool& verboseMode,
	std::string dataMemoryDir,
	std::string simulationMemoryDir
) :
	globalIteration(iteration), verboseMode(verboseMode),
	dataMemoryDir(dataMemoryDir), simulationsDir(simulationMemoryDir + "/Simulations"),
	testName(testName), historicalData(), historicalMetrics(), numberOfMetrics(numberOfMetrics),
	historicalDataToCluster(), previousMetrics(numberOfMetrics, fill::zeros),
	newMetrics(colvec(numberOfMetrics, fill::zeros))
{
	DataHandler::lastIterationInDataMemory = 0;
	DataHandler::numberOfRegisters = 0;
	DataHandler::maxNumberOfRegisters = maxNumberOfRegisters;
	DataHandler::simulationName = "";
}

void DataHandler::initializeDataHandler()
{
	// historical data needs to be loaded before historicalMetrics
	loadHistoricalData();
	loadHistoricalMetrics();

	if (verboseMode) {
		cout << "Data Handler for " << testName << " initialized" << endl;
		cout << "Number of rows in '" << testName << "/HistoricalData.csv': " << historicalData.n_cols << endl;
		cout << "Number of rows in '" << testName << "/HistoricalMetrics.csv': " << historicalMetrics.n_cols << endl;
	}

}

int DataHandler::loadHistoricalMetrics()
{
	int size = 0;
	try {
		mlpack::data::Load(
			dataMemoryDir + "/" + simulationName + "/"
			+ testName + "/HistoricalMetrics.csv",
			historicalMetrics
		);
		size = historicalMetrics.n_cols;

		if (size > maxNumberOfRegisters / 2) {
			throw RegistersOverflowExcep(size, maxNumberOfRegisters / 2);
		}

		if (size > 0) {
			int iterationInHistoricalMetrics = historicalMetrics(0, size - 1);

			if (iterationInHistoricalMetrics != lastIterationInDataMemory) {
				throw IncompatibleIterationExcep(iterationInHistoricalMetrics, lastIterationInDataMemory);
			}

			mat historicalMetricsView = historicalMetrics.submat(1, size - 1, numberOfMetrics, size - 1);
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
		+ simulationName + "/"
		+ testName + "/HistoricalMetrics.csv",
		historicalMetrics, true);
}

void DataHandler::insertNewMetrics(colvec newMetrics) {
	DataHandler::previousMetrics = colvec(DataHandler::newMetrics);
	DataHandler::newMetrics = newMetrics;

	colvec newHistoricalMetricsCol = { double(globalIteration) };
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

int DataHandler::getLastIterationInDataMemory()
{
	return lastIterationInDataMemory;
}

int DataHandler::getNumberOfMetrics()
{
	return numberOfMetrics;
}

int DataHandler::loadHistoricalData() {
	int size = 0;
	try {
		mlpack::data::Load(
			dataMemoryDir + "/" + simulationName + "/"
			+ testName + "/HistoricalData.csv",
			historicalData
		);
		size = historicalData.n_cols;

		if (size > maxNumberOfRegisters) {
			throw RegistersOverflowExcep(size, maxNumberOfRegisters);
		}

		numberOfRegisters = size;

		if (numberOfRegisters > 0) {
			// here the iteration is updated for the entire application
			lastIterationInDataMemory = historicalData(0, numberOfRegisters - 1);
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
	lastIterationInDataMemory = 0;
	numberOfRegisters = 0;
	previousMetrics = colvec(numberOfMetrics, fill::zeros);
	newMetrics = colvec(numberOfMetrics, fill::zeros);
	historicalData = mat();
	historicalMetrics = mat();
	historicalDataToCluster = mat();

	if (verboseMode) cout << "Data Handler for " << testName << " was reset" << endl;
}

void DataHandler::insertNewHistoricalData(mat newData) {
	if (numberOfRegisters == maxNumberOfRegisters) {
		historicalData.shed_cols(0, 1);
	}

	lastIterationInDataMemory = globalIteration;

	// iteration variable is updated in ProcessUnitSR's scope
	newData.insert_rows(0, rowvec({ double(globalIteration),  double(globalIteration) }));

	/*
		after the last operation, mat newData will have a format like:
		| iteration  iteration |
		| input1     input2    |
		| output1    output2   |

		-> it is important to remember that the 'mlpack' and 'armadillo'
		libraries used in this project are column-major
	*/

	historicalData.insert_cols(historicalData.n_cols, newData);

	updateSimulationHistoricalData(newData);

	numberOfRegisters = historicalData.n_cols;

	historicalDataToCluster = historicalData.submat(2, 0, 2, historicalData.n_cols - 1);

}

void DataHandler::updateHistoricalData() {
	mlpack::data::Save(
		dataMemoryDir + "/"
		+ simulationName + "/"
		+ testName + "/HistoricalData.csv",
		historicalData, true);
};

mat DataHandler::getHistoricalDataToCluster() {
	return historicalDataToCluster;
}

void DataHandler::updateSimulationHistoricalData(mat newData) {
	std::ofstream simulationDataFile;

	int numberOfColumns = newData.n_cols;
	int numberOfRows = newData.n_rows;
	double element;

	simulationDataFile.open(
		simulationsDir + "/" +
		simulationName + "/HistoricalDataFullLog.csv",
		std::ios_base::app);

	for (int j = 0; j < numberOfColumns; j++) {
		for (int i = 0; i < numberOfRows - 1; i++) {
			element = newData(i, j);
			simulationDataFile << element << ',';
		}
		element = newData(numberOfRows - 1, j);
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
	simulationDataFile << globalIteration << ',';
	for (int i = 0; i < numberOfRows - 1; i++) {
		element = newMetrics(i);
		simulationDataFile << element << ',';
	}
	element = newMetrics(numberOfRows - 1);
	simulationDataFile << element << endl;

	simulationDataFile.close();
}

void DataHandler::setSimulationName(std::string simulationName)
{
	DataHandler::simulationName = simulationName;
}

void DataHandler::setMaxNumberOfRegisters(unsigned int maxNumberOfRegisters)
{
	DataHandler::maxNumberOfRegisters = maxNumberOfRegisters;
}