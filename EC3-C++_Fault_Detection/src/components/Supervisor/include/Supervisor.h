#include "ProcessUnitSR.h"

class Supervisor
{
public:
	Supervisor(
		int maxNumberOfRegisters,
		double overallSilhouetteTolerance,
		double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance,
		bool verboseMode);
	void attach(Supervised* supervised);
	void newTest();
	int* getIterationPointer();

private:
	AnalysisUnit analysisUnit;
	DataHandler dataHandler;
	ProcessUnitSR processUnit;
};