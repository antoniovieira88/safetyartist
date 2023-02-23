// change the directory to run different tests
#include "../../tests/SimulationController/include/SimulationControllerTest1.h"
//#include "../../tests/RandomGeneratorMt19937/include/RandomGeneratorTest.h"

using namespace std;

int main()
{
	int dumm;
	// function under test
	try {
		SimulationControllerTest1();
		/*RandomGeneratorUnityUniformityTest();*/
	}
	catch (exception& error) {
		cout << endl << endl << error.what() << endl;
		cout << "Simulator run canceled" << endl;
	}

	cout << endl << endl << "Press any button to close the terminal";

	getchar();

	return 0;
}