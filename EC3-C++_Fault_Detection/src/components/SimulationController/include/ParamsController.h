#include "../../../utils/components/include/Component.h"
#include "../../../utils/exceptions/include/AbortSimulationOpExcep.h"
#include "../../../utils/exceptions/include/SimulatorFailureExcep.h"
#include "../../../utils/exceptions/include/ForcedSimulationEndExcep.h"

using namespace std;

class ParamsController {
public:
	ParamsController(
		string& simulationName,
		SimulationSpecificParamsType& simulationSpecificParams,
		mt19937& generator,
		vector<Component>& componentsArray,
		int*& iterationPointer,
		string simulationMemoryDir = "data/SimulationMemory",
		bool verboseMode = true
	);

	void loadFailureSpecs();
	int setComponentsInitialOperationalState();
	void updateComponentsOperationalStateFile();

	bool isSurpervisedStartingWithFailure();

	void loadSimulationSpecificParams();

	void setVerboseMode(bool verboseModeValue);

private:
	int numberOfComponents;

	const string faultModesDir;
	const string failureSpecsDir;
	const string simulationsDir;

	string& simulationName;
	int*& iterationPointer;
	SimulationSpecificParamsType& simulationSpecificParams;

	mt19937& generator;
	vector<Component>& componentsArray;

	bool verboseMode, initialFaults;

};