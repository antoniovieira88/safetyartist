#include <string>
#include <fstream>

using namespace std;
int SupervisorTest1()
{
	int iteration;
	Supervisor supervisor;
	Supervised supervised;
	ofstream simulationDataFile;
	string logError;

	cout << "Simulation started";

	cout << "Supervised attached to supervisor" << endl;
	supervisor.attach(&supervised);

	for (iteration = 1; iteration < 5; iteration++) {

		cout << "Begin of Iteration " << iteration << endl;
		try {
			supervisor.runTest();
		}
		catch (FailureDetectedExcep& error) {
			cout << error.what() << endl;

			logError = error.getLogError();

			simulationDataFile.open("data/SimulationMemory/HistoricalCatchedFailureMetricsLog.csv", std::ios_base::app);

			simulationDataFile << logError;

			simulationDataFile.close();
		};

		cout << "End of Iteration " << iteration << endl;
		cout << " " << endl;

	}

	cout << "Simulation completed";

	return 0;
}