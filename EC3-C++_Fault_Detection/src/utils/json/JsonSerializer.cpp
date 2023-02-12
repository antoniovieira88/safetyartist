#include "include/JsonSerializer.h"

void std::to_json(json& j, const FaultModeAnalysisResultType& obj) {
	j = json{
		{"FaultModeId", obj.faultModeId},
		{"FaultModeName", obj.faultModeName},
		{"FuseTest", json(obj.fuseTestResult)},
		{"KeepPowerTest", json(obj.keepPowerTestResult)},
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