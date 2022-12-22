#include "../enumerators/enum.h"

#pragma once

struct failureMetricIndicatorType {
	metrics metric;
	double variation;
	double tolerance;
	int iteration;
};

struct FailureScenarioType {
	double meanValueFuseResultBurn;
	double meanValueFuseResultNotBurn;
	double minFuseResultBurn;
	double maxFuseResultBurn;
	double minFuseResultNotBurn;
	double maxFuseResultNotBurn;
};

struct TestScenarioType {
	int numberOfFailedComponents;
	FailureScenarioType* singleFailureScenario;
};