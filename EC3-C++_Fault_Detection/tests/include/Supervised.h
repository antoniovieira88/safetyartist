#include "CorrectOutputGenerator.h"

class Supervised {
	public:
		Supervised();
		void setTestInput(double input);
		void setTestScenario();
		double getTestOutput();

	private:
		double testInput, testOutput, stdDeviationTest;
		CorrectOutputGenerator correctOutputGenerator;
		
};