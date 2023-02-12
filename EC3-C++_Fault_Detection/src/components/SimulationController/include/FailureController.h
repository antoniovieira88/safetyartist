#include "ParamsController.h"
#include<unordered_set>

using namespace std;

class FailureController {
public:
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario);
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode);

	void defineNewRandomTestScenario();
	void defineTestScenarioWithoutFailure();
	void defineTestScenarioForSpecificFailure(int componentId, int faultModeId, FailureScenarioType* failureScenarioPointer);

	int getNumberOfFailedComponents();
	unordered_set<string>& getFailedComponentsNameSet();
	void setVerboseMode(bool verboseModeValue);

private:
	vector<Component>& componentsArray;
	TestScenarioType& testScenario;
	unordered_set<string> failedComponentsNameSet;

	bool verboseMode;

	int numberOfFailedComponents;
	int singleFailedComponentId;
};