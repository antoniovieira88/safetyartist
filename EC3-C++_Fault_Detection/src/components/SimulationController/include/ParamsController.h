#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../../../utils/components/include/Component.h"

using namespace std;

class ParamsController {
public:
	ParamsController(double simulationStep, mt19937& generator);

	vector<Component>& getComponentsArray();

private:
	vector<Component> componentsArray;
	void loadFailureSpecs();
	fstream faultRatesFile;
	int numberOfComponents;

	const double simulationStep;

	mt19937& generator;

};