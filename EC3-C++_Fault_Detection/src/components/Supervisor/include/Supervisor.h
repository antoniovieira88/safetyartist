#include "ProcessUnit.h"

class Supervisor
{
public:
	Supervisor();
	void attach(Supervised *supervised);
	void newTest();

private:
	AnalysisUnit analysisUnit;
	DataHandler dataHandler;
	ProcessUnit processUnit;
};