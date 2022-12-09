#include "include/Supervisor.h"


Supervisor::Supervisor(): analysisUnit(2), dataHandler(1000), processUnit(analysisUnit, dataHandler, NULL, 0.0, 0.0, 0.0, true)
{}

void Supervisor::attach(Supervised* supervised) {
	processUnit.attach(supervised);
}

void Supervisor::newTest() {
	processUnit.newTest();
}