#include "ProcessUnitSD.h"
#include "../../../utils/mt_engine/include/MtRandEngine.h"

using namespace std;

class Supervised {
public:
	Supervised(
		double nominalFuseResultBurn,
		double nominalFuseResultNotBurn,
		bool verboseMode = true);

	double getFuseTestOutput();
	vector<double> getNominalFuseResults();

	void setFuseTestInput(double input);
	void setKeepPower(double keepPower);
	void setFuseTestScenario(FuseTestScenarioType& fuseTestScenario);
	void setBasicParams(
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