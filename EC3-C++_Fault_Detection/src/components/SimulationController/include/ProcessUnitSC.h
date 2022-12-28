#include "FailureController.h"
#include "../../Supervisor/include/Supervisor.h"

using namespace std;

class ProcessUnitSC {
public:
	ProcessUnitSC(
		FailureController& failureController,
		ParamsController& paramsController,
		TestScenarioType& testScenario,
		vector<Component>& componentsArray,
		double simulationStep,
		bool verboseMode
	);

	~ProcessUnitSC();

	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);

	void runSimulation(int duration);
private:
	FailureController& failureController;
	ParamsController& paramsController;

	TestScenarioType& testScenario;

	vector<Component>& componentsArray;

	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;

	int* iterationPointer;
	bool verboseMode;
	double simulationStep;

	void initializeParamsController();

	void resetComponentsOperationalStates();
	void resetSupervisor();
	void initialUserOptions();
};

