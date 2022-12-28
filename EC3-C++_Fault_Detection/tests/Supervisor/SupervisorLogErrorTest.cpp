#include "include/SupervisorLogErrorTest.h"

using namespace std;

static string componentStr[] =
{
  "ComponentA",
  "ComponentB",
  "ComponentC",
  "ComponentD"
};

int SupervisorLogErrorTest()
{

	int iteration;
	Supervisor supervisor(
		1000,
		0.1, 0.9,
		0.01, 0.01, 0.01, true);

	Supervised supervised(0.1, 0.9, 1);
	ofstream simulationDataFile;
	string logError;

	cout << "Simulation started" << endl;

	cout << "Supervised attached to supervisor" << endl;
	supervisor.attach(&supervised);

	for (iteration = 1; iteration < 5; iteration++) {

		cout << endl << "Begin of Iteration " << iteration << endl;
		try {
			supervisor.runTest();
		}
		catch (FailureDetectedExcep& error) {
			cout << error.what() << endl;

			logError = error.getLogError();

			simulationDataFile.open("data/SimulationMemory/HistoricalFailureLog.csv", std::ios_base::app);

			simulationDataFile << logError;

			simulationDataFile.close();
		};

		cout << "End of Iteration " << iteration << endl;
		cout << " " << endl;

	}

	cout << "Simulation completed";

	return 0;
}