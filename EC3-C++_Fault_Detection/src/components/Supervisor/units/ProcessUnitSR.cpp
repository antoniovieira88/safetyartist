#include "../include/ProcessUnitSR.h"

/*

In this case, it was used the 'reference' cpp operator ('&') so that "ProcessUnitSR" class directly receives
the addresses of "analysisUnit" and "dataHandler" objects instantiated in the "Supervisor"
class - where "Process Unit" is also created. As a result, ProcessUnitSR stores references to "analysisUnit"
and "dataHandler" objects as class members

Obs.: When a variable of the type 'reference' is used, it is not necessary to append the pointer operator "*" to access
the pointed data - it is accessed simply by its name. If the operator '&' were not used,
an undesired copy of "analysisUnit" and "dataHandler" objects  would be created every time ProcessUnitSR constructor is called.
Moreover, reference members must be initialized using Initializer List.

*/
ProcessUnitSR::ProcessUnitSR(
	AnalysisUnit& analysisUnit,
	DataHandler& dataHandlerFuseTest,
	DataHandler& dataHandlerKeepPowTest,
	Supervised* supervised,
	mat& nominalFuseResults,
	mat& nominalKeepPowReadbacks,
	int& globalIteration,
	bool verboseMode) :
	globalIteration(globalIteration),
	nominalFuseResults(nominalFuseResults),
	nominalKeepPowReadbacks(nominalKeepPowReadbacks),
	analysisUnit(analysisUnit),
	dataHandlerFuseTest(dataHandlerFuseTest),
	dataHandlerKeepPowTest(dataHandlerKeepPowTest)
{
	ProcessUnitSR::supervisedPointer = supervised;

	ProcessUnitSR::overallSilhouetteDecreaseToleranceFuseTest = NAN;
	ProcessUnitSR::silhouetteClustersDecreaseToleranceFuseTest = NAN;
	ProcessUnitSR::imbalanceClustersIncreaseToleranceFuseTest = NAN;
	ProcessUnitSR::silhouetteClustersDecreaseToleranceKeepPowTest = NAN;
	ProcessUnitSR::imbalanceClustersIncreaseToleranceKeepPowTest = NAN;
	ProcessUnitSR::verboseMode = verboseMode;
	ProcessUnitSR::simulationName = "";
	ProcessUnitSR::lastPerfomedTest = test::none;

	newMetricsFuseTest = colvec(dataHandlerFuseTest.getNumberOfMetrics(), fill::zeros);
	previousMetricsFuseTest = colvec(dataHandlerFuseTest.getNumberOfMetrics(), fill::zeros);

	newMetricsKeepPowTest = colvec(dataHandlerKeepPowTest.getNumberOfMetrics(), fill::zeros);
	previousMetricsKeepPowTest = colvec(dataHandlerKeepPowTest.getNumberOfMetrics(), fill::zeros);

	fuseTest = 1.0;
	keepPower = 0.0;

	// Initializes all control flow attributes with 'false'
	controlFlowAttach = false;
	controlFlowRunTest = false;
	controlFlowReset = false;
	controlFlowGetReadyForNextSimulationCycle = false;
	controlFlowInitializeDataHandlers = false;
	controlFlowSetFuseTestBasicParams = false;
	controlFlowGetFuseTestResults = false;
	controlFlowGetKeepPowerTestResults = false;
	controlFlowGetLastPerfomedTest = false;
	controlFlowDeleteRecordsFromLatestIteration = false;
	controlFlowclearControlFlowProcessUnitSR = false;
	controlFlowDetectFailure = false;
	controlFlowRunFuseTest = false;
	controlFlowRunKeepPowTest = false;
	controlFlowCalculateMetricVariation = false;
	controlFlowGetFuseResult = false;
	controlFlowGetKeepPowReadback = false;
	controlFlowSetKeepPower = false;
	controlFlowSetFuseTest = false;
	controlFlowGetFuseTestMetricsStruct = false;
	controlFlowGetKeepPowerTestMetricsStruct = false;
}

ProcessUnitSR::~ProcessUnitSR()
{
	if (verboseMode)
	{
		cout << endl << "Supervisor deactivated" << endl;
	}
}

void ProcessUnitSR::attach(Supervised* supervisedPointer)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowAttach == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> attach");
	}

	else
	{
		controlFlowAttach = true;

		ProcessUnitSR::supervisedPointer = supervisedPointer;

		if (verboseMode)
		{
			cout << endl << "Supervised attached to supervisor" << endl;
		}

		// Releases controlFlowAttach after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowAttach == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> attach");
		}

		else
		{
			controlFlowAttach = false;
		}
	}
}

void ProcessUnitSR::runTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowRunTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runTest");
	}

	else
	{
		controlFlowRunTest = true;

		globalIteration++;
		if (globalIteration % 2 == 1)
		{
			lastPerfomedTest = test::fuseTest;
			runFuseTest();
		}
		else
		{
			lastPerfomedTest = test::keepPowerTest;
			runKeepPowTest();
		}

		// Releases controlFlowRunTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowRunTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runTest");
		}

		else
		{
			controlFlowRunTest = false;
		}
	}
}

void ProcessUnitSR::runFuseTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowRunFuseTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runFuseTest");
	}

	else
	{
		controlFlowRunFuseTest = true;

		arma::mat dataToCluster;
		bool failure = false;

		if (verboseMode)
		{
			cout << "Begin of a new diagnostic fuse test " << endl;
			cout << "Iteration of the initiated diagnostic test: " << globalIteration << endl;
		}

		keepPower = 1;
		setKeepPower(keepPower);

		fuseTest = 0.0;
		setFuseTest(fuseTest);

		fuseResultBurn = getFuseResult();

		if (verboseMode)
		{
			cout << "fuse_test = " << fuseTest << endl;
			cout << "fuse_result_burn = " << fuseResultBurn << endl;
		}

		fuseTest = 1.0;
		setFuseTest(fuseTest);

		fuseResultNotBurn = getFuseResult();

		if (verboseMode) {
			cout << "fuse_test = " << fuseTest << endl;
			cout << "fuse_result_not_burn = " << fuseResultNotBurn << endl;
		}

		mat fuseResults = { {0.0, 1.0},
						 {fuseResultBurn, fuseResultNotBurn} };

		dataHandlerFuseTest.insertNewHistoricalData(fuseResults);
		dataToCluster = dataHandlerFuseTest.getHistoricalDataToCluster();

		analysisUnit.cluster(dataToCluster, nominalFuseResults);

		newMetricsFuseTest = analysisUnit.getNewMetrics();
		dataHandlerFuseTest.insertNewMetrics(newMetricsFuseTest);

		previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();

		if (verboseMode)
		{
			cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
			cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
			cout << "OverallSilhouette: " << newMetricsFuseTest(overallSilhouette) << endl;

			mat centroids = analysisUnit.getCentroids();
			cout << "Centroids: " << centroids[0] << " , " << centroids[1] << endl;

		}

		// all metrics are used in the FuseTest
		bool metricsToAnalyse[5];
		fill_n(metricsToAnalyse, 5, true);

		detectFailure(
			previousMetricsFuseTest,
			newMetricsFuseTest,
			metricsToAnalyse,
			imbalanceClustersIncreaseToleranceFuseTest,
			silhouetteClustersDecreaseToleranceFuseTest,
			overallSilhouetteDecreaseToleranceFuseTest);

		if (faultDiagnosis.failure)
		{
			keepPower = 0.0;
			setKeepPower(keepPower);
			throw FailureDetectedExcep(faultDiagnosis);
		}

		else if (verboseMode)
		{
			cout << "-> End of the diagnostic fuse test. No failure detected. " << endl;
			cout << "Iteration of the finished diagnostic fuse test: " << globalIteration << endl;
		}

		// Releases controlFlowRunFuseTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowRunFuseTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runFuseTest");
		}

		else
		{
			controlFlowRunFuseTest = false;
		}
	}
}

void ProcessUnitSR::runKeepPowTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowRunKeepPowTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runKeepPowTest");
	}

	else
	{
		controlFlowRunKeepPowTest = true;

		arma::mat dataToCluster;
		bool failure = false;

		if (verboseMode)
		{
			cout << "Begin of a new diagnostic keep power test " << endl;
			cout << "Iteration of the initiated diagnostic keep power test: " << globalIteration << endl;
		}

		fuseTest = 1.0;
		setFuseTest(fuseTest);

		keepPower = 1;

		setKeepPower(keepPower);
		keepPowerReadbackOn = getKeepPowReadback();

		if (verboseMode)
		{
			cout << "keep_power = " << keepPower << endl;
			cout << "keep_power_readback = " << keepPowerReadbackOn << endl;
		}

		keepPower = 0;
		setKeepPower(keepPower);
		keepPowerReadbackOff = getKeepPowReadback();

		if (verboseMode)
		{
			cout << "keep_power = " << keepPower << endl;
			cout << "keep_power_readback = " << keepPowerReadbackOff << endl;
		}

		keepPower = 1;
		setKeepPower(keepPower);

		mat keepPowerReadbacks = { {0, 1},
								  {double(keepPowerReadbackOff), double(keepPowerReadbackOn)} };

		dataHandlerKeepPowTest.insertNewHistoricalData(keepPowerReadbacks);
		dataToCluster = dataHandlerKeepPowTest.getHistoricalDataToCluster();

		analysisUnit.cluster(dataToCluster, nominalKeepPowReadbacks);

		bool metricsToAnalyse[5];
		fill_n(metricsToAnalyse, 5, false);
		// only the metrics below are used in KeepPowerTest.
		metricsToAnalyse[numPointsCluster1] = true;
		metricsToAnalyse[numPointsCluster2] = true;

		newMetricsKeepPowTest = analysisUnit.getNewMetrics(metricsToAnalyse);
		dataHandlerKeepPowTest.insertNewMetrics(newMetricsKeepPowTest);

		previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();

		if (verboseMode)
		{
			cout << "Number of points: " << analysisUnit.getTotalNumberOfPoints() << endl;
			cout << "Number of clusters: " << analysisUnit.getNumberOfClusters() << endl;
		}

		detectFailure(
			previousMetricsKeepPowTest,
			newMetricsKeepPowTest,
			metricsToAnalyse,
			0.0,
			0.0,
			0);


		if (faultDiagnosis.failure)
		{
			fuseTest = 0.0;
			setFuseTest(fuseTest);
			throw FailureDetectedExcep(faultDiagnosis);
		}

		else if (verboseMode)
		{
			cout << "-> End of the diagnostic keep power test. No failure detected. " << endl;
			cout << "Iteration of the finished diagnostic keep power test: " << globalIteration << endl;
		}

		// Releases controlFlowRunKeepPowTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowRunKeepPowTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> runKeepPowTest");
		}

		else
		{
			controlFlowRunKeepPowTest = false;
		}
	}
}

double ProcessUnitSR::calculateMetricVariation(
	colvec& previousMetrics,
	colvec& newMetrics,
	int metricIndex)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowCalculateMetricVariation == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> calculateMetricVariation");
	}

	else
	{
		controlFlowCalculateMetricVariation = true;

		// Releases controlFlowCalculateMetricVariation after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowCalculateMetricVariation == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> calculateMetricVariation");
		}

		else
		{
			controlFlowCalculateMetricVariation = false;
			return newMetrics[metricIndex] - previousMetrics[metricIndex];
		}
	}	
}

double ProcessUnitSR::getFuseResult()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetFuseResult == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseResult");
	}

	else
	{
		controlFlowGetFuseResult = true;

		// Releases controlFlowGetFuseResult after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetFuseResult == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseResult");
		}

		else
		{
			controlFlowGetFuseResult = false;
			return supervisedPointer->getFuseResult();
		}
	}
}

int ProcessUnitSR::getKeepPowReadback()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetKeepPowReadback == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowReadback");
	}

	else
	{
		controlFlowGetKeepPowReadback = true;

		// Releases controlFlowGetKeepPowReadback after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetKeepPowReadback == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowReadback");
		}

		else
		{
			controlFlowGetKeepPowReadback = false;
			return supervisedPointer->getKeepPowReadback();
		}
	}
}

void ProcessUnitSR::reset()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowReset == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> reset");
	}

	else
	{
		controlFlowReset = true;

		globalIteration = 0;
		dataHandlerFuseTest.reset();
		dataHandlerKeepPowTest.reset();

		// Releases controlFlowReset after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowReset == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> reset");
		}

		else
		{
			controlFlowReset = false;
		}
	}
}

void ProcessUnitSR::detectFailure(
	colvec& previousMetrics,
	colvec& newMetrics,
	bool metricsToAnalyse[5],
	double imbalanceClustersIncreaseTolerance,
	double silhouetteClustersDecreaseTolerance,
	double overallSilhouetteDecreaseTolerance
)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowDetectFailure == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> detectFailure");
	}

	else
	{
		controlFlowDetectFailure = true;

		double imbalanceClustersNewMetrics, imbalanceClustersPreviousMetrics;
		double silhouetteCluster1Increase, silhouetteCluster2Increase,
			imbalanceClustersIncrease, overallSilhouetteIncrease;
		bool failure = false;
		bool anyMetricAnalysed = false;
		int metricIndex = 0;

		vector<FailureMetricIndicatorType> failureIndicators;

		if (verboseMode)
		{
			cout << "Failure detection process initiated" << endl;
		}

		// calculate the variation of each metric (the increase or decrease)
		// and then its compared to the tolerance value

		// silhouette of cluster 1
		if (metricsToAnalyse[silhouetteCluster1]) {
			anyMetricAnalysed = true;
			silhouetteCluster1Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
			if (verboseMode) cout << "Increase in silhouette of cluster 1: " << silhouetteCluster1Increase << endl;
			metricIndex++;

			if (silhouetteCluster1Increase < -silhouetteClustersDecreaseTolerance) {
				failure = true;
				FailureMetricIndicatorType failureIndicator = { silhouetteCluster1, silhouetteCluster1Increase, silhouetteClustersDecreaseTolerance, globalIteration };
				failureIndicators.push_back(failureIndicator);
			}
		}

		// silhouette of cluster 2
		if (metricsToAnalyse[silhouetteCluster2]) {
			anyMetricAnalysed = true;
			silhouetteCluster2Increase = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
			if (verboseMode) cout << "Increase in silhouette of cluster 2: " << silhouetteCluster2Increase << endl;
			metricIndex++;

			if (silhouetteCluster2Increase < -silhouetteClustersDecreaseTolerance) {
				failure = true;
				FailureMetricIndicatorType failureIndicator = { silhouetteCluster2, silhouetteCluster2Increase, silhouetteClustersDecreaseTolerance, globalIteration };
				failureIndicators.push_back(failureIndicator);
			}
		}

		// |number of points in cluster 2 - number of points in cluster 1|
		if (metricsToAnalyse[numPointsCluster1] && metricsToAnalyse[numPointsCluster2]) {
			anyMetricAnalysed = true;
			imbalanceClustersNewMetrics = abs(newMetrics[metricIndex + 1] - newMetrics[metricIndex]);
			imbalanceClustersPreviousMetrics = abs(previousMetrics[metricIndex + 1] - previousMetrics[metricIndex]);
			imbalanceClustersIncrease = imbalanceClustersNewMetrics - imbalanceClustersPreviousMetrics;
			if (verboseMode) cout << "Increase in cluster imbalance: " << imbalanceClustersIncrease << endl;
			metricIndex += 2;

			if (imbalanceClustersIncrease > imbalanceClustersIncreaseTolerance) {
				failure = true;
				FailureMetricIndicatorType failureIndicator = { imbalanceNumPoints, imbalanceClustersIncrease, imbalanceClustersIncreaseTolerance, globalIteration };
				failureIndicators.push_back(failureIndicator);
			}
		}

		// overall silhouette
		if (metricsToAnalyse[overallSilhouette]) {
			anyMetricAnalysed = true;
			overallSilhouetteIncrease = calculateMetricVariation(previousMetrics, newMetrics, metricIndex);
			if (verboseMode) cout << "Increase in overall silhouette: " << overallSilhouetteIncrease << endl;

			if (overallSilhouetteIncrease < -overallSilhouetteDecreaseTolerance) {
				failure = true;
				FailureMetricIndicatorType failureIndicator = { overallSilhouette, overallSilhouetteIncrease, overallSilhouetteDecreaseTolerance, globalIteration };
				failureIndicators.push_back(failureIndicator);
			}
		}

		// it throws an exception if no metric has been analyzed
		if (!anyMetricAnalysed) throw exception();

		faultDiagnosis = { failure, failureIndicators, lastPerfomedTest };

		if (verboseMode)
		{
			cout << "Failure detection process finished" << endl;
		}

		// Releases controlFlowDetectFailure after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowDetectFailure == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> detectFailure");
		}

		else
		{
			controlFlowDetectFailure = false;
		}
	}
}

void ProcessUnitSR::initializeDataHandlers()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowInitializeDataHandlers == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> initializeDataHandlers");
	}

	else
	{
		controlFlowInitializeDataHandlers = true;

		if (verboseMode) cout << "Simulation Name: " << simulationName << endl;

		dataHandlerFuseTest.initializeDataHandler();
		dataHandlerKeepPowTest.initializeDataHandler();

		previousMetricsFuseTest = dataHandlerFuseTest.getPreviousMetrics();
		int lastIterationFuseTest = dataHandlerFuseTest.getLastIterationInDataMemory();

		previousMetricsKeepPowTest = dataHandlerKeepPowTest.getPreviousMetrics();
		int lastIterationKeepPowTest = dataHandlerKeepPowTest.getLastIterationInDataMemory();

		// the global iteration parameter is the maximum value between the iterations
		// values provided by the two dataHandler units

		globalIteration =
		{ lastIterationFuseTest > lastIterationKeepPowTest
			? lastIterationFuseTest
			: lastIterationKeepPowTest
		};

		// Releases controlFlowInitializeDataHandlers after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowInitializeDataHandlers == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> initializeDataHandlers");
		}

		else
		{
			controlFlowInitializeDataHandlers = false;
		}
	}
}

void ProcessUnitSR::getReadyForNextSimulationCycle()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetReadyForNextSimulationCycle == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getReadyForNextSimulationCycle");
	}

	else
	{
		controlFlowGetReadyForNextSimulationCycle = true;

		dataHandlerFuseTest.updateHistoricalData();
		dataHandlerFuseTest.updateHistoricalMetrics();


		dataHandlerKeepPowTest.updateHistoricalData();
		dataHandlerKeepPowTest.updateHistoricalMetrics();

		if (verboseMode) {
			cout << "HistoricalData.csv and HistoricalMetrics.csv for FuseTest and KeepPowerTest"
				<< "updated in data memory" << endl;
		}

		// Releases controlFlowGetReadyForNextSimulationCycle after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetReadyForNextSimulationCycle == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getReadyForNextSimulationCycle");
		}

		else
		{
			controlFlowGetReadyForNextSimulationCycle = false;
		}
	}
}

void ProcessUnitSR::setVerboseMode(bool verboseModeValue)
{
	ProcessUnitSR::verboseMode = verboseModeValue;
}

void ProcessUnitSR::setSimulationName(string simulationName)
{
	ProcessUnitSR::simulationName = simulationName;
}

void ProcessUnitSR::setFuseTestBasicParams(
	double overallSilhouetteToleranceValue,
	double silhouetteDiffToleranceValue,
	double numberOfPointsPerClusterDiffToleranceValue)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetFuseTestBasicParams == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setFuseTestBasicParams");
	}

	else
	{
		controlFlowSetFuseTestBasicParams = true;

		ProcessUnitSR::overallSilhouetteDecreaseToleranceFuseTest = overallSilhouetteToleranceValue;
		ProcessUnitSR::silhouetteClustersDecreaseToleranceFuseTest = silhouetteDiffToleranceValue;
		ProcessUnitSR::imbalanceClustersIncreaseToleranceFuseTest = numberOfPointsPerClusterDiffToleranceValue;

		// Releases controlFlowSetFuseTestBasicParams after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetFuseTestBasicParams == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setFuseTestBasicParams");
		}

		else
		{
			controlFlowSetFuseTestBasicParams = false;
		}
	}
}

FuseTestResultsType ProcessUnitSR::getFuseTestResults()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetFuseTestResults == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseTestResults");
	}

	else
	{
		controlFlowGetFuseTestResults = true;

		FuseTestResultsType result;

		if (lastPerfomedTest == test::keepPowerTest)
		{
			result = {};
		}

		else
		{
			MetricsFuseTestType newMetrics = getFuseTestMetricsStruct(newMetricsFuseTest);
			MetricsFuseTestType previousMetrics = getFuseTestMetricsStruct(previousMetricsFuseTest);

			result = { faultDiagnosis,	previousMetrics, newMetrics, fuseResultBurn, fuseResultNotBurn };
		}

		// Releases controlFlowGetFuseTestResults after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetFuseTestResults == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseTestResults");
		}

		else
		{
			controlFlowGetFuseTestResults = false;
			return result;
		}
	}
}

KeepPowerTestResultsType ProcessUnitSR::getKeepPowerTestResults()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetKeepPowerTestResults == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowerTestResults");
	}

	else
	{
		controlFlowGetKeepPowerTestResults = true;

		KeepPowerTestResultsType result;

		if (lastPerfomedTest == test::fuseTest)
		{
			result = {};
		}

		else
		{
			MetricsKeepPowerTestType newMetrics = getKeepPowerTestMetricsStruct(newMetricsKeepPowTest);
			MetricsKeepPowerTestType previousMetrics = getKeepPowerTestMetricsStruct(previousMetricsKeepPowTest);
			result = { faultDiagnosis, previousMetrics,	newMetrics,	keepPowerReadbackOn, keepPowerReadbackOff };
		}

		// Releases controlFlowGetKeepPowerTestResults after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetKeepPowerTestResults == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowerTestResults");
		}

		else
		{
			controlFlowGetKeepPowerTestResults = false;
			return result;
		}
	}
}

test ProcessUnitSR::getLastPerfomedTest()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetLastPerfomedTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getLastPerfomedTest");
	}

	else
	{
		controlFlowGetLastPerfomedTest = true;

		// Releases controlFlowGetLastPerfomedTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetLastPerfomedTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getLastPerfomedTest");
		}

		else
		{
			controlFlowGetLastPerfomedTest = false;
			return lastPerfomedTest;
		}
	}
}

void ProcessUnitSR::deleteRecordsFromLatestIteration()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowDeleteRecordsFromLatestIteration == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> deleteRecordsFromLatestIteration");
	}

	else
	{
		controlFlowDeleteRecordsFromLatestIteration = true;

		dataHandlerFuseTest.deleteRecordsFromLatestIteration();
		dataHandlerKeepPowTest.deleteRecordsFromLatestIteration();
		globalIteration -= 2;

		// Releases controlFlowDeleteRecordsFromLatestIteration after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowDeleteRecordsFromLatestIteration == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> deleteRecordsFromLatestIteration");
		}

		else
		{
			controlFlowDeleteRecordsFromLatestIteration = false;
		}
	}
}

void ProcessUnitSR::setKeepPower(int keepPower)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetKeepPower == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setKeepPower");
	}

	else
	{
		controlFlowSetKeepPower = true;

		supervisedPointer->setKeepPower(keepPower);

		// Releases controlFlowSetKeepPower after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetKeepPower == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setKeepPower");
		}

		else
		{
			controlFlowSetKeepPower = false;
		}
	}
}

void ProcessUnitSR::setFuseTest(double fuseTest)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowSetFuseTest == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setFuseTest");
	}

	else
	{
		controlFlowSetFuseTest = true;

		supervisedPointer->setFuseTest(fuseTest);

		// Releases controlFlowSetFuseTest after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowSetFuseTest == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> setFuseTest");
		}

		else
		{
			controlFlowSetFuseTest = false;
		}
	}
}

MetricsFuseTestType ProcessUnitSR::getFuseTestMetricsStruct(colvec metricsArray)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetFuseTestMetricsStruct == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseTestMetricsStruct");
	}

	else
	{
		controlFlowGetFuseTestMetricsStruct = true;

		MetricsFuseTestType metricsStruct;
		metricsStruct.numPointsCluster1 = metricsArray[numPointsCluster1];
		metricsStruct.numPointsCluster2 = metricsArray[numPointsCluster2];
		metricsStruct.silhouetteCluster1 = metricsArray[silhouetteCluster1];
		metricsStruct.silhouetteCluster2 = metricsArray[silhouetteCluster2];
		metricsStruct.overallSilhouette = metricsArray[overallSilhouette];

		// Releases controlFlowGetFuseTestMetricsStruct after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetFuseTestMetricsStruct == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getFuseTestMetricsStruct");
		}

		else
		{
			controlFlowGetFuseTestMetricsStruct = false;
			return metricsStruct;
		}
	}
}

MetricsKeepPowerTestType ProcessUnitSR::getKeepPowerTestMetricsStruct(colvec metricsArray)
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowGetKeepPowerTestMetricsStruct == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowerTestMetricsStruct");
	}

	else
	{
		controlFlowGetKeepPowerTestMetricsStruct = true;

		MetricsKeepPowerTestType metricsStruct;
		metricsStruct.numPointsCluster1 = metricsArray[0];
		metricsStruct.numPointsCluster2 = metricsArray[1];

		// Releases controlFlowGetKeepPowerTestMetricsStruct after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowGetKeepPowerTestMetricsStruct == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> getKeepPowerTestMetricsStruct");
		}

		else
		{
			controlFlowGetKeepPowerTestMetricsStruct = false;
			return metricsStruct;
		}
	}
}

void ProcessUnitSR::clearControlFlowProcessUnitSR()
{
	// Checks if a prior execution of the method has been started and throws exception in this case; otherwise, runs the method.
	if (controlFlowclearControlFlowProcessUnitSR == true)
	{
		throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> clearControlFlowProcessUnitSR");
	}

	else
	{
		controlFlowclearControlFlowProcessUnitSR = true;

		controlFlowAttach = false;
		controlFlowRunTest = false;
		controlFlowReset = false;
		controlFlowGetReadyForNextSimulationCycle = false;
		controlFlowInitializeDataHandlers = false;
		controlFlowSetFuseTestBasicParams = false;
		controlFlowGetFuseTestResults = false;
		controlFlowGetKeepPowerTestResults = false;
		controlFlowGetLastPerfomedTest = false;
		controlFlowDeleteRecordsFromLatestIteration = false;
		controlFlowDetectFailure = false;
		controlFlowRunFuseTest = false;
		controlFlowRunKeepPowTest = false;
		controlFlowCalculateMetricVariation = false;
		controlFlowGetFuseResult = false;
		controlFlowGetKeepPowReadback = false;
		controlFlowSetKeepPower = false;
		controlFlowSetFuseTest = false;
		controlFlowGetFuseTestMetricsStruct = false;
		controlFlowGetKeepPowerTestMetricsStruct = false;

		// Releases controlFlowclearControlFlowProcessUnitSR after the method is finished with correct execution. Throws exception if the current execution has not begun from the start.
		if (controlFlowclearControlFlowProcessUnitSR == false)
		{
			throw SimulatorFailureExcep("Invalid control flow", "Supervisor ==> ProcessUnitSR ==> clearControlFlowProcessUnitSR");
		}

		else
		{
			controlFlowclearControlFlowProcessUnitSR = false;
		}
	}
}