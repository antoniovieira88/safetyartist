#include "ProcessUnitSR.h"

using namespace std;

class Supervisor {
public:
	Supervisor(
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		int maxNumberOfRegisters = 1000,
		double nominalFuseResultBurn = 54, double nominalFuseResultNotBurn = 4092,
		bool verboseMode = true);

	void attach(Supervised* supervised);
	void runTest();
	void reset();
	int* getIterationPointer();
	void getReadyForNextSimulationCycle();
	void prepareForSimulation();
	void setVerboseMode(bool verboseModeValue);
	void setBasicParams(
		double nominalValueFuseResultBurn,
		double nominalValueFuseResultNotBurn,
		double overallSilhouetteToleranceValue,
		double silhouetteDiffToleranceValue,
		double numberOfPointsPerClusterDiffToleranceValue,
		int maxNumberOfRegisters,
		string simulationName);

	FuseTestResultsType getFuseTestResults();
	KeepPowerTestResultsType getKeepPowerTestResults();

	void deleteRecordsFromLatestIteration();
	void logFilesConfig(bool enable);
	test getLastPerfomedTest();

private:
	mat nominalFuseResults;
	mat nominalKeepPowReadbacks;
	int globalIteration;

	AnalysisUnit analysisUnit;
	DataHandler dataHandlerFuseTest;
	DataHandler dataHandlerKeepPowTest;
	ProcessUnitSR processUnit;
};