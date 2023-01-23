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
	dataHandlerFuseTest(globalIteration, maxNumberOfRegisters, 5,
		"FuseTest", verboseMode, dataMemoryDir, simulationMemoryDir),
	dataHandlerKeepPowTest(globalIteration, maxNumberOfRegisters, 3,
		"KeepPowerTest", verboseMode, dataMemoryDir, simulationMemoryDir),
	processUnit(
		analysisUnit,
		dataHandlerFuseTest,
		dataHandlerKeepPowTest,
		nullptr,
		globalIteration,
		verboseMode)
{
	// the nominals values for fuseResult will be set again when a supervised object
	// is attached to supervisor. The values set come from the Supervised definition
	Supervisor::nominalFuseResults(0, 0) = nominalFuseResultBurn;
	Supervisor::nominalFuseResults(0, 1) = nominalFuseResultNotBurn;

	Supervisor::globalIteration = 0;
}

void Supervisor::attach(Supervised* supervisedPointer) {
	processUnit.attach(supervisedPointer);
	nominalFuseResults(0, 0) = supervisedPointer->getNominalFuseResults()[0];
	nominalFuseResults(0, 1) = supervisedPointer->getNominalFuseResults()[1];
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
	return &globalIteration;
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

// ! need to re-factor later!!
void Supervisor::setBasicParams(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue,
	int maxNumberOfRegisters)
{
	nominalFuseResults(0, 0) = nominalValueFuseResultBurn;
	nominalFuseResults(0, 1) = nominalValueFuseResultNotBurn;
	dataHandlerFuseTest.setMaxNumberOfRegisters(maxNumberOfRegisters);
	processUnit.setFuseTestBasicParams(
		overallSilhouetteToleranceValue,
		silhouetteDiffToleranceValue,
		numberOfPointsPerClusterDiffToleranceValue);
}
