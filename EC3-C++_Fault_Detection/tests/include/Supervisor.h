#include "ProcessUnit.h"
#include "AnalysisUnit.h"
#include "DataHandler.h"

class Supervisor
{
public:
	Supervisor();
	void attach(Supervised *supervised);
	void newTest();

private:
	ProcessUnit processUnit;
	AnalysisUnit analysisUnit;
	DataHandler dataHandler;
};