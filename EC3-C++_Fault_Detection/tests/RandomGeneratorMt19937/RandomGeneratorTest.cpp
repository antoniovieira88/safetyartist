#include "include/RandomGeneratorTest.h"

int RandomGeneratorTest()
{
	MtRandEngine generator;
	uniform_int_distribution<int> dist(0, 1000);
	/*const int seed = 7;*/
	string state_fname = "tests/RandomGeneratorMt19937/state";
	generator.setFileDir(state_fname);
	cout << "Full sequence starting from seed: " << "random seed" << endl;
	/*generator.seed(seed)*/;
	generator.setRandSeed();
	generator.saveState(true);
	for (int i = 0; i < 12; i++) {
		cout << dist(generator) << ", ";
	}
	cout << endl << endl << endl << endl;

	cout << "Stepped sequence starting from seed: " << "random seed" << endl << endl;
	for (int i = 0; i < 3; i++) {
		generator.loadState(true);
		cout << "Sequence" << i << ": ";
		for (int j = 0; j < 4; j++) {
			cout << dist(generator) << ", ";
		}
		generator.saveState(true);
		cout << endl;
	}

	return 0;
}
