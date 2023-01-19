#include "ParamsController.h"

using namespace std;

class FailureController {
public:
	FailureController(vector<Component>& componentsArray, FuseTestScenarioType& testScenario);
	FailureController(vector<Component>& componentsArray, FuseTestScenarioType& testScenario, bool verboseMode);
	void defineNewTestScenario();

	int getNumberOfFailedComponents();
	void setVerboseMode(bool verboseModeValue);

private:
	vector<Component>& componentsArray;
	FuseTestScenarioType& testScenario;

	bool verboseMode;

	int numberOfFailedComponents;
	int singleFailedComponentId;
};