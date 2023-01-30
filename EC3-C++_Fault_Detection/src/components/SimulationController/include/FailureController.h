#include "ParamsController.h"

using namespace std;

class FailureController {
public:
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario);
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode);
	void defineNewTestScenario();

	int getNumberOfFailedComponents();
	vector<string>& getFailedComponentsNameArray();
	void setVerboseMode(bool verboseModeValue);

private:
	vector<Component>& componentsArray;
	TestScenarioType& testScenario;
	vector<string> failedComponentsNameArray;

	bool verboseMode;

	int numberOfFailedComponents;
	int singleFailedComponentId;
};