#include "include/Supervisor.h"

Supervisor::Supervisor(
	string dataMemoryDir,
	string simulationMemoryDir,
	int maxNumberOfRegisters,
	double nominalFuseResultBurn,
	double nominalFuseResultNotBurn,
	bool verboseMode) :
	nominalFuseResults(1, 2),
	nominalKeepPowReadbacks(1, 2),
	analysisUnit(2),
	dataHandlerFuseTest(globalIteration, maxNumberOfRegisters, 5,
		"FuseTest", verboseMode, dataMemoryDir, simulationMemoryDir),
	dataHandlerKeepPowTest(globalIteration, maxNumberOfRegisters, 2,
		"KeepPowerTest", verboseMode, dataMemoryDir, simulationMemoryDir),
	processUnit(
		analysisUnit,
		dataHandlerFuseTest,
		dataHandlerKeepPowTest,
		nullptr,
		nominalFuseResults,
		nominalKeepPowReadbacks,
		globalIteration,
		verboseMode)
{
	// the nominals values for fuseResult will be set again when a supervised object
	// is attached to supervisor. The values set come from the Supervised definition
	Supervisor::nominalFuseResults(0, 0) = nominalFuseResultBurn;
	Supervisor::nominalFuseResults(0, 1) = nominalFuseResultNotBurn;

	// the nominal values for keepPowerReadback are constants,
	// independently of the simulation parameters
	Supervisor::nominalKeepPowReadbacks(0, 0) = 0;
	Supervisor::nominalKeepPowReadbacks(0, 1) = 1;

	Supervisor::globalIteration = 0;

	controlFlowAttach = false;
	controlFlowRunTest = false;
	controlFlowReset = false;
	controlFlowGetIterationPointer = false;
	controlFlowGetReadyForNextSimulationCycle = false;
	controlFlowPrepareForSimulation = false;
	controlFlowSetBasicParams = false;
	controlFlowGetFuseTestResults = false;
	controlFlowGetKeepPowerTestResults = false;
	controlFlowDeleteRecordsFromLatestIteration = false;
	controlFlowLogFilesConfig = false;
	controlFlowGetLastPerfomedTest = false;
	controlFlowUpdateDataMemory = false;
	controlFlowClearControlFlowSupervisor = false;
}

void Supervisor::attach(Supervised* supervisedPointer)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowAttach == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> attach");
	}

	else
	{
		controlFlowAttach = true;

		processUnit.attach(supervisedPointer);
		nominalFuseResults(0, 0) = supervisedPointer->getNominalFuseResults()[0];
		nominalFuseResults(0, 1) = supervisedPointer->getNominalFuseResults()[1];

		// Releases controlFlowAttach after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowAttach == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> attach");
		}

		else
		{
			controlFlowAttach = false;
		}
	}	
}

void Supervisor::runTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowRunTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> runTest");
	}

	else
	{
		controlFlowRunTest = true;

		processUnit.runTest();

		// Releases controlFlowRunTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowRunTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> runTest");
		}

		else
		{
			controlFlowRunTest = false;
		}
	}
}

void Supervisor::reset()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowReset == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> reset");
	}

	else
	{
		controlFlowReset = true;

		processUnit.reset();

		// Releases controlFlowReset after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowReset == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> reset");
		}

		else
		{
			controlFlowReset = false;
		}
	}
}

int* Supervisor::getIterationPointer()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetIterationPointer == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getIterationPointer");
	}

	else
	{
		controlFlowGetIterationPointer = true;

		// Releases controlFlowGetIterationPointer after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetIterationPointer == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getIterationPointer");
		}

		else
		{
			controlFlowGetIterationPointer = false;
			return &globalIteration;
		}
	}
}

void Supervisor::getReadyForNextSimulationCycle()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetReadyForNextSimulationCycle == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getReadyForNextSimulationCycle");
	}

	else
	{
		controlFlowGetReadyForNextSimulationCycle = true;

		processUnit.getReadyForNextSimulationCycle();

		// Releases controlFlowGetReadyForNextSimulationCycle after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetReadyForNextSimulationCycle == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getReadyForNextSimulationCycle");
		}

		else
		{
			controlFlowGetReadyForNextSimulationCycle = false;
		}
	}
}

void Supervisor::prepareForSimulation()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowPrepareForSimulation == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> prepareForSimulation");
	}

	else
	{
		controlFlowPrepareForSimulation = true;

		processUnit.initializeDataHandlers();

		// Releases controlFlowPrepareForSimulation after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowPrepareForSimulation == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> prepareForSimulation");
		}

		else
		{
			controlFlowPrepareForSimulation = false;
		}
	}
}

void Supervisor::setVerboseMode(bool verboseModeValue)
{
	processUnit.setVerboseMode(verboseModeValue);
}

void Supervisor::setBasicParams(
	double nominalValueFuseResultBurn,
	double nominalValueFuseResultNotBurn,
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue,
	int maxNumberOfRegisters,
	string simulationName)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetBasicParams == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> setBasicParams");
	}

	else
	{
		controlFlowSetBasicParams = true;

		// here the centroids for analysis are set
		// PS: note that analysisUnit received a reference for the array below
		nominalFuseResults(0, 0) = nominalValueFuseResultBurn;
		nominalFuseResults(0, 1) = nominalValueFuseResultNotBurn;

		// basic params for processUnit
		processUnit.setSimulationName(simulationName);
		processUnit.setFuseTestBasicParams(
			overallSilhouetteToleranceValue,
			silhouetteDiffToleranceValue,
			numberOfPointsPerClusterDiffToleranceValue); // params for failure detection

		// basic params for dataHandlerFuseTest
		dataHandlerFuseTest.setMaxNumberOfRegisters(maxNumberOfRegisters);
		dataHandlerFuseTest.setSimulationName(simulationName);

		// basic params for dataHandlerKeepPowTest
		dataHandlerKeepPowTest.setMaxNumberOfRegisters(maxNumberOfRegisters);
		dataHandlerKeepPowTest.setSimulationName(simulationName);

		// Releases controlFlowSetBasicParams after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetBasicParams == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> setBasicParams");
		}

		else
		{
			controlFlowSetBasicParams = false;
		}
	}
}

FuseTestResultsType Supervisor::getFuseTestResults()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetFuseTestResults == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getFuseTestResults");
	}

	else
	{
		controlFlowGetFuseTestResults = true;

		// Releases controlFlowGetFuseTestResults after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetFuseTestResults == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getFuseTestResults");
		}

		else
		{
			controlFlowGetFuseTestResults = false;
			return processUnit.getFuseTestResults();
		}
	}
}

KeepPowerTestResultsType Supervisor::getKeepPowerTestResults()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetKeepPowerTestResults == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getKeepPowerTestResults");
	}

	else
	{
		controlFlowGetKeepPowerTestResults = true;

		// Releases controlFlowGetKeepPowerTestResults after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetKeepPowerTestResults == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getKeepPowerTestResults");
		}

		else
		{
			controlFlowGetKeepPowerTestResults = false;
			return processUnit.getKeepPowerTestResults();
		}
	}
}

void Supervisor::deleteRecordsFromLatestIteration()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowDeleteRecordsFromLatestIteration == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> deleteRecordsFromLatestIteration");
	}

	else
	{
		controlFlowDeleteRecordsFromLatestIteration = true;

		processUnit.deleteRecordsFromLatestIteration();

		// Releases controlFlowDeleteRecordsFromLatestIteration after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowDeleteRecordsFromLatestIteration == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> deleteRecordsFromLatestIteration");
		}

		else
		{
			controlFlowDeleteRecordsFromLatestIteration = false;
		}
	}
}

void Supervisor::logFilesConfig(bool enable)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowLogFilesConfig == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> logFilesConfig");
	}

	else
	{
		controlFlowLogFilesConfig = true;

		dataHandlerFuseTest.logFilesConfig(enable);
		dataHandlerKeepPowTest.logFilesConfig(enable);

		// Releases controlFlowLogFilesConfig after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowLogFilesConfig == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> logFilesConfig");
		}

		else
		{
			controlFlowLogFilesConfig = false;
		}
	}
}

test Supervisor::getLastPerfomedTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetLastPerfomedTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getLastPerfomedTest");
	}

	else
	{
		controlFlowGetLastPerfomedTest = true;

		// Releases controlFlowGetLastPerfomedTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetLastPerfomedTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> getLastPerfomedTest");
		}

		else
		{
			controlFlowGetLastPerfomedTest = false;
			return processUnit.getLastPerfomedTest();
		}
	}
}

void Supervisor::updateDataMemory()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowUpdateDataMemory == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> updateDataMemory");
	}

	else
	{
		controlFlowUpdateDataMemory = true;

		dataHandlerFuseTest.updateHistoricalData();
		dataHandlerFuseTest.updateHistoricalMetrics();
		dataHandlerKeepPowTest.updateHistoricalData();
		dataHandlerKeepPowTest.updateHistoricalMetrics();

		// Releases controlFlowUpdateDataMemory after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowUpdateDataMemory == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> updateDataMemory");
		}

		else
		{
			controlFlowUpdateDataMemory = false;
		}
	}
}

void Supervisor::clearControlFlowSupervisor()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowClearControlFlowSupervisor == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> clearControlFlowSupervisor");
	}

	else
	{
		controlFlowClearControlFlowSupervisor = true;

		// Clears the control flow flags of the Supervisor
		controlFlowAttach = false;
		controlFlowRunTest = false;
		controlFlowReset = false;
		controlFlowGetIterationPointer = false;
		controlFlowGetReadyForNextSimulationCycle = false;
		controlFlowPrepareForSimulation = false;
		controlFlowSetBasicParams = false;
		controlFlowGetFuseTestResults = false;
		controlFlowGetKeepPowerTestResults = false;
		controlFlowDeleteRecordsFromLatestIteration = false;
		controlFlowLogFilesConfig = false;
		controlFlowGetLastPerfomedTest = false;
		controlFlowUpdateDataMemory = false;

		// Clears the control flow flags of the ProcessUnitSR
		processUnit.clearControlFlowProcessUnitSR();

		// Releases controlFlowClearControlFlowSupervisor after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowClearControlFlowSupervisor == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> clearControlFlowSupervisor");
		}

		else
		{
			controlFlowClearControlFlowSupervisor = false;
		}
	}
}