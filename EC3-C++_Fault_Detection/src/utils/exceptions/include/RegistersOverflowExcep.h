#include <string>

using namespace std;

class RegistersOverflowExcep : public exception {
private:
	string errorMsg;

public:
	RegistersOverflowExcep(int iterationMetrics, int iterationData);
	const char* what() const throw();
};