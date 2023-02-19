#include "include/JsonSerializer.h"

void std::to_json(json& j, const FaultModeAnalysisResultType& obj) {
	j = json{
		{"FaultModeId", obj.faultMode.id},
		{"FaultModeName", obj.faultMode.name},
		{"AddInfo", json(obj.faultMode)},
		{"FuseTest", json(obj.fuseTestResult)},
		{"KeepPowerTest", json(obj.keepPowerTestResult)},
	};
}

void std::to_json(json& j, const FaultModeType& obj)
{
	j = json{
		{"componentId", obj.componentId},
		{"probability", obj.probability},
		{"fmSafety", fmSafetyStr[obj.fmSafety]},
		{"fmDetectableFuse", fmDetectableStr[obj.fmDetectableFuse]},
		{"fmDetectableKeepPow", fmDetectableStr[obj.fmDetectableKeepPow]},
		{"classMultipleFaults", classMultipleFaultsStr[obj.classMultipleFaults]},
	};
}

void std::to_json(json& j, const FuseTestResultsType& obj) {
	j = json{
		{"Burn", obj.fuseResultBurn},
		{"NotBurn", obj.fuseResultNotBurn},
		{"FaultDiagnosis", json(obj.faultDiagnosis)},
		{"previousMetrics", json(obj.previousMetrics)},
		{"newMetrics", json(obj.newMetrics)}
	};
}

void std::to_json(json& j, const MetricsFuseTestType& obj)
{
	j = json{
		{"silhouetteCluster1", obj.silhouetteCluster1},
		{"silhouetteCluster2", obj.silhouetteCluster2},
		{"numPointsCluster1", obj.numPointsCluster1},
		{"numPointsCluster2", obj.numPointsCluster2},
		{"overallSilhouette", obj.overallSilhouette},
	};
}

void std::to_json(json& j, const KeepPowerTestResultsType& obj) {
	j = json{
		{"On", obj.keepPowerReadbackOn},
		{"Off", obj.keepPowerReadbackOff},
		{"FaultDiagnosis", json(obj.faultDiagnosis)},
		{"previousMetrics", json(obj.previousMetrics)},
		{"newMetrics", json(obj.newMetrics)}
	};
}

void std::to_json(json& j, const MetricsKeepPowerTestType& obj)
{
	j = json{
		{"numPointsCluster1", obj.numPointsCluster1},
		{"numPointsCluster2", obj.numPointsCluster2},
	};
}

void std::to_json(json& j, const FaultDiagnosisType& obj) {
	j = json{
		{"Failure", obj.failure},
		{"PerfomedTest", testStr[obj.perfomedTest]},
		{"FailureIndicators", json(obj.failureIndicators)},
	};
}

void std::to_json(json& j, const FailureMetricIndicatorType& obj) {
	j = json{
		{"Metric", metricStr[obj.metric]},
		{"Tolerance", obj.tolerance},
		{"Variation", obj.variation},
	};
}