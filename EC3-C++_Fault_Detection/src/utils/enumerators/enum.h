#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <limits>

using namespace std;

#pragma once
namespace std {
	enum metrics {
		silhouetteCluster1 = 0,
		silhouetteCluster2 = 1,
		numPointsCluster1 = 2,
		numPointsCluster2 = 3,
		overallSilhouette = 4,
		imbalanceNumPoints = 5
	};

	enum componentOpStatus {
		noFault = 0,
		newFault = 1,
		previousFault = 2
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
		outsideScope = 3,
		maybe = 4
	};

	enum classMultipleFaults {
		cm0 = 0,
		cm1 = 1,
		cm2 = 2,
		cm3 = 3,
		notApplicable = 4
	};

	enum simulationMemberObj {
		processUnit = 0,
		paramsController = 1,
		failureController = 2,
		generator = 5,
		simulationName = 6,
		iterationPointer = 7,
		simulationSpecificParams = 8,
		verboseMode = 9,
		iterationEquivalentTime = 10,
		componentsArray = 11,
		testScenario = 12,
	};

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

	static map<string, fmSafety> stringToFmSafetyEnum = {
		{"safe", safe},
		{"unsafe", unsafe}
	};

	static map<string, fmDetectable> stringToFmDetectableEnum = {
		{"yes", yes},
		{"no", no},
		{"impactless", impactless},
		{"outside_scope", outsideScope},
		{"maybe", maybe}
	};

	static map<string, classMultipleFaults> stringToClassMultipleFaultsEnum = {
		{"cm0", cm0},
		{"cm1", cm1},
		{"cm2", cm2},
		{"cm3", cm3},
		{"not_applicable", notApplicable}
	};

	static map<bool, string> boolStr = {
		{false, "False"},
		{true, "True"}
	};
}