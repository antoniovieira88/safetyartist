#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include "../../src/utils/structs/structs.h"

using namespace std;

class ParamsController {
public:
	ParamsController();
	vector<double> getFailureRateArray();
	vector<int>* getCountBetweenFailuresArray();
	vector<double> getReliabiabilityArray();

private:
	vector<string> componentsArray;
	vector<double> failureRateArray;
	vector<int> countBetweenFailuresArray;
	vector<double> reliabiabilityArray;
	void loadFailureSpecs();
	fstream failureRatesFile;
	int numberOfComponents;
};