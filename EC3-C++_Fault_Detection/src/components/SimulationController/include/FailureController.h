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
	void defineTestScenarioForSpecificFaultMode(FaultModeType* faultModePointer);

	int getNumberOfFailedComponents();
	unordered_set<string>& getFailedComponentsNameSet();
	void setVerboseMode(bool verboseModeValue);

private:
	vector<Component>& componentsArray;

	TestScenarioType& testScenario;
	unordered_set<string> failedComponentsNameSet;
	vector<FaultModeType*> failuresWithImpactArray;

	bool verboseMode;

	bool failureScenarioKeepPowTstLocked;
	bool failureScenarioFuseTstLocked;

	int numberOfFailedComponents, maxNumberOfFailuresWithImpact;
	int singleFailedComponentId;

	fmDetectable getFmDetectableForNextText(FaultModeType* pointerForFaultMode, test nextTestToBePerfomed);

	void updateTestScenario(FaultModeType* pointerForNewFaultMode, test nextTestToBePerfomed);
	void resolveFailureScenarioForMultipleFailuresWithImpact(FaultModeType* pointerForNewFaultMode);

	void resolveFuseFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode);
	void resolveKeepPowFailureScenario(FaultModeType* pointerForLastFaultMode, FaultModeType* pointerForNewFaultMode);
};