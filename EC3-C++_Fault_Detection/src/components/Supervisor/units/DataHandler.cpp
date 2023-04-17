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
	DataHandler::allowLogFiles = true; // Standard setting: always generates simulation logs.

	// Initializes all control flow attributes with 'false'
	controlFlowInitializeDataHandler = false;
	controlFlowLoadHistoricalMetrics = false;
	controlFlowUpdateHistoricalMetrics = false;
	controlFlowInsertNewMetrics = false;
	controlFlowLoadHistoricalData = false;
	controlFlowReset = false;
	controlFlowInsertNewHistoricalData = false;
	controlFlowUpdateHistoricalData = false;
	controlFlowUpdateSimulationHistoricalData = false;
	controlFlowUpdateSimulationHistoricalMetrics = false;
	controlFlowGetHistoricalDataToCluster = false;
	controlFlowGetPreviousMetrics = false;
	controlFlowGetLastIterationInDataMemory = false;
	controlFlowGetNumberOfMetrics = false;
	controlFlowSetSimulationName = false;
	controlFlowSetMaxNumberOfRegisters = false;
	controlFlowDeleteRecordsFromOldestIteration = false;
	controlFlowDeleteRecordsFromLatestIteration = false;
	controlFlowLogFilesConfig = false;
}

void DataHandler::initializeDataHandler()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowInitializeDataHandler == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> initializeDataHandler");
	}

	else
	{
		controlFlowInitializeDataHandler = true;
		
		// historical data needs to be loaded before historicalMetrics
		loadHistoricalData();
		loadHistoricalMetrics();

		if (verboseMode)
		{
			cout << "Data Handler for " << testName << " initialized" << endl;
			cout << "Number of rows in '" << testName << "/HistoricalData.csv': " << historicalData.n_cols << endl;
			cout << "Number of rows in '" << testName << "/HistoricalMetrics.csv': " << historicalMetrics.n_cols << endl;
		}

		// Releases controlFlowInitializeDataHandler after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowInitializeDataHandler == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> initializeDataHandler");
		}

		else
		{
				controlFlowInitializeDataHandler = false;
		}
	}
}

int DataHandler::loadHistoricalMetrics()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowLoadHistoricalMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> loadHistoricalMetrics");
	}

	else
	{
		controlFlowLoadHistoricalMetrics = true;

		historicalMetrics = mat();
		previousMetrics = colvec(numberOfMetrics, fill::zeros);
		newMetrics = colvec(numberOfMetrics, fill::zeros);
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

		// Releases controlFlowLoadHistoricalMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowLoadHistoricalMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> loadHistoricalMetrics");
		}

		else
		{
			controlFlowLoadHistoricalMetrics = false;
			return size;
		}
	}
}

void DataHandler::updateHistoricalMetrics()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowUpdateHistoricalMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateHistoricalMetrics");
	}

	else
	{
		controlFlowUpdateHistoricalMetrics = true;

		mlpack::data::Save(
			dataMemoryDir + "/"
			+ simulationName + "/"
			+ testName + "/HistoricalMetrics.csv",
			historicalMetrics, true);

		// Releases controlFlowUpdateHistoricalMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowUpdateHistoricalMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateHistoricalMetrics");
		}

		else
		{
			controlFlowUpdateHistoricalMetrics = false;
		}
	}
}

void DataHandler::insertNewMetrics(colvec newMetrics) {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowInsertNewMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> insertNewMetrics");
	}

	else
	{
		controlFlowInsertNewMetrics = true;

		colvec newHistoricalMetricsCol = { double(globalIteration) };
		newHistoricalMetricsCol.insert_rows(1, newMetrics);

		if (historicalMetrics.n_cols == maxNumberOfRegisters / 2) {
			historicalMetrics.shed_col(0);
		}

		historicalMetrics.insert_cols(historicalMetrics.n_cols, newHistoricalMetricsCol);

		DataHandler::previousMetrics = colvec(DataHandler::newMetrics);
		DataHandler::newMetrics = newMetrics;

		if (allowLogFiles) updateSimulationHistoricalMetrics(newMetrics);

		// Releases controlFlowInsertNewMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowInsertNewMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> insertNewMetrics");
		}

		else
		{
			controlFlowInsertNewMetrics = false;
		}
	}
}

colvec DataHandler::getPreviousMetrics()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetPreviousMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getPreviousMetrics");
	}

	else
	{
		controlFlowGetPreviousMetrics = true;

		// Releases controlFlowGetPreviousMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetPreviousMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getPreviousMetrics");
		}

		else
		{
			controlFlowGetPreviousMetrics = false;
			return previousMetrics;
		}
	}
}

int DataHandler::getLastIterationInDataMemory()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetLastIterationInDataMemory == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getLastIterationInDataMemory");
	}

	else
	{
		controlFlowGetLastIterationInDataMemory = true;

		// Releases controlFlowGetLastIterationInDataMemory after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetLastIterationInDataMemory == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getLastIterationInDataMemory");
		}

		else
		{
			controlFlowGetLastIterationInDataMemory = false;
			return lastIterationInDataMemory;
		}
	}
}

int DataHandler::getNumberOfMetrics()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetNumberOfMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getNumberOfMetrics");
	}

	else
	{
		controlFlowGetNumberOfMetrics = true;

		// Releases controlFlowGetNumberOfMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetNumberOfMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getNumberOfMetrics");
		}

		else
		{
			controlFlowGetNumberOfMetrics = false;
			return numberOfMetrics;
		}
	}
}

int DataHandler::loadHistoricalData() {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowLoadHistoricalData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> loadHistoricalData");
	}

	else
	{
		controlFlowLoadHistoricalData = true;

		int size = 0;
		try {
			historicalData = mat();
			historicalDataToCluster = mat();
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
			else {
				lastIterationInDataMemory = 0;
			}
		}
		catch (const std::exception& error) {
			throw SimulatorFailureExcep(error.what(), "Supervisor.DataHandler");
		}

		// Releases controlFlowLoadHistoricalData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowLoadHistoricalData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> loadHistoricalData");
		}

		else
		{
			controlFlowLoadHistoricalData = false;
			return size;
		}
	}
}

void DataHandler::reset()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowReset == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> reset");
	}

	else
	{
		controlFlowReset = true;

		lastIterationInDataMemory = 0;
		numberOfRegisters = 0;
		previousMetrics = colvec(numberOfMetrics, fill::zeros);
		newMetrics = colvec(numberOfMetrics, fill::zeros);
		historicalData = mat();
		historicalMetrics = mat();
		historicalDataToCluster = mat();

		if (verboseMode) cout << "Data Handler for " << testName << " was reset" << endl;

		// Releases controlFlowReset after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowReset == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> reset");
		}

		else
		{
			controlFlowReset = false;
		}
	}	
}

void DataHandler::insertNewHistoricalData(mat newData) {
	
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowInsertNewHistoricalData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> insertNewHistoricalData");
	}

	else
	{
		controlFlowInsertNewHistoricalData = true;

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

		if (allowLogFiles) updateSimulationHistoricalData(newData);

		numberOfRegisters = historicalData.n_cols;

		historicalDataToCluster = historicalData.submat(2, 0, 2, numberOfRegisters - 1);

		// Releases controlFlowInsertNewHistoricalData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowInsertNewHistoricalData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> insertNewHistoricalData");
		}

		else
		{
			controlFlowInsertNewHistoricalData = false;
		}
	}
}

void DataHandler::updateHistoricalData()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowUpdateHistoricalData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateHistoricalData");
	}

	else
	{
		controlFlowUpdateHistoricalData = true;

		mlpack::data::Save(
			dataMemoryDir + "/"
			+ simulationName + "/"
			+ testName + "/HistoricalData.csv",
			historicalData, true);

		// Releases controlFlowUpdateHistoricalData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowUpdateHistoricalData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateHistoricalData");
		}

		else
		{
			controlFlowUpdateHistoricalData = false;
		}
	}	
};

mat DataHandler::getHistoricalDataToCluster()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetHistoricalDataToCluster == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getHistoricalDataToCluster");
	}

	else
	{
		controlFlowGetHistoricalDataToCluster = true;

		mlpack::data::Save(
			dataMemoryDir + "/"
			+ simulationName + "/"
			+ testName + "/HistoricalData.csv",
			historicalData, true);

		// Releases controlFlowUpdateHistoricalData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetHistoricalDataToCluster == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> getHistoricalDataToCluster");
		}

		else
		{
			controlFlowGetHistoricalDataToCluster = false;
			return historicalDataToCluster;
		}
	}	
}

void DataHandler::updateSimulationHistoricalData(mat newData)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowUpdateSimulationHistoricalData == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateSimulationHistoricalData");
	}

	else
	{
		controlFlowUpdateSimulationHistoricalData = true;

		std::ofstream simulationDataFile;

		int numberOfColumns = newData.n_cols;
		int numberOfRows = newData.n_rows;
		double element;

		simulationDataFile.open(
			simulationsDir + "/" +
			simulationName + "/" +
			testName +
			"/HistoricalDataFullLog.csv",
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

		// Releases controlFlowUpdateSimulationHistoricalData after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowUpdateSimulationHistoricalData == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateSimulationHistoricalData");
		}

		else
		{
			controlFlowUpdateSimulationHistoricalData = false;
		}
	}	
}

void DataHandler::updateSimulationHistoricalMetrics(colvec newMetrics)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowUpdateSimulationHistoricalMetrics == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateSimulationHistoricalMetrics");
	}

	else
	{
		controlFlowUpdateSimulationHistoricalMetrics = true;

		std::ofstream simulationDataFile;

		int numberOfRows = newMetrics.n_rows;
		double element;

		simulationDataFile.open(
			simulationsDir + "/"
			+ simulationName + "/"
			+ testName
			+ "/HistoricalMetricsFullLog.csv",
			std::ios_base::app);

		simulationDataFile << globalIteration << ',';

		for (int i = 0; i < numberOfRows - 1; i++) {
			element = newMetrics(i);
			simulationDataFile << element << ',';
		}
		element = newMetrics(numberOfRows - 1);
		simulationDataFile << element << endl;

		simulationDataFile.close();

		// Releases controlFlowUpdateSimulationHistoricalMetrics after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowUpdateSimulationHistoricalMetrics == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> updateSimulationHistoricalMetrics");
		}

		else
		{
			controlFlowUpdateSimulationHistoricalMetrics = false;
		}
	}	
}

void DataHandler::setSimulationName(std::string simulationName)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetSimulationName == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> setSimulationName");
	}

	else
	{
		controlFlowSetSimulationName = true;

		DataHandler::simulationName = simulationName;

		// Releases controlFlowSetSimulationName after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetSimulationName == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> setSimulationName");
		}

		else
		{
			controlFlowSetSimulationName = false;
		}
	}	
}

void DataHandler::setMaxNumberOfRegisters(unsigned int maxNumberOfRegisters)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetMaxNumberOfRegisters == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> setMaxNumberOfRegisters");
	}

	else
	{
		controlFlowSetMaxNumberOfRegisters = true;

		DataHandler::maxNumberOfRegisters = maxNumberOfRegisters;

		// Releases controlFlowSetMaxNumberOfRegisters after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetMaxNumberOfRegisters == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> setMaxNumberOfRegisters");
		}

		else
		{
			controlFlowSetMaxNumberOfRegisters = false;
		}
	}	
}

void DataHandler::deleteRecordsFromOldestIteration()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowDeleteRecordsFromOldestIteration == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> deleteRecordsFromOldestIteration");
	}

	else
	{
		controlFlowDeleteRecordsFromOldestIteration = true;

		// PS: remember that all data stored in armadillo's mat is in a column-major format

		// it eliminates the first two input-output records stored in historicalData
		// PS: remember that each iteration (test) always produces two records in historicalData,
		// since tests are executed for all possible input values (0 and 1)
		// for 'Fuse Test' and 'Keep Power Test') Therefore, data from the first iteration are being
		// removed from memory here
		historicalData.shed_cols(0, 1);

		// it eliminates the first (oldest) record of metrics stored in historicalMetrics
		// PS: remember that each iteration (test)  always produces a single record 
		// in historicalMetrics
		historicalMetrics.shed_col(0);

		numberOfRegisters = historicalData.n_cols;
		historicalDataToCluster = historicalData.submat(2, 0, 2, numberOfRegisters - 1);

		// Releases controlFlowDeleteRecordsFromOldestIteration after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowDeleteRecordsFromOldestIteration == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> deleteRecordsFromOldestIteration");
		}

		else
		{
			controlFlowDeleteRecordsFromOldestIteration = false;
		}
	}	
}

void DataHandler::deleteRecordsFromLatestIteration()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowDeleteRecordsFromLatestIteration == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> deleteRecordsFromLatestIteration");
	}

	else
	{
		controlFlowDeleteRecordsFromLatestIteration = true;

		// it eliminates the last (most recent) two input-output records stored in historicalData
		// PS: remember that each iteration (test) always produces two records in historicalData,
		// since tests are executed for all possible input values (0 and 1
		// for 'Fuse Test' and 'Keep Power Test'). Therefore, data from last iteration are being
		// removed from memory here
		historicalData.shed_cols(historicalData.n_cols - 2, historicalData.n_cols - 1);

		// it eliminates the last metric stored in historicalMetrics
		// PS: remember that data is stored in a column-major format
		historicalMetrics.shed_col(historicalMetrics.n_cols - 1);

		int lastMetricIndex = historicalMetrics.n_cols - 1;

		DataHandler::newMetrics = historicalMetrics.submat(1, lastMetricIndex, numberOfMetrics, lastMetricIndex);
		DataHandler::previousMetrics = historicalMetrics.submat(1, lastMetricIndex - 1, numberOfMetrics, lastMetricIndex - 1);

		numberOfRegisters = historicalData.n_cols;
		historicalDataToCluster = historicalData.submat(2, 0, 2, numberOfRegisters - 1);

		// Releases controlFlowDeleteRecordsFromLatestIteration after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowDeleteRecordsFromLatestIteration == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> deleteRecordsFromLatestIteration");
		}

		else
		{
			controlFlowDeleteRecordsFromLatestIteration = false;
		}
	}
}

void DataHandler::logFilesConfig(bool enable)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowLogFilesConfig == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> logFilesConfig");
	}

	else
	{
		controlFlowLogFilesConfig = true;

		allowLogFiles = enable;

		// Releases controlFlowLogFilesConfig after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowLogFilesConfig == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> DataHandler ==> logFilesConfig");
		}

		else
		{
			controlFlowLogFilesConfig = false;
		}
	}	
}
