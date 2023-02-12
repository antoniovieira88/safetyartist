#include <string>

using namespace std;

#pragma once
namespace std {
	static string metricStr[] =
	{
	  "silhouetteCluster1",
	  "silhouetteCluster2",
	  "numPointsCluster1",
	  "numPointsCluster2",
	  "overallSilhouette",
	  "imbalanceNumPoints"
	};

	static string testStr[] = {
		"none",
		"fuseTest",
		"keepPowerTest"
	};

	static string fmSafetyStr[]{
		"safe",
		"unsafe"
	};

	static string fmDetectableStr[]{
		"yes",
		"no",
		"impactless",
		"outside_scope",
		"maybe"
	};

	static string classMultipleFaultsStr[]{
		"cm0",
		"cm1",
		"cm2",
		"cm3",
		"not_applicable"
	};

	enum metrics {
		silhouetteCluster1 = 0,
		silhouetteCluster2 = 1,
		numPointsCluster1 = 2,
		numPointsCluster2 = 3,
		overallSilhouette = 4,
		imbalanceNumPoints = 5
	};

	enum test {
		none = 0,
		fuseTest = 1,
		keepPowerTest = 2,
	};

	enum fmSafety {
		safe = 0,
		unsafe = 1
	};

	enum fmDetectable {
		yes = 0,
		no = 1,
		impactless = 2,
		outside_scope = 3,
		maybe = 4
	};

	enum classMultipleFaults {
		cm0 = 0,
		cm1 = 1,
		cm2 = 2,
		cm3 = 3,
		not_applicable
	};
}