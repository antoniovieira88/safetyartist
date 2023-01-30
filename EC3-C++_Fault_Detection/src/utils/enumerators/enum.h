#include <string>

using namespace std;

#pragma once
enum metrics {
	silhouetteCluster1 = 0,
	silhouetteCluster2 = 1,
	numPointsCluster1 = 2,
	numPointsCluster2 = 3,
	overallSilhouette = 4,
	imbalanceNumPoints = 5
};