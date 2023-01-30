#include "ProcessUnitSR.h"

using namespace std;

class Supervisor {
public:
	Supervisor(
		int maxNumberOfRegisters = 1000,
		double nominalFuseResultBurn = 0.1, double nominalFuseResultNotBurn = 0.9,
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
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

private:
	mat nominalFuseResults;
	int globalIteration;

	AnalysisUnit analysisUnit;
	DataHandler dataHandlerFuseTest;
	DataHandler dataHandlerKeepPowTest;
	ProcessUnitSR processUnit;
};