#include "../../../include/SimulationFileHandler.h"

SimulationFileHandler::SimulationFileHandler(string dataMemoryDir, string simulationMemoryDir)
{
	SimulationFileHandler::dataMemoryDir = dataMemoryDir;
	SimulationFileHandler::simulationMemoryDir = simulationMemoryDir;
	SimulationFileHandler::simulationsDir = simulationMemoryDir + "/Simulations";
}

void SimulationFileHandler::exportJsonFaultModeAnalysisArray(vector<FaultModeAnalysisResultType>& faultModeDataArray, string destinyFilePath)
{
	json faultModeDataJson = json(faultModeDataArray);

	ofstream simulationJsonDataFile(
		destinyFilePath,
		std::ios_base::out);

	simulationJsonDataFile << faultModeDataJson.dump(4, ' ');

	simulationJsonDataFile.close();

};

void SimulationFileHandler::exportFailureEventsHistoryJson(vector<FailureEventType>& failureEventsArray, int iteration, string simulationName)
{
	json failureEventsHistoryJson = json(failureEventsArray);
	const string destinyFilePath = simulationsDir + "/" + simulationName +
		"/FailureEventsHistory" + to_string(iteration) + ".json";

	ofstream simulationJsonDataFile(
		destinyFilePath,
		std::ios_base::out);

	simulationJsonDataFile << failureEventsHistoryJson.dump(4, ' ');

	simulationJsonDataFile.close();
}

bool SimulationFileHandler::searchForSimulationDirectories(string simulationName)
{
	string dirSM = simulationsDir + "/" + simulationName;
	string dirSD = dataMemoryDir + "/" + simulationName;
	bool dirsFound = filesystem::exists(dirSM) && filesystem::exists(dirSD);

	return dirsFound;
}

void SimulationFileHandler::createLogAndStatusCSVFiles(string simulationName)
{
	string const dirSM = simulationsDir + "/" + simulationName;
	string const dirSpecs = simulationMemoryDir + "/FailureSpecs_EC3";

	FileSysHandler::createCSVFile(
		"HistoricalCaughtFailureMetricsLog",
		dirSM,
		{ "iteration", "testName", "metric", "tolerance", "variation" });

	FileSysHandler::createCSVFile(
		"AllHistoricalFailureLog",
		dirSM,
		{ "iteration", "failureOccurred", "failureCaught", "numberOfFailedComponents", "failedComponentsList",
		"unsafeFailureGenerated", "outsideScopeFailureGenerated",
		"detectableFailureGenerated", "impactlessFailureGenerated" });


	FileSysHandler::createCSVFile(
		"HistoricalDataFullLog",
		dirSM + "/FuseTest",
		{ "iteration", "fuseTest", "fuseResult" });
	FileSysHandler::createCSVFile(
		"HistoricalDataFullLog",
		dirSM + "/KeepPowerTest",
		{ "iteration", "keepPower", "keepPowerReadback" });


	FileSysHandler::createCSVFile(
		"HistoricalMetricsFullLog",
		dirSM + "/FuseTest",
		{ "iteration", "silhouetteCluster1", "silhouetteCluster2", "numPointsCluster1", "numPointsCluster2", "overallSilhouette" });
	FileSysHandler::createCSVFile(
		"HistoricalMetricsFullLog",
		dirSM + "/KeepPowerTest",
		{ "iteration", "numPointsCluster1", "numPointsCluster2" });

	FileSysHandler::copyFileOverwrite("ComponentsInitialState.csv", "ComponentsOperationalState.csv", dirSpecs, dirSM);
}

void SimulationFileHandler::createDataMemoryCSVFiles(string simulationName)
{
	const string fuseTestDir = dataMemoryDir + "/" + simulationName + "/FuseTest";

	FileSysHandler::createCSVFile("HistoricalMetrics", fuseTestDir);
	FileSysHandler::createCSVFile("HistoricalData", fuseTestDir);

	const string keepPowerTestDir = dataMemoryDir + "/" + simulationName + "/KeepPowerTest";

	FileSysHandler::createCSVFile("HistoricalMetrics", keepPowerTestDir);
	FileSysHandler::createCSVFile("HistoricalData", keepPowerTestDir);
}

void SimulationFileHandler::createSimulationFiles(string simulationName)
{

	const string relativeDirFuseTest = simulationName + "/FuseTest";
	const string relativeDirKeepPowerTest = simulationName + "/KeepPowerTest";

	bool success = FileSysHandler::createDirectories(simulationsDir, { relativeDirFuseTest, relativeDirKeepPowerTest });

	if (success) {
		if (verboseMode) {
			cout << endl << "New simulation output directories successfully created" << endl;
		}

		createLogAndStatusCSVFiles(simulationName);
	}

	success = FileSysHandler::createDirectories(dataMemoryDir, { relativeDirFuseTest, relativeDirKeepPowerTest });


	if (success) {
		if (verboseMode) {
			cout << "New data memory output directories successfully created" << endl;
		}

		createDataMemoryCSVFiles(simulationName);
	}
}

string SimulationFileHandler::createLogFileForComponentAvaliation(string componentName, string faultModesAvaliationsDir)
{
	string filename = componentName + "_AnalysisResult";
	return FileSysHandler::createJsonFile(filename, faultModesAvaliationsDir);
}

string SimulationFileHandler::createFaultModesAvaliationDir(string simulationName)
{
	const string faultModesAvaliationsBaseDir = simulationsDir + "/" + simulationName;
	FileSysHandler::createDirectories(faultModesAvaliationsBaseDir, { "FaultModesAnalysis" });
	return faultModesAvaliationsBaseDir + "/FaultModesAnalysis";
}

void SimulationFileHandler::resetCSVFiles(string simulationName)
{
	createLogAndStatusCSVFiles(simulationName);
	createDataMemoryCSVFiles(simulationName);
}

void SimulationFileHandler::defineSimulationParamsFile(SimulationSpecificParamsType simulationParams, string simulationName)
{
	ofstream simulationParamsFile;

	simulationParamsFile.open(simulationsDir + "/" + simulationName + "/SimulationParams.csv", std::ios::app);

	// header of the file
	simulationParamsFile << "parameter,value" << endl;

	// Supervisor (doubles)
	simulationParamsFile << "overallSilhouetteTolerance," << simulationParams.overallSilhouetteTolerance << endl;
	simulationParamsFile << "silhouetteDiffTolerance," << simulationParams.silhouetteDiffTolerance << endl;
	simulationParamsFile << "numberOfPointsPerClusterDiffTolerance," << simulationParams.numberOfPointsPerClusterDiffTolerance << endl;
	// Supervised (doubles)
	simulationParamsFile << "nominalFuseResultBurn," << simulationParams.nominalFuseResultBurn << endl;
	simulationParamsFile << "nominalFuseResultNotBurn," << simulationParams.nominalFuseResultNotBurn << endl;
	simulationParamsFile << "minNominalFuseResultBurn," << simulationParams.minNominalFuseResultBurn << endl;
	simulationParamsFile << "maxNominalFuseResultBurn," << simulationParams.maxNominalFuseResultBurn << endl;
	simulationParamsFile << "minNominalFuseResultNotBurn," << simulationParams.minNominalFuseResultNotBurn << endl;
	simulationParamsFile << "maxNominalFuseResultNotBurn," << simulationParams.maxNominalFuseResultNotBurn << endl;
	simulationParamsFile << "maxStdDeviation," << simulationParams.maxStdDeviation << endl;
	// Simulation Controller (doubles)
	simulationParamsFile << "iterationEquivalentTime," << simulationParams.iterationEquivalentTime << endl;
	// integers
	simulationParamsFile << "simulationSeed," << simulationParams.simulationSeed << endl;
	simulationParamsFile << "supervisorMaxNumberOfRegisters," << simulationParams.maxNumberOfRegisters;

	simulationParamsFile.close();
}
