#include "include/Supervisor.h"

Supervisor::Supervisor(
	int maxNumberOfRegisters,
	double nominalFuseResultBurn,
	double nominalFuseResultNotBurn,
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	nominalFuseResults(1, 2),
	analysisUnit(2, nominalFuseResults),
	dataHandler(maxNumberOfRegisters, dataMemoryDir, simulationMemoryDir),
	processUnit(
		analysisUnit,
		dataHandler,
		NULL,
		verboseMode)
{
	Supervisor::nominalFuseResults(0, 0) = nominalFuseResultBurn;
	Supervisor::nominalFuseResults(0, 1) = nominalFuseResultNotBurn;
}

Supervisor::Supervisor(
	int maxNumberOfRegisters,
	double nominalFuseResultBurn, double nominalFuseResultNotBurn,
	double overallSilhouetteTolerance,
	double silhouetteDiffTolerance,
	double numberOfPointsPerClusterDiffTolerance,
	string dataMemoryDir,
	string simulationMemoryDir,
	bool verboseMode) :
	nominalFuseResults(1, 2),
	analysisUnit(2, nominalFuseResults),
	dataHandler(maxNumberOfRegisters, dataMemoryDir, simulationMemoryDir),
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

void Supervisor::getReadyForNextSimulationCycle()
{
	processUnit.getReadyForNextSimulationCycle();
}

void Supervisor::prepareForSimulation(string simulationName)
{
	processUnit.initializeDataHandler(simulationName);
}

void Supervisor::setVerboseMode(bool verboseModeValue)
{
	processUnit.setVerboseMode(verboseModeValue);
}

void Supervisor::setBasicParams(
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue)
{
	processUnit.setBasicParams(
		overallSilhouetteToleranceValue,
		silhouetteDiffToleranceValue,
		numberOfPointsPerClusterDiffToleranceValue);
}
