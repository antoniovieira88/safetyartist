#include <string>
#pragma once

using namespace std;

class AbortSimulationOpExcep : public exception {
private:
	string errorMsg;
public:
	AbortSimulationOpExcep(string reason);

	const char* what() const throw();
};