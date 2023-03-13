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
	void exportFailureEventsHistoryJson(vector<FailureEventType>& failureEventsArray, string filename, string simulationName);
	void exportFailureEventsHistoryJson(vector<FailureEventType>& failureEventsArray, string destinyFilePath);
	string createLogFileForComponentAvaliation(string componentName, string faultModesAvaliationsDir);
	string createFaultModesAvaliationDir(string simulationName);
	void resetCSVFiles(string simulationName);
	void defineSimulationParamsFile(SimulationSpecificParamsType simulationParams, string simulationName);
	void createMultiFailureOutputLogCSVFiles(string outputLogBaseDir, string testName);
private:

	string dataMemoryDir, simulationMemoryDir, simulationsDir;
};