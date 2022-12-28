#include "../../../utils/components/include/Component.h"

using namespace std;

class ParamsController {
public:
	ParamsController(
		double simulationStep,
		mt19937& generator,
		vector<Component>& componentsArray,
		string dirFailureSpecs,
		string dirFaultModes);

	ParamsController(
		double simulationStep,
		mt19937& generator,
		vector<Component>& componentsArray,
		string dirFailureSpecs,
		string dirFaultModes,
		bool verboseMode);

	void loadFailureSpecs();
	void setComponentsInitialOperationalState();
	void updateComponentsOperationalStateFile();

	bool isSurpervisedStartingWithFailure();

private:
	int numberOfComponents;

	const string dirFaultModes;
	const string dirFailureSpecs;

	const double simulationStep;

	mt19937& generator;
	vector<Component>& componentsArray;

	bool verboseMode, initialFaults;

};