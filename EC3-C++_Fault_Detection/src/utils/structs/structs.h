#include "../enumerators/enum.h"
#include <vector>

#pragma once

struct failureMetricIndicatorType {
	metrics metric;
	double variation;
	double tolerance;
	int iteration;
};