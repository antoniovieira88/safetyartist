#include "include/MtRandEngine.h"

void MtRandEngine::loadState(bool verboseMode)
{
	ifstream inputFileStream;
	inputFileStream.open(srcFileDir.c_str(), ios::binary);
	if (inputFileStream.fail()) {
		throw AbortSimulationOpExcep("File '" + srcFileDir + "' could not be opened\n");
	}
	inputFileStream >> (*this);
	if (verboseMode) cout << endl << "MtEngine state loaded from " << srcFileDir << endl;
}

void MtRandEngine::saveState(bool verboseMode)
{
	ofstream ouputFileStream;
	ouputFileStream.open(srcFileDir.c_str(), ios::out);
	ouputFileStream << (*this);
	ouputFileStream.close();
	if (verboseMode) cout << endl << "MtEngine state saved in " << srcFileDir << endl;
}

void MtRandEngine::setFileDir(string srcFileDir)
{
	MtRandEngine::srcFileDir = srcFileDir;
}

// the first number of the pseudo-random number sequence corresponds
// to the initial seed
unsigned int MtRandEngine::setRandSeed()
{
	// it is possible to pass 'to the seed' method an seed sequence object
	// like a 'time' object. Internally, the mt19937 object converts it to an
	// unsigned integer
	this->seed(time(nullptr));
	return (*this)();
}