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

	void updateDataMemory();

	void clearControlFlowSupervisor();

private:
	mat nominalFuseResults;
	mat nominalKeepPowReadbacks;
	int globalIteration;

	AnalysisUnit analysisUnit;
	DataHandler dataHandlerFuseTest;
	DataHandler dataHandlerKeepPowTest;
	ProcessUnitSR processUnit;

	// Control flow attributes - one attribute per method (except for the constructor)
	// False indicates that the method is not currently running; true indicates that a prior call is running
	bool controlFlowAttach;
	bool controlFlowRunTest;
	bool controlFlowReset;
	bool controlFlowGetIterationPointer;
	bool controlFlowGetReadyForNextSimulationCycle;
	bool controlFlowPrepareForSimulation;
	bool controlFlowSetBasicParams;
	bool controlFlowGetFuseTestResults;
	bool controlFlowGetKeepPowerTestResults;
	bool controlFlowDeleteRecordsFromLatestIteration;
	bool controlFlowLogFilesConfig;
	bool controlFlowGetLastPerfomedTest;
	bool controlFlowUpdateDataMemory;
	bool controlFlowClearControlFlowSupervisor;

};