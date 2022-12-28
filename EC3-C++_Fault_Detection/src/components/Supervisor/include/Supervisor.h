#include "ProcessUnitSR.h"

class Supervisor
{
public:
	Supervisor(
		int maxNumberOfRegisters,
		double nominalFuseResultBurn, double nominalFuseResultNotBurn,
		double overallSilhouetteTolerance,
		double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance,
		bool verboseMode);

	void attach(Supervised* supervised);
	void runTest();
	void reset();
	int* getIterationPointer();
	void reinitializeForNewSimulation();

private:
	mat nominalFuseResults;

	AnalysisUnit analysisUnit;
	DataHandler dataHandler;
	ProcessUnitSR processUnit;
};