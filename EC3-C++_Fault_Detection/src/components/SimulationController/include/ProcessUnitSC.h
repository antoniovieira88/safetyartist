#include "FailureController.h"
#include "../../Supervisor/include/Supervisor.h"

using namespace std;

class ProcessUnitSC {
public:
	ProcessUnitSC(
		FailureController& failureController,
		ParamsController& paramsController,
		vector<int>& testScenario
	);

	void attach(Supervisor* supervisorPointer, Supervised* supervisedPointer);

	void runSimulation(int duration);
private:
	FailureController& failureController;
	ParamsController& paramsController;

	vector<int>& testScenario;

	Supervisor* supervisorPointer;
	Supervised* supervisedPointer;

	int* iterationPointer;

	void initializeParamsController();

};

