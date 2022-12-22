#include "ParamsController.h"

using namespace std;

class FailureController {
public:
	FailureController(vector<Component>& componentsArray, vector<int>& testScenario);
	FailureController(vector<Component>& componentsArray, vector<int>& testScenario, bool verboseMode);
	void defineNewTestScenario();

	int getNumberOfFailedComponents();

private:
	vector<Component>& componentsArray;
	vector<int>& testScenario;

	bool verboseMode;

	int numberOfFailedComponents;
	int singleFailedComponentId;
};