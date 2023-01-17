#include "ProcessUnitSD.h"
#include "../../../utils/mt_engine/include/MtRandEngine.h"

using namespace std;
class Supervised {
public:
	Supervised(
		double nominalFuseResultBurn,
		double nominalFuseResultNotBurn,
		bool verboseMode = true);

	double getTestOutput();

	void setTestInput(double input);
	void setTestScenario(TestScenarioType& testScenario);
	void setBasicParams(
		double minNominalFuseResultBurn,
		double maxNominalFuseResultBurn,
		double minNominalFuseResultNotBurn,
		double maxNominalFuseResultNotBurn,
		int seed);
	void setMtEngineRandSeed();
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