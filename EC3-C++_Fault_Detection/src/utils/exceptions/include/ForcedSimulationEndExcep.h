#include <string>
#include "../../structs/structs.h"

using namespace std;

class ForcedSimulationEndExcep : public exception {
private:
	string reason;
	test testName;

public:
	ForcedSimulationEndExcep(string reason, test testName);
	const char* what() const throw();
};