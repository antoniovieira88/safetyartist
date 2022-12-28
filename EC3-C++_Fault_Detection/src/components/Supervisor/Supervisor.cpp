#include "include/Supervisor.h"


Supervisor::Supervisor(
	int maxNumberOfRegisters,
	double nominalFuseResultBurn, double nominalFuseResultNotBurn,
	double overallSilhouetteTolerance,
	double silhouetteDiffTolerance,
	double numberOfPointsPerClusterDiffTolerance,
	bool verboseMode)
	:
	nominalFuseResults(1, 2),
	analysisUnit(2, nominalFuseResults),
	dataHandler(maxNumberOfRegisters),
	processUnit(
		analysisUnit,
		dataHandler,
		NULL,
		overallSilhouetteTolerance,
		silhouetteDiffTolerance,
		numberOfPointsPerClusterDiffTolerance,
		verboseMode)
{
	Supervisor::nominalFuseResults(0, 0) = nominalFuseResultBurn;
	Supervisor::nominalFuseResults(0, 1) = nominalFuseResultNotBurn;
}

void Supervisor::attach(Supervised* supervisedPointer) {
	processUnit.attach(supervisedPointer);
}

void Supervisor::runTest() {
	processUnit.runTest();
}

void Supervisor::reset()
{
	processUnit.reset();
}

int* Supervisor::getIterationPointer()
{
	return dataHandler.getIterationPointer();
}

void Supervisor::reinitializeForNewSimulation()
{
	dataHandler.saveNewMetrics();
	dataHandler.updateHistoricalData();
	processUnit.initializeDataHandler();
}
