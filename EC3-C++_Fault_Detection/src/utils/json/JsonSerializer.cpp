#include "include/JsonSerializer.h"

void std::to_json(json& j, const FaultModeAnalysisResultType& obj) {
	j = json{
		{"ComponentName", obj.componentName},
		{"FaultModeId", to_string(obj.faultMode.id)},
		{"FaultModeName", obj.faultMode.name},
		{"AddInfo", json(obj.faultMode)},
		{"FuseTest", json(obj.fuseTestResult)},
		{"KeepPowerTest", json(obj.keepPowerTestResult)},
	};
}

void std::to_json(json& j, const FaultModeType& obj)
{
	j = json{
		{"componentId", to_string(obj.componentId)},
		{"probability", to_string(obj.probability)},
		{"fmSafety", fmSafetyStr[obj.fmSafety]},
		{"fmDetectableFuse", fmDetectableStr[obj.fmDetectableFuse]},
		{"fmDetectableKeepPow", fmDetectableStr[obj.fmDetectableKeepPow]},
		{"classMultipleFaults", classMultipleFaultsStr[obj.classMultipleFaults]},
	};
}

void std::to_json(json& j, const FuseTestResultsType& obj) {
	j = json{
		{"Burn", to_string(obj.fuseResultBurn)},
		{"NotBurn", to_string(obj.fuseResultNotBurn)},
		{"FaultDiagnosis", json(obj.faultDiagnosis)},
		{"previousMetrics", json(obj.previousMetrics)},
		{"newMetrics", json(obj.newMetrics)},
		{"overallScoreVar", convertDoubleToStr(obj.newMetrics.overallSilhouette - obj.previousMetrics.overallSilhouette)},
		{"cluster1ScoreVar", convertDoubleToStr(obj.newMetrics.silhouetteCluster1 - obj.previousMetrics.silhouetteCluster1)},
		{"cluster2ScoreVar", convertDoubleToStr(obj.newMetrics.silhouetteCluster2 - obj.previousMetrics.silhouetteCluster2)},
	};
}

void std::to_json(json& j, const MetricsFuseTestType& obj)
{
	j = json{
		{"silhouetteCluster1", convertDoubleToStr(obj.silhouetteCluster1)},
		{"silhouetteCluster2", convertDoubleToStr(obj.silhouetteCluster2)},
		{"numPointsCluster1", convertDoubleToStr(obj.numPointsCluster1)},
		{"numPointsCluster2", convertDoubleToStr(obj.numPointsCluster2)},
		{"overallSilhouette", convertDoubleToStr(obj.overallSilhouette)},
	};
}

void std::to_json(json& j, const KeepPowerTestResultsType& obj) {
	j = json{
		{"On", to_string(obj.keepPowerReadbackOn)},
		{"Off", to_string(obj.keepPowerReadbackOff)},
		{"FaultDiagnosis", json(obj.faultDiagnosis)},
		{"previousMetrics", json(obj.previousMetrics)},
		{"newMetrics", json(obj.newMetrics)}
	};
}

void std::to_json(json& j, const MetricsKeepPowerTestType& obj)
{
	j = json{
		{"numPointsCluster1", to_string(obj.numPointsCluster1)},
		{"numPointsCluster2", to_string(obj.numPointsCluster2)},
	};
}

void std::to_json(json& j, const FaultDiagnosisType& obj) {
	j = json{
		{"Failure", boolStr[obj.failure]},
		{"PerformedTest", testStr[obj.perfomedTest]},
		{"FailureIndicators", json(obj.failureIndicators)},
	};
}

void std::to_json(json& j, const FailureMetricIndicatorType& obj) {
	j = json{
		{"Metric", metricStr[obj.metric]},
		{"Tolerance", to_string(obj.tolerance)},
		{"Variation", convertDoubleToStr(obj.variation)},
	};
}

void std::to_json(json& j, const FailureEventType& obj)
{
	j = json{
		{"Component", obj.componentName},
		{"FaultMode", obj.faultMode.name},
		{"FaultModeId", obj.faultMode.id},
		{"Iteration", obj.iteration},
		{"IterationOnFailure", obj.iterationOnFailure},
		{"PerformedTest", testStr[obj.testName]},
		{"FaultModeInfo", json(obj.faultMode)},
		{"FailureDetected", obj.failureDetected},
		{"ForcedEnd", obj.forcedEnd}
	};

	if (obj.testName == fuseTest) {
		j["SupervisorResult"] = obj.fuseTestResults;
		j["NominalValues"]["Burn"] = obj.faultMode.singleFailureScenario.fuseFailureScenario.meanValueFuseResultBurn;
		j["NominalValues"]["NotBurn"] = obj.faultMode.singleFailureScenario.fuseFailureScenario.meanValueFuseResultNotBurn;
	}
	else {
		j["SupervisorResult"] = obj.keepPowerTestResults;
		j["NominalValues"]["On"] = obj.faultMode.singleFailureScenario.keepPowFailureScenario.keepPowerReadbackOnValue;
		j["NominalValues"]["Off"] = obj.faultMode.singleFailureScenario.keepPowFailureScenario.keepPowerReadbackOffValue;
	}
}

string std::convertDoubleToStr(double value)
{
	ostringstream ss;

	ss << value;

	return ss.str();
}
