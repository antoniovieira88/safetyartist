#include "include/ComponentTest.h"

void ComponentTest()
{
	int iteration = 0;
	int* iterationPointer = &iteration;
	double iterationEquivalentTime = 12.0;
	mt19937 generator;
	string faultModesDir = "data/SimulationMemory/FailureSpecs_EC3/FaultModes";
	double faultRateDzSys = 4.01333E-6;
	int idDzSys = 18;
	bool verboseMode = false;
	double reliability = NAN;

	vector<unsigned int>
		seedsArray = { 3944864314U,
					3510813216U,
					1451051205U,
					776178934U,
					578210035U,
					2000000000U,
					987654321U,
					1234567890U,
					8457832U,
					49U,
					135748965U,
					977544012U,
					135792468U,
					864207531U,
					908172635U,
					918273645U,
					222333444U,
					555553330U,
					88888888U,
					999999999U,
					22U,
					1123581321U,
					1248163264U,
					128256512U,
					10242048U,
					30915734U,
					5690149U,
					1248844221U,
					963852741U,
					1597532584U };

	vector<int> interationOnFailureArray;
	vector<double> reliabilityArray;


	Component DzSysComponent(
		"DZ_Sys",
		idDzSys,
		faultRateDzSys,
		iterationPointer,
		iterationEquivalentTime,
		generator,
		faultModesDir,
		verboseMode
	);

	for (unsigned int& seed : seedsArray) {
		generator.seed(seed);

		componentOpStatus statusDzSys = noFault;

		while (statusDzSys == noFault) {
			iteration++;
			DzSysComponent.calculateReliability();
			statusDzSys = DzSysComponent.generateNewOperationalState();
		}

		double iterationOnFailure = DzSysComponent.getIterationOnFailure();
		double randNum = DzSysComponent.getRandNumGeneratedInFailure();
		string faultModeName = DzSysComponent.getCurrentFaultModeName();
		int faultModeId = DzSysComponent.getCurrentFaultModeId();
		double reliability = DzSysComponent.getReliability();
		int countBetweenFailures = DzSysComponent.getCountBetweenFailures();

		cout << endl << "seed: " << seed << endl;
		cout << "iterationOnFailure: " << iterationOnFailure << endl;
		cout << "randNumGeneratedInFailure: " << randNum << endl;
		cout << "faultModeName: " << faultModeName << endl;
		cout << "faultModeId: " << faultModeId << endl;
		cout << "reliability: " << reliability << endl;
		cout << "countBetweenFailures: " << countBetweenFailures << endl;

		interationOnFailureArray.push_back(iterationOnFailure);
		reliabilityArray.push_back(reliability);

		DzSysComponent.repair();
		iteration = 0;
	}

	double mttf = (reduce(interationOnFailureArray.begin(), interationOnFailureArray.end(), 0.0) * iterationEquivalentTime) / interationOnFailureArray.size();
	double averageReliability = reduce(reliabilityArray.begin(), reliabilityArray.end(), 0.0) / reliabilityArray.size();


	cout << endl << endl << "Final Results " << endl << endl;
	cout << "mttf: " << mttf << endl;
	cout << "averageReliability: " << averageReliability << endl;
}
