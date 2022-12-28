#include "ParamsController.h"

using namespace std;

class FailureController {
public:
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario);
	FailureController(vector<Component>& componentsArray, TestScenarioType& testScenario, bool verboseMode);
	void defineNewTestScenario();

	int getNumberOfFailedComponents();

private:
	vector<Component>& componentsArray;
	TestScenarioType& testScenario;

	bool verboseMode;

	int numberOfFailedComponents;
	int singleFailedComponentId;
};