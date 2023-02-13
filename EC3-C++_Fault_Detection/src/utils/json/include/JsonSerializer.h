#include "../../structs/structs.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace std {
	void to_json(json& j, const FaultModeAnalysisResultType& obj);

	void to_json(json& j, const FaultModeType& obj);

	void to_json(json& j, const FuseTestResultsType& obj);

	void to_json(json& j, const MetricsFuseTestType& obj);

	void to_json(json& j, const KeepPowerTestResultsType& obj);

	void to_json(json& j, const MetricsKeepPowerTestType& obj);

	void to_json(json& j, const FaultDiagnosisType& obj);

	void to_json(json& j, const FailureMetricIndicatorType& obj);
}