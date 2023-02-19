#include "ParamsController.h"
#include<unordered_set>

using namespace std;

class FailureController {
public:
	FailureController(
		vector<Component>& componentsArray,
		TestScenarioType& testScenario,
		bool verboseMode = true);

	void defineNewRandomTestScenario(test nextTestToBePerfomed);
	void defineTestScenarioWithoutFailure();
	void defineTestScenarioForSpecificSingleFaultMode(FaultModeType* faultModePointer);
	void addNewFailureToTestScenario(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed);

	int getNumberOfFailedComponents();
	void setVerboseMode(bool verboseModeValue);

	void reset();

private:
	vector<Component>& componentsArray;

	TestScenarioType& testScenario;
	unordered_set<string> failedComponentsNameSet;
	vector<FaultModeType*> failuresWithImpactArray;

	bool verboseMode;

	bool failureScenarioKeepPowTstLocked, failureScenarioFuseTstLocked;

	int numberOfFailedComponents, maxNumberOfFailuresWithImpact;

	void updateTestScenarioFlags(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed);

	fmDetectable getFmDetectableForNextText(FaultModeType* pointerForFaultMode, test nextTestToBePerfomed);

	void resolveFailureScenarioForMultipleFailuresWithImpact(FaultModeType* pointerForNewFaultMode);

	void resolveFuseFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode);
	void resolveKeepPowFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode);
};