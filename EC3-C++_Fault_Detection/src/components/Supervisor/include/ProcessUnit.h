#include <mlpack/core.hpp>
#include "AnalysisUnit.h"
#include "DataHandler.h"
#include "../../Supervised/include/Supervised.h"
#include "../../../utils/structs/structs.h"
#include "../../../utils/exceptions/include/FailureDetectedExcep.h"

class ProcessUnit {
public:
	ProcessUnit(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
		double overallSilhouetteTolerance, double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance);

	ProcessUnit(AnalysisUnit& analysisUnit, DataHandler& dataHandler, Supervised* supervised,
		double overallSilhouetteTolerance, double silhouetteDiffTolerance,
		double numberOfPointsPerClusterDiffTolerance, bool verboseMode);

	~ProcessUnit();

	void attach(Supervised* supervised);
	void newTest();

private:
	AnalysisUnit& analysisUnit;
	DataHandler& dataHandler;
	Supervised* supervised;

	bool verboseMode;
	int iteration;

	double fuseTest, keepPower;
	double overallSilhouetteDecreaseTolerance, silhouetteClustersDecreaseTolerance, imbalanceClustersIncreaseTolerance;
	double silhouetteCluster1Increase, silhouetteCluster2Increase, imbalanceClustersIncrease, overallSilhouetteIncrease;
	faultDiagnosisType detectFailure();

	colvec previousMetrics, newMetrics;

	void initializeDataHandler();

	void provideTestInput(double testInput);
	double receiveTestOutput();
};