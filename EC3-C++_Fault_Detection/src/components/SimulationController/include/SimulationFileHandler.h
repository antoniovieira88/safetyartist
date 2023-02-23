#include "../../../utils/filesys_handler/include/FileSysHandler.h"

using namespace std;
class SimulationFileHandler {
public:
	SimulationFileHandler(string dataMemoryDir, string simulationMemoryDir);

	void createSimulationFiles(string simulationName);
	bool searchForSimulationDirectories(string simulationName);
	void exportJsonFaultModeAnalysisArray(vector<FaultModeAnalysisResultType>& faultModeDataArray, string destinyFilePath);
	void createLogAndStatusCSVFiles(string simulationName);
	void createDataMemoryCSVFiles(string simulationName);
	void exportFailureEventsHistoryJson(vector<FailureEventType>& failureEventsArray, int iteration, string simulationName);
private:

	string dataMemoryDir, simulationMemoryDir, simulationsDir;
};