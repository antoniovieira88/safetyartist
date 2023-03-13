#include <string>

using namespace std;

class IncompatibleIterationExcep : public exception {
private:
	string errorMsg;

public:
	IncompatibleIterationExcep(int iterationMetrics, int iterationData);
	const char* what() const throw();
};