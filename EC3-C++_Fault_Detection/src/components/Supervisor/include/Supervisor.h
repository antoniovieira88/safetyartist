#include "ProcessUnitSR.h"

using namespace std;

class Supervisor {
public:
	Supervisor(
		int maxNumberOfRegisters,
		double nominalFuseResultBurn = 0.1, double nominalFuseResultNotBurn = 0.9,
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true);

	Supervisor(
		int maxNumberOfRegisters,
		double nominalFuseResultBurn, double nominalFuseResultNotBurn,
		double overallSilhouetteTolerance,
		double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance,
		string dataMemoryDir = "data/DataMemory",
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true);

	void attach(Supervised* supervised);
	void runTest();
	void reset();
	int* getIterationPointer();
	void getReadyForNextSimulationCycle();
	void prepareForSimulation(string simulationName);
	void setVerboseMode(bool verboseModeValue);
	void setBasicParams(
		double overallSilhouetteToleranceValue,
		double silhouetteDiffToleranceValue,
		double numberOfPointsPerClusterDiffToleranceValue);

private:
	mat nominalFuseResults;

	AnalysisUnit analysisUnit;
	DataHandler dataHandler;
	ProcessUnitSR processUnit;
};