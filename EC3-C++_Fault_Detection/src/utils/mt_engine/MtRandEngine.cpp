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

void MtRandEngine::setRandSeed()
{
	this->seed(time(nullptr));
}