#include <string>
#pragma once

using namespace std;

class SimulatorFailureExcep : public exception {
private:
	string errorMsg;
public:
	SimulatorFailureExcep(string reason, string local);

	const char* what() const throw();
};