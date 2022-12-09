// Includes all relevant components of mlpack.
#include <mlpack/core.hpp>
#include "./include/Supervisor.h"
#include "../src/utils/exceptions/include/FailureDetectedExcep.h"
#include <string>
#include <fstream>

using namespace std;

static string componentStr[] =
{
  "ComponentA",
  "ComponentB",
  "ComponentC",
  "ComponentD",
  "ComponentE",
  "ComponentF"
};

int main()
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
			supervisor.newTest();
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