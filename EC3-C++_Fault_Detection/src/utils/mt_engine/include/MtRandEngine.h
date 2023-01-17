#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "../../exceptions/include/AbortSimulationOpExcep.h"

using namespace std;
class MtRandEngine : public mt19937 {
public:

	using mt19937::mt19937;

	void loadState(bool verboseMode);
	void saveState(bool verboseMode);
	void setFileDir(string srcFileDir);
	void setRandSeed();

private:
	bool verboseMode;
	string srcFileDir;

};