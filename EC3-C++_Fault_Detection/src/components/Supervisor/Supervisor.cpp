#include "include/Supervisor.h"


Supervisor::Supervisor(
	int maxNumberOfRegisters,
	double overallSilhouetteTolerance,
	double silhouetteDiffTolerance,
	double numberOfPointsPerClusterDiffTolerance,
	bool verboseMode)
	:
	analysisUnit(2),
	dataHandler(maxNumberOfRegisters),
	processUnit(
		analysisUnit,
		dataHandler,
		NULL,
		overallSilhouetteTolerance,
		silhouetteDiffTolerance,
		numberOfPointsPerClusterDiffTolerance,
		verboseMode)
{}

void Supervisor::attach(Supervised* supervised) {
	processUnit.attach(supervised);
}

void Supervisor::newTest() {
	processUnit.newTest();
}

int* Supervisor::getIterationPointer()
{
	return dataHandler.getIterationPointer();
}
