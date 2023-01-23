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

	vector<double> getNominalFuseResults();

	// FuseTest
	void setFuseTestScenario(FuseTestScenarioType& testScenario);
	void setFuseTest(double fuseTest);
	double runFuseTest();

	// KeepPowTest
	void setKeepPowTestScenario(bool fail);
	void setKeepPower(double keepPower);
	double runKeepPowTest();

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