#include <mlpack/core.hpp>
#include "AnalysisUnit.h"
#include "DataHandler.h"
#include "../../Supervised/include/Supervised.h"
#include "../../../utils/structs/structs.h"
#include "../../../utils/exceptions/include/FailureDetectedExcep.h"

class ProcessUnitSR {
public:
	ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervisedPointer,
		double overallSilhouetteTolerance, double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance);

	ProcessUnitSR(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
		double overallSilhouetteTolerance, double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance, bool verboseMode);

	~ProcessUnitSR();

	void attach(Supervised* supervisedPointer);
	void runTest();
	void reset();
	void initializeDataHandler();

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

	void provideTestInput(double testInput);
	double receiveTestOutput();
};