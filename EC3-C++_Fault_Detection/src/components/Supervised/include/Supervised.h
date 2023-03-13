#include "ProcessUnitSD.h"
#include "../../../utils/mt_engine/include/MtRandEngine.h"

using namespace std;

class Supervised {
public:
	Supervised(
		double uncertaintyRangeInput = 0.000001,
		bool verboseMode = true);

	Supervised(
		double nominalFuseResultBurn,
		double nominalFuseResultNotBurn,
		double uncertaintyRangeInput = 0.000001,
		bool verboseMode = true);

	void setTestScenario(TestScenarioType& testScenario);

	// FuseTest
	void setFuseTest(double fuseTest);
	double getFuseResult();
	vector<double> getNominalFuseResults();

	// KeepPowTest
	void setKeepPower(int keepPower);
	int getKeepPowReadback();

	// here are set the basic params which are specified in 'simulationsParams.csv'.
	// since the values of keepPowerReadback are the same for all simulations, 
	// there are not taken into account in this method. we can consider the params
	// belows as constants for a given simulation
	void setBasicParams(
		double nominalValueFuseResultBurn,
		double nominalValueFuseResultNotBurn,
		double minNominalFuseResultBurn,
		double maxNominalFuseResultBurn,
		double minNominalFuseResultNotBurn,
		double maxNominalFuseResultNotBurn,
		double maxStdDeviation,
		unsigned int seed);

	void setMtEngineSrcFile(string srcFileDir);

	void loadMtEngineState();
	void saveMtEngineState();

private:
	MtRandEngine generator;

	bool verboseMode;

	CorrectOutputGenerator correctOutputGenerator;
	FailedOutputGenerator failedOutputGenerator;
	ProcessUnitSD processUnit;
};