// change the directory to run different tests
#include "../../tests/SimulationController/include/SimulationControllerTest1.h"

using namespace std;

int main()
{
	int dumm;
	// function under test
	try {
		SimulationControllerTest1();
		/*dumm = KMeansTest1();
		dumm = KMeansTest2();
		dumm = KMeansTest3();
		dumm = KMeansTest4();*/
	}
	catch (exception& error) {
		cout << endl << endl << error.what() << endl;
		cout << "Simulator run cancelled" << endl;
	}

	cout << endl << endl << "Press any button to close the terminal" << endl;
	cin >> dumm;

	return 0;
}