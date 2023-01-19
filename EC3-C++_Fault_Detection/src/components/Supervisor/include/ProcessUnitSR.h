#include <mlpack/core.hpp>
#include <vector>
#include "AnalysisUnit.h"
#include "DataHandler.h"
#include "../../Supervised/include/Supervised.h"
#include "../../../utils/structs/structs.h"
#include "../../../utils/exceptions/include/FailureDetectedExcep.h"

using namespace std;

class ProcessUnitSR {
public:
	ProcessUnitSR(
		AnalysisUnit& analysisUnit,
		DataHandler& dataHandler,
		Supervised* supervised,
		bool verboseMode = true);

	ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
		double overallSilhouetteTolerance, double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance, bool verboseMode);

	~ProcessUnitSR();

	void attach(Supervised* supervisedPointer);
	void runTest();
	void reset();
	void getReadyForNextSimulationCycle();
	void initializeDataHandler(string simulationName);

	void setVerboseMode(bool verboseModeValue);
	void setBasicParams(
		double overallSilhouetteToleranceValue,
		double silhouetteDiffToleranceValue,
		double numberOfPointsPerClusterDiffToleranceValue);

private:
	AnalysisUnit& analysisUnit;
	DataHandler& dataHandler;
	Supervised* supervisedPointer;

	bool verboseMode;
	int* iterationPointer;

	double fuseTest, keepPower;
	double overallSilhouetteDecreaseTolerance, silhouetteClustersDecreaseTolerance, imbalanceClustersIncreaseTolerance;
	faultDiagnosisType detectFailure();

	colvec previousMetrics, newMetrics;

	void provideFuseTestInput(double testInput);
	void setKeepPower(double keepPower);
	double receiveFuseTestOutput();
};