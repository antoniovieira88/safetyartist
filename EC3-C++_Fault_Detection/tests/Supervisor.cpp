#include "include/Supervisor.h"


Supervisor::Supervisor()
{
	analysisUnit = AnalysisUnit(2);
	dataHandler = DataHandler(1000);

	processUnit = ProcessUnit(analysisUnit, dataHandler, NULL, 0.0, 0.0, 0.0);
}


void Supervisor::attach(Supervised* supervised) {
	processUnit.attach(supervised);
}

void Supervisor::newTest() {
	processUnit.newTest();
}