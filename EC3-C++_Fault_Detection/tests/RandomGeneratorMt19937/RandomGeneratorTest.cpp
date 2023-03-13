#include "include/RandomGeneratorTest.h"

// Test to check the saving of the random generator state whenever a simulation reaches its end
int RandomGeneratorStateTest()
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

/* Test to check the if the random generator test provides adequate uniformity within [0; 1]
 * for reliability decision.
 */
void RandomGeneratorUnityUniformityTest()
{
	// Random number generator
	MtRandEngine generator;

	// Instantiation as an uniform distribution within [0; 1]
	uniform_real_distribution<double> dist{ 0.0, 1.0 };

	/* Counters of random numbers within 0.05-width subintervals
	 * countHistogram[i] comprises the count of random numbers within [i * 0.05; (i+1) * 0.05[.
	 * Exceptions: countHistogram[19] also includes the generation of '1'.
	 *             countHistogram[20] counts exceptions outside [0; 1].
	 */ 
	int randomDistributionCount[21];

	// Auxiliary variable to store a random number
	double randomNumber = 0;

	// Auxiliary counter variable
	int i = 0;

	// String that indicates the address of the file in which the results are written
	string results_file = "tests/RandomGeneratorMt19937/UnityDistributionResults.txt";

	// Output file stream for results_file
	// Opens the output stream by pointing it to the file of the string 'results_file' in 'write' mode
	ofstream out_file(results_file, std::ofstream::out);

	// Initializes random number generator with a random seed
	generator.setRandSeed();

	// Initializes randomDistributionCount with zeroes in all its positions
	for (i = 0; i < 21; i++)
		randomDistributionCount[i] = 0;

	/* Randomly sorts 1G numbers within [0; 1] and stratify them into groups of 0.05 width
	 * to support the generation of a histogram with the actual distribution of the generator.
	 * */
	for (i = 0; i < 1000000000; i++)
	{
		randomNumber = dist(generator);

		if (randomNumber >= 0 && randomNumber < 0.05)
			randomDistributionCount[0]++;

		else if (randomNumber >= 0.05 && randomNumber < 0.10)
			randomDistributionCount[1]++;

		else if (randomNumber >= 0.10 && randomNumber < 0.15)
			randomDistributionCount[2]++;

		else if (randomNumber >= 0.15 && randomNumber < 0.20)
			randomDistributionCount[3]++;

		else if (randomNumber >= 0.20 && randomNumber < 0.25)
			randomDistributionCount[4]++;

		else if (randomNumber >= 0.25 && randomNumber < 0.30)
			randomDistributionCount[5]++;

		else if (randomNumber >= 0.30 && randomNumber < 0.35)
			randomDistributionCount[6]++;

		else if (randomNumber >= 0.35 && randomNumber < 0.40)
			randomDistributionCount[7]++;

		else if (randomNumber >= 0.40 && randomNumber < 0.45)
			randomDistributionCount[8]++;

		else if (randomNumber >= 0.45 && randomNumber < 0.50)
			randomDistributionCount[9]++;

		else if (randomNumber >= 0.50 && randomNumber < 0.55)
			randomDistributionCount[10]++;

		else if (randomNumber >= 0.55 && randomNumber < 0.60)
			randomDistributionCount[11]++;

		else if (randomNumber >= 0.60 && randomNumber < 0.65)
			randomDistributionCount[12]++;

		else if (randomNumber >= 0.65 && randomNumber < 0.70)
			randomDistributionCount[13]++;

		else if (randomNumber >= 0.70 && randomNumber < 0.75)
			randomDistributionCount[14]++;

		else if (randomNumber >= 0.75 && randomNumber < 0.80)
			randomDistributionCount[15]++;

		else if (randomNumber >= 0.80 && randomNumber < 0.85)
			randomDistributionCount[16]++;

		else if (randomNumber >= 0.85 && randomNumber < 0.90)
			randomDistributionCount[17]++;

		else if (randomNumber >= 0.90 && randomNumber < 0.95)
			randomDistributionCount[18]++;

		else if (randomNumber >= 0.95 && randomNumber <= 1.00)
			randomDistributionCount[19]++;

		// Exception: Invalid numbers outside [0; 1]
		else
			randomDistributionCount[20]++;

		// Prints message on the screen each time 10M numbers have been generated
		if (i % 10000000 == 0)
			cout << "Number of random numbers already generated: " << i << " out of 1000000000 ("
			     << (i / 10000000) << "% finished)" << endl;

	}

	/* Prints the contents of randomDistributionCount[] into the output file 'out_file'
	 * if the latter has been succesfully opened. */
	if (out_file.is_open())
	{
		out_file << "Numbers within [0.00; 0.05[: " << randomDistributionCount[0] << endl;
		out_file << "Numbers within [0.05; 0.10[: " << randomDistributionCount[1] << endl;
		out_file << "Numbers within [0.10; 0.15[: " << randomDistributionCount[2] << endl;
		out_file << "Numbers within [0.15; 0.20[: " << randomDistributionCount[3] << endl;
		out_file << "Numbers within [0.20; 0.25[: " << randomDistributionCount[4] << endl;
		out_file << "Numbers within [0.25; 0.30[: " << randomDistributionCount[5] << endl;
		out_file << "Numbers within [0.30; 0.35[: " << randomDistributionCount[6] << endl;
		out_file << "Numbers within [0.35; 0.40[: " << randomDistributionCount[7] << endl;
		out_file << "Numbers within [0.40; 0.45[: " << randomDistributionCount[8] << endl;
		out_file << "Numbers within [0.45; 0.50[: " << randomDistributionCount[9] << endl;
		out_file << "Numbers within [0.50; 0.55[: " << randomDistributionCount[10] << endl;
		out_file << "Numbers within [0.55; 0.60[: " << randomDistributionCount[11] << endl;
		out_file << "Numbers within [0.60; 0.65[: " << randomDistributionCount[12] << endl;
		out_file << "Numbers within [0.65; 0.70[: " << randomDistributionCount[13] << endl;
		out_file << "Numbers within [0.70; 0.75[: " << randomDistributionCount[14] << endl;
		out_file << "Numbers within [0.75; 0.80[: " << randomDistributionCount[15] << endl;
		out_file << "Numbers within [0.80; 0.85[: " << randomDistributionCount[16] << endl;
		out_file << "Numbers within [0.85; 0.90[: " << randomDistributionCount[17] << endl;
		out_file << "Numbers within [0.90; 0.95[: " << randomDistributionCount[18] << endl;
		out_file << "Numbers within [0.95; 1.00[: " << randomDistributionCount[19] << endl;
		out_file << "Numbers outside [0.00; 1.00]: " << randomDistributionCount[20];

	}

	// Closes out_file
	out_file.close();
}
