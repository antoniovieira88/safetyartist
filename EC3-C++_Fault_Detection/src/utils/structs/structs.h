#include "../enumerators/enum.h"
#include <vector>

#pragma once

struct failureMetricIndicatorType {
	metrics metric;
	double variation;
	double tolerance;
	int iteration;
};

struct failureModeType {
	int componentId;
	double probability;
	double expectedFuseResultBurn;
	double expectedFuseResultNotBurn;
};