# Safety ArtISt-specific module
# Objective: Provide infrastructure for the safety assurance of the experiments by Kozal and Ksieniewicz

from dataset_utils.load_data import *

from keras.utils.np_utils import to_categorical

""" Function load_whole_dataset_safety

- Inputs: None.

- Outputs: Two vectors: np.vstack([trainX, testX]) corresponding to the list of inputs from the "mitbih_train_sa.csv"
           and "mitbih_test_sa.csv" files, and np.vstack([trainY, testY]) corresponding to the list of outputs
           from the "mitbih_train_sa.csv" and "mitbih_test_sa.csv" files.

- Summary: Reads the input files "mitbih_train_sa.csv" and "mitbih_test_sa.csv", which include safety-related data to
           the original "mitbih_train.csv" and "mitbih_test.csv" to support Safety ArtISt's steps 5 and 6, and merges all input
           data to np.vstack([trainX, testX]), and all output data to np.vstack([trainY, testY]).
           Based on the original 'load_whole_dataset' function created by Kozal and Ksieniewicz.
""" 
def load_whole_dataset_safety():
    trainX, trainY = load_file('dataset/mitbih_train_sa.csv')
    testX, testY = load_file('dataset/mitbih_test_sa.csv')
    return np.vstack([trainX, testX]), np.vstack([trainY, testY])

""" Function adds_ad_noise

- Inputs: x: Vector of ECG samples.

- Outputs: x_noise: Input 'x' including simulated quantization noise from the analog-to-digital converter
                    used in the digitization of the ECG heartbeats. Given a 11-bit AD converter has been used,
                    the quantization error is of either -(1/2048) or +(1/2048), hard-limited to 0 and 1. 

- Summary: For each ECG sample of 'x', corresponding to its columns 0 up to 186, adds a random quantization noise
           of either -(1/2048) or +(1/2048), limiting the sample to 0 or 1 if the quantization noise leads the sample
           to be outside this range. All other columns, related to the ECG ID, length and corner case flags are left
           unchanged. The processing result is retrieved on 'x_noise'.  
""" 
def adds_ad_noise(x):

    # Copies 'x' on 'x_noise'
    x_noise = np.copy(x)

    # Randomly initializes random number generator seed
    np.random.seed(None)
    
    # Gets the length (number of lines) of "x". "columns_x" and "arrayList_x" are declared
    # just to allow reading "lines_x" through "shape" and are unused at the rest of the function.
    lines_x, columns_x, arrayList_x = x.shape

    # Adds positive or negative quantization noise to each of the valid samples of 'x'
    for i in range (0, lines_x):

        # For each line, adds quantization noise up to the last valid sample of the heartbeat
        # Since x[188] has the number of samples per heartbeat, the last valid column is 'x[i][188] - 1'
        num_samples = int(x[i][188])
        for j in range (0, num_samples - 1):

            # Generates a random number within [0; 1[. If the number is smaller than 0.5, adds
            # the quantization error -(1/2048); otherwise, adds the quantization error +(1/2048).
            random_number = np.random.random()

            if (random_number < 0.5):
                quantization_error = -(1/2048)

            else:
                quantization_error = (1/2048)

            # Adds 'random_number' to the current sample of 'x_noise'
            x_noise[i][j] =  x_noise[i][j] + quantization_error

            # Checks for overflow or underflow of the sample and keeps it within [0; 1]
            if (x_noise[i][j] < 0):
                x_noise[i][j] = 0
            
            elif (x_noise[i][j] > 1):
                x_noise[i][j] = 1

    # Returns x_noise
    return x_noise

""" Function filterSafetyData

- Inputs: Two vectors, named "x_train" and "x_test", which include input data and safety-related data for
          the Safety ArtISt's method activities and subactivities.

- Outputs: Two vectors, named "x_train_only" and "x_test_only", which only include the first 187 actual data columns
           of the corresponding inputs;
           Two vectors, named "x_train_safety_only" and "x_test_safety_only", which only include the last 22
           safety-critical columns of the corresponding inputs.

- Summary: Since the input vectors "x_train" and "x_test" include 209 columns, with the first 187 ones effectively
           corresponding to input data for training and testing the AI models, and the last 22 ones with supporting
           safety-critical data for Safety ArtISt's steps 5 and 6 activities and subactivities, the function aims to
           split these groups of columns into two variables, in such a way that the only the input data are available
           for the AI models (in one group of outputs) and that the remaining safety-critical data are still traceable
           to their corresponding inputs (in the other group of outputs).
           Hence, this function shall be called only after "x_train" and "x_test" have been subject to the pre-processing
           involving fold shuffling and oversampling/undersampling.
""" 
def filterSafetyData (x_train, x_test):
    x_train_only = x_train[:, :-22]
    x_train_safety_only = x_train[:, -22:]
    x_test_only = x_test[:, :-22]
    x_test_safety_only = x_test[:, -22:]
    return x_train_only, x_test_only, x_train_safety_only, x_test_safety_only

""" Function filterCornerCases01

- Inputs: One vector, named "x", which include input data and safety-related data for the Safety ArtISt's method
          activities and subactivities, and one vector, named "y", with the corresponding heartbeat categories of "x".

- Outputs: Sixty vectors:
           a) "x_cc01_data", "x_cc01_safety and "y_cc01", which only include the records of heartbeats which
           consist on corner cases of category 0 heartbeats that might be potentially mistook for category 1 heartbeats.
           b) "x_cc10_data", "x_cc10_safety and "y_cc10", which only include the records of heartbeats which
           consist on corner cases of category 1 heartbeats that might be potentially mistook for category 0 heartbeats.
           c) "x_cc02_data", "x_cc02_safety and "y_cc02", which only include the records of heartbeats which
           consist on corner cases of category 0 heartbeats that might be potentially mistook for category 2 heartbeats.
           d) "x_cc20_data", "x_cc20_safety and "y_cc20", which only include the records of heartbeats which
           consist on corner cases of category 2 heartbeats that might be potentially mistook for category 0 heartbeats.
           e) "x_cc03_data", "x_cc03_safety and "y_cc03", which only include the records of heartbeats which
           consist on corner cases of category 0 heartbeats that might be potentially mistook for category 3 heartbeats.
           f) "x_cc30_data", "x_cc30_safety and "y_cc30", which only include the records of heartbeats which
           consist on corner cases of category 3 heartbeats that might be potentially mistook for category 0 heartbeats.
           g) "x_cc04_data", "x_cc04_safety and "y_cc04", which only include the records of heartbeats which
           consist on corner cases of category 0 heartbeats that might be potentially mistook for category 4 heartbeats.
           h) "x_cc40_data", "x_cc40_safety and "y_cc40", which only include the records of heartbeats which
           consist on corner cases of category 4 heartbeats that might be potentially mistook for category 0 heartbeats.
           i) "x_cc12_data", "x_cc12_safety and "y_cc12", which only include the records of heartbeats which
           consist on corner cases of category 1 heartbeats that might be potentially mistook for category 2 heartbeats.
           j) "x_cc21_data", "x_cc21_safety and "y_cc21", which only include the records of heartbeats which
           consist on corner cases of category 2 heartbeats that might be potentially mistook for category 1 heartbeats.
           k) "x_cc13_data", "x_cc13_safety and "y_cc13", which only include the records of heartbeats which
           consist on corner cases of category 1 heartbeats that might be potentially mistook for category 3 heartbeats.
           l) "x_cc31_data", "x_cc31_safety and "y_cc31", which only include the records of heartbeats which
           consist on corner cases of category 3 heartbeats that might be potentially mistook for category 1 heartbeats.
           m) "x_cc14_data", "x_cc14_safety and "y_cc14", which only include the records of heartbeats which
           consist on corner cases of category 1 heartbeats that might be potentially mistook for category 4 heartbeats.
           n) "x_cc41_data", "x_cc41_safety and "y_cc41", which only include the records of heartbeats which
           consist on corner cases of category 4 heartbeats that might be potentially mistook for category 1 heartbeats.
           o) "x_cc23_data", "x_cc23_safety and "y_cc23", which only include the records of heartbeats which
           consist on corner cases of category 2 heartbeats that might be potentially mistook for category 3 heartbeats.
           p) "x_cc32_data", "x_cc32_safety and "y_cc32", which only include the records of heartbeats which
           consist on corner cases of category 3 heartbeats that might be potentially mistook for category 2 heartbeats.
           q) "x_cc24_data", "x_cc24_safety and "y_cc24", which only include the records of heartbeats which
           consist on corner cases of category 2 heartbeats that might be potentially mistook for category 4 heartbeats.
           r) "x_cc42_data", "x_cc42_safety and "y_cc42", which only include the records of heartbeats which
           consist on corner cases of category 4 heartbeats that might be potentially mistook for category 2 heartbeats.
           s) "x_cc34_data", "x_cc34_safety and "y_cc34", which only include the records of heartbeats which
           consist on corner cases of category 3 heartbeats that might be potentially mistook for category 4 heartbeats.
           t) "x_cc43_data", "x_cc43_safety and "y_cc43", which only include the records of heartbeats which
           consist on corner cases of category 4 heartbeats that might be potentially mistook for category 3 heartbeats.

- Summary: Since the input vector "x" includes 209 columns, with the first 187 ones effectively corresponding to input data
           and the last 22 ones with supporting safety-critical data for Safety ArtISt's steps 5 and 6 activities and subactivities,
           the function aims to check the flags of "x" indicating each of the aforementioned corner cases, respectively available
           from the 190th up to the 209th column of "x", and only placing the "x" lines in which this flag equals to '1' on the
           corner case group corresponding outputs (as per the previous list of items). "x_ccNN_data" outputs include the 187 data columns
           of "x", whereas "x_ccNN_safety" comprises the remaining columns.
           Finally, "y_ccNN" shall be equal to the original hearbeat classification for all scenarios. This is made sure by comparing
           the corresponding line of "y" to the expected category.
""" 
def filterCornerCases (x, y):
    
    # Initialization: Makes all output vectors "x_ccNN_data", "x_ccNN_safety" and "y_ccNN" equal to empty lists
    x_cc01_data = []
    x_cc01_safety = []
    y_cc01 = []
    x_cc10_data = []
    x_cc10_safety = []
    y_cc10 = []
    x_cc02_data = []
    x_cc02_safety = []
    y_cc02 = []
    x_cc20_data = []
    x_cc20_safety = []
    y_cc20 = []
    x_cc03_data = []
    x_cc03_safety = []
    y_cc03 = []
    x_cc30_data = []
    x_cc30_safety = []
    y_cc30 = []
    x_cc04_data = []
    x_cc04_safety = []
    y_cc04 = []
    x_cc40_data = []
    x_cc40_safety = []
    y_cc40 = []
    x_cc12_data = []
    x_cc12_safety = []
    y_cc12 = []
    x_cc21_data = []
    x_cc21_safety = []
    y_cc21 = []
    x_cc13_data = []
    x_cc13_safety = []
    y_cc13 = []
    x_cc31_data = []
    x_cc31_safety = []
    y_cc31 = []
    x_cc14_data = []
    x_cc14_safety = []
    y_cc14 = []
    x_cc41_data = []
    x_cc41_safety = []
    y_cc41 = []
    x_cc23_data = []
    x_cc23_safety = []
    y_cc23 = []
    x_cc32_data = []
    x_cc32_safety = []
    y_cc32 = []
    x_cc24_data = []
    x_cc24_safety = []
    y_cc24 = []
    x_cc42_data = []
    x_cc42_safety = []
    y_cc42 = []
    x_cc34_data = []
    x_cc34_safety = []
    y_cc34 = []
    x_cc43_data = []
    x_cc43_safety = []
    y_cc43 = []

    # Gets the length (number of lines) of "x" and "y". "columns_x", "columns_y" and "arrayList_x" are declared
    # just to allow reading the "lines_x" and "lines_y" through "shape" and are unused at the rest of the function.
    lines_x, columns_x, arrayList_x = x.shape
    lines_y, columns_y = y.shape

    # Error: incompatible lengths of 'x' and 'y'.
    if (lines_x != lines_y):
        print("Error on filterCornerCases01: the lengths of 'x and 'y' are different!")
        return None

    # Regular processing
    else:

        # Intially, "y" is locally categorized to standardize it to usage within the ResNets
        y_categorical = to_categorical(y)

        # For each line of "x", checks if the corner case flags from the 190th to the 209th column of x are equal to '1'.
        # When such a condition is satisfied, the corresponding lines of "x" and "y" are added to "x_ccNN_data", "x_ccNN_safety"
        # and "y_ccNN" as follows:
        # a) 190th column = 1 --> Data is added to "x_cc01_data", "x_cc01_safety" and "y_cc01"
        # b) 191th column = 1 --> Data is added to "x_cc10_data", "x_cc10_safety" and "y_cc10"
        # c) 192th column = 1 --> Data is added to "x_cc02_data", "x_cc02_safety" and "y_cc02"
        # d) 193th column = 1 --> Data is added to "x_cc20_data", "x_cc20_safety" and "y_cc20"
        # e) 194th column = 1 --> Data is added to "x_cc03_data", "x_cc03_safety" and "y_cc03"
        # f) 195th column = 1 --> Data is added to "x_cc30_data", "x_cc30_safety" and "y_cc30"
        # g) 196th column = 1 --> Data is added to "x_cc04_data", "x_cc04_safety" and "y_cc04"
        # h) 197th column = 1 --> Data is added to "x_cc40_data", "x_cc40_safety" and "y_cc40"
        # i) 198th column = 1 --> Data is added to "x_cc12_data", "x_cc12_safety" and "y_cc12"
        # j) 199th column = 1 --> Data is added to "x_cc21_data", "x_cc21_safety" and "y_cc21"
        # k) 200th column = 1 --> Data is added to "x_cc13_data", "x_cc13_safety" and "y_cc13"
        # l) 201st column = 1 --> Data is added to "x_cc31_data", "x_cc31_safety" and "y_cc31"
        # m) 202nd column = 1 --> Data is added to "x_cc14_data", "x_cc14_safety" and "y_cc14"
        # n) 203rd column = 1 --> Data is added to "x_cc41_data", "x_cc41_safety" and "y_cc41"
        # o) 204th column = 1 --> Data is added to "x_cc23_data", "x_cc23_safety" and "y_cc23"
        # p) 205th column = 1 --> Data is added to "x_cc32_data", "x_cc32_safety" and "y_cc32"
        # q) 206th column = 1 --> Data is added to "x_cc24_data", "x_cc24_safety" and "y_cc24"
        # r) 207th column = 1 --> Data is added to "x_cc42_data", "x_cc42_safety" and "y_cc42"
        # s) 208th column = 1 --> Data is added to "x_cc34_data", "x_cc34_safety" and "y_cc34"
        # t) 209th column = 1 --> Data is added to "x_cc43_data", "x_cc43_safety" and "y_cc43"
        for i in range (0, lines_x):
        
            # Scenario "a)"
            if (x[i][189] == np.array(1) and y[i] == np.array(0)):
                x_cc01_data.append(x[i, :-22])
                x_cc01_safety.append(x[i, -22:])
                y_cc01.append(y_categorical[i])

            # Error on scenario "a)" - invalid output on "y"
            elif (x[i][189] == np.array(1) and y[i] != np.array(0)):
                print("Error on filterCornerCases: corner case 0 --> 1 does not have the correct category!")
                return None

            # Scenario "b)"
            if (x[i][190] == np.array(1) and y[i] == np.array(1)):
                x_cc10_data.append(x[i, :-22])
                x_cc10_safety.append(x[i, -22:])
                y_cc10.append(y_categorical[i])

            # Error on scenario "b)" - invalid output on "y"
            elif (x[i][190] == np.array(1) and y[i] != np.array(1)):
                print("Error on filterCornerCases: corner case 1 --> 0 does not have the correct category!")
                return None

            # Scenario "c)"
            if (x[i][191] == np.array(1) and y[i] == np.array(0)):
                x_cc02_data.append(x[i, :-22])
                x_cc02_safety.append(x[i, -22:])
                y_cc02.append(y_categorical[i])

            # Error on scenario "c)" - invalid output on "y"
            elif (x[i][191] == np.array(1) and y[i] != np.array(0)):
                print("Error on filterCornerCases: corner case 0 --> 2 does not have the correct category!")
                return None

            # Scenario "d)"
            if (x[i][192] == np.array(1) and y[i] == np.array(2)):
                x_cc20_data.append(x[i, :-22])
                x_cc20_safety.append(x[i, -22:])
                y_cc20.append(y_categorical[i])

            # Error on scenario "d)" - invalid output on "y"
            elif (x[i][192] == np.array(1) and y[i] != np.array(2)):
                print("Error on filterCornerCases: corner case 2 --> 0 does not have the correct category!")
                return None

            # Scenario "e)"
            if (x[i][193] == np.array(1) and y[i] == np.array(0)):
                x_cc03_data.append(x[i, :-22])
                x_cc03_safety.append(x[i, -22:])
                y_cc03.append(y_categorical[i])

            # Error on scenario "e)" - invalid output on "y"
            elif (x[i][193] == np.array(1) and y[i] != np.array(0)):
                print("Error on filterCornerCases: corner case 0 --> 3 does not have the correct category!")
                return None

            # Scenario "f)"
            if (x[i][194] == np.array(1) and y[i] == np.array(3)):
                x_cc30_data.append(x[i, :-22])
                x_cc30_safety.append(x[i, -22:])
                y_cc30.append(y_categorical[i])

            # Error on scenario "f)" - invalid output on "y"
            elif (x[i][194] == np.array(1) and y[i] != np.array(3)):
                print("Error on filterCornerCases: corner case 3 --> 0 does not have the correct category!")
                return None

            # Scenario "g)"
            if (x[i][195] == np.array(1) and y[i] == np.array(0)):
                x_cc04_data.append(x[i, :-22])
                x_cc04_safety.append(x[i, -22:])
                y_cc04.append(y_categorical[i])

            # Error on scenario "g)" - invalid output on "y"
            elif (x[i][195] == np.array(1) and y[i] != np.array(0)):
                print("Error on filterCornerCases: corner case 0 --> 4 does not have the correct category!")
                return None

            # Scenario "h)"
            if (x[i][196] == np.array(1) and y[i] == np.array(4)):
                x_cc40_data.append(x[i, :-22])
                x_cc40_safety.append(x[i, -22:])
                y_cc40.append(y_categorical[i])

            # Error on scenario "h)" - invalid output on "y"
            elif (x[i][196] == np.array(1) and y[i] != np.array(4)):
                print("Error on filterCornerCases: corner case 4 --> 0 does not have the correct category!")
                return None

            # Scenario "i)"
            if (x[i][197] == np.array(1) and y[i] == np.array(1)):
                x_cc12_data.append(x[i, :-22])
                x_cc12_safety.append(x[i, -22:])
                y_cc12.append(y_categorical[i])

            # Error on scenario "i)" - invalid output on "y"
            elif (x[i][197] == np.array(1) and y[i] != np.array(1)):
                print("Error on filterCornerCases: corner case 1 --> 2 does not have the correct category!")
                return None

            # Scenario "j)"
            if (x[i][198] == np.array(1) and y[i] == np.array(2)):
                x_cc21_data.append(x[i, :-22])
                x_cc21_safety.append(x[i, -22:])
                y_cc21.append(y_categorical[i])

            # Error on scenario "j)" - invalid output on "y"
            elif (x[i][198] == np.array(1) and y[i] != np.array(2)):
                print("Error on filterCornerCases: corner case 2 --> 1 does not have the correct category!")
                return None

            # Scenario "k)"
            if (x[i][199] == np.array(1) and y[i] == np.array(1)):
                x_cc13_data.append(x[i, :-22])
                x_cc13_safety.append(x[i, -22:])
                y_cc13.append(y_categorical[i])

            # Error on scenario "k)" - invalid output on "y"
            elif (x[i][199] == np.array(1) and y[i] != np.array(1)):
                print("Error on filterCornerCases: corner case 1 --> 3 does not have the correct category!")
                return None

            # Scenario "l)"
            if (x[i][200] == np.array(1) and y[i] == np.array(3)):
                x_cc31_data.append(x[i, :-22])
                x_cc31_safety.append(x[i, -22:])
                y_cc31.append(y_categorical[i])

            # Error on scenario "l)" - invalid output on "y"
            elif (x[i][200] == np.array(1) and y[i] != np.array(3)):
                print("Error on filterCornerCases: corner case 3 --> 1 does not have the correct category!")
                return None

            # Scenario "m)"
            if (x[i][201] == np.array(1) and y[i] == np.array(1)):
                x_cc14_data.append(x[i, :-22])
                x_cc14_safety.append(x[i, -22:])
                y_cc14.append(y_categorical[i])

            # Error on scenario "m)" - invalid output on "y"
            elif (x[i][201] == np.array(1) and y[i] != np.array(1)):
                print("Error on filterCornerCases: corner case 1 --> 4 does not have the correct category!")
                return None

            # Scenario "n)"
            if (x[i][202] == np.array(1) and y[i] == np.array(4)):
                x_cc41_data.append(x[i, :-22])
                x_cc41_safety.append(x[i, -22:])
                y_cc41.append(y_categorical[i])

            # Error on scenario "n)" - invalid output on "y"
            elif (x[i][202] == np.array(1) and y[i] != np.array(4)):
                print("Error on filterCornerCases: corner case 4 --> 1 does not have the correct category!")
                return None

            # Scenario "o)"
            if (x[i][203] == np.array(1) and y[i] == np.array(2)):
                x_cc23_data.append(x[i, :-22])
                x_cc23_safety.append(x[i, -22:])
                y_cc23.append(y_categorical[i])

            # Error on scenario "o)" - invalid output on "y"
            elif (x[i][203] == np.array(2) and y[i] != np.array(2)):
                print("Error on filterCornerCases: corner case 2 --> 3 does not have the correct category!")
                return None

            # Scenario "p)"
            if (x[i][204] == np.array(1) and y[i] == np.array(3)):
                x_cc32_data.append(x[i, :-22])
                x_cc32_safety.append(x[i, -22:])
                y_cc32.append(y_categorical[i])

            # Error on scenario "p)" - invalid output on "y"
            elif (x[i][204] == np.array(1) and y[i] != np.array(3)):
                print("Error on filterCornerCases: corner case 3 --> 2 does not have the correct category!")
                return None

            # Scenario "q)"
            if (x[i][205] == np.array(1) and y[i] == np.array(2)):
                x_cc24_data.append(x[i, :-22])
                x_cc24_safety.append(x[i, -22:])
                y_cc24.append(y_categorical[i])

            # Error on scenario "q)" - invalid output on "y"
            elif (x[i][205] == np.array(1) and y[i] != np.array(2)):
                print("Error on filterCornerCases: corner case 2 --> 4 does not have the correct category!")
                return None

            # Scenario "r)"
            if (x[i][206] == np.array(1) and y[i] == np.array(4)):
                x_cc42_data.append(x[i, :-22])
                x_cc42_safety.append(x[i, -22:])
                y_cc42.append(y_categorical[i])

            # Error on scenario "r)" - invalid output on "y"
            elif (x[i][206] == np.array(1) and y[i] != np.array(4)):
                print("Error on filterCornerCases: corner case 4 --> 2 does not have the correct category!")
                return None

            # Scenario "s)"
            if (x[i][207] == np.array(1) and y[i] == np.array(3)):
                x_cc34_data.append(x[i, :-22])
                x_cc34_safety.append(x[i, -22:])
                y_cc34.append(y_categorical[i])

            # Error on scenario "s)" - invalid output on "y"
            elif (x[i][207] == np.array(1) and y[i] != np.array(3)):
                print("Error on filterCornerCases: corner case 3 --> 4 does not have the correct category!")
                return None

            # Scenario "t)"
            if (x[i][208] == np.array(1) and y[i] == np.array(4)):
                x_cc43_data.append(x[i, :-22])
                x_cc43_safety.append(x[i, -22:])
                y_cc43.append(y_categorical[i])

            # Error on scenario "t)" - invalid output on "y"
            elif (x[i][208] == np.array(1) and y[i] != np.array(4)):
                print("Error on filterCornerCases: corner case 4 --> 3 does not have the correct category!")
                return None
            
            
    # Returns "x_cc01_data", "x_cc01_safety" and "y_cc01" as NumPy arrays
    return (np.array(x_cc01_data), np.array(x_cc01_safety), np.array(y_cc01),
            np.array(x_cc10_data), np.array(x_cc10_safety), np.array(y_cc10),
            np.array(x_cc02_data), np.array(x_cc02_safety), np.array(y_cc02),
            np.array(x_cc20_data), np.array(x_cc20_safety), np.array(y_cc20),
            np.array(x_cc03_data), np.array(x_cc03_safety), np.array(y_cc03),
            np.array(x_cc30_data), np.array(x_cc30_safety), np.array(y_cc30),
            np.array(x_cc04_data), np.array(x_cc04_safety), np.array(y_cc04),
            np.array(x_cc40_data), np.array(x_cc40_safety), np.array(y_cc40),
            np.array(x_cc12_data), np.array(x_cc12_safety), np.array(y_cc12),
            np.array(x_cc21_data), np.array(x_cc21_safety), np.array(y_cc21),
            np.array(x_cc13_data), np.array(x_cc13_safety), np.array(y_cc13),
            np.array(x_cc31_data), np.array(x_cc31_safety), np.array(y_cc31),
            np.array(x_cc14_data), np.array(x_cc14_safety), np.array(y_cc14),
            np.array(x_cc41_data), np.array(x_cc41_safety), np.array(y_cc41),
            np.array(x_cc23_data), np.array(x_cc23_safety), np.array(y_cc23),
            np.array(x_cc32_data), np.array(x_cc32_safety), np.array(y_cc32),
            np.array(x_cc24_data), np.array(x_cc24_safety), np.array(y_cc24),
            np.array(x_cc42_data), np.array(x_cc42_safety), np.array(y_cc42),
            np.array(x_cc34_data), np.array(x_cc34_safety), np.array(y_cc34),
            np.array(x_cc43_data), np.array(x_cc43_safety), np.array(y_cc43))

""" Function array_of_arrays_to_array_of_ints

- Inputs: a) "input": Array whose elements are singleton arrays.

- Outputs: a) "output": Array whose elements are the integers of the singleton arrays.

- Summary: Transforms and array whose elements are singleton arrays into an array whose elements are the integers of the singleton arrays.
""" 
def array_of_arrays_to_array_of_ints(input):

    # Creates the output of the function an empty array
    output = []

    # Gets the length (number of lines) of "input". "columns_input" is declared just to
    # allow reading "lines_input" through "shape" and are unused at the rest of the function.
    lines_input, columns_input = input.shape

    for i in range (0, lines_input):

        output.append(int(input[i][0]))

    # Returns the processed output
    return np.array(output)

""" Function comparison_result

- Inputs: a) "decoded_y_pred": Array with the categories predicted by the classifier for a specific fold / emsemble member.
              Each category is an integer within [0; 4].
          b) "corner_case": String with the identification of the set of corner cases dealt with.

- Outputs: An array with the result of the comparison between "y_pred" and the ground truth according to the corner case.

- Summary: Decodes y_pred, compares it to decoded_y_truth and produces an array reporting the comparison between them both.
""" 
def comparison_result(decoded_y_pred, corner_case):

    # Gets the length (number of lines) of "decoded_y_truth".
    lines_decoded_y_pred = decoded_y_pred.size

    # Makes y_comparison equal to an empty list
    y_comparison = []

    # Diagnoses the comparison between decoded_y_pred and decoded_y_truth according to the corner case under study
    # Please refer to the following dictionary for the analysis:
    # 0 --> Truly positive lack of arrithmia
    # 1 --> Truly positive presence of expected arrithmia
    # 2 --> Falsely positive lack of arrithmia expected for the corner case
    # 3 --> Falsely positive lack of arrithmia not expected for the corner case
    # 4 --> Falsely positive arrithmia of the expected type for the corner case
    # 5 --> Falsely positive arrithmia of an unexpected type for the corner case
    # 6 --> Truly positive presence of arrithmia of the expected type for the corner case
    # 7 --> Truly positive presence of arrithmia of an unexpected type for the corner case
    for i in range (0, lines_decoded_y_pred):

        # a) Corner Case 0 --> 1: decoded_y_truth equals to '0' (lack of arrithmias)
        if corner_case == 'cc01':

            if (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(0))
            elif (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(4))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(5))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # b) Corner Case 0 --> 2: decoded_y_truth equals to '0' (lack of arrithmias)
        elif corner_case == 'cc02':

            if (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(0))
            elif (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(4))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(5))            
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # c) Corner Case 0 --> 3: decoded_y_truth equals to '0' (lack of arrithmias)
        elif corner_case == 'cc03':

            if (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(0))
            elif (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(4))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(5))            
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # d) Corner Case 0 --> 4: decoded_y_truth equals to '0' (lack of arrithmias)
        elif corner_case == 'cc04':

            if (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(0))
            elif (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(4))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(5))            
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # e) Corner Case 1 --> 0: decoded_y_truth equals to '1' (arrithmia type 1)
        elif corner_case == 'cc10':

            if (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(2))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # f) Corner Case 1 --> 2: decoded_y_truth equals to '1' (arrithmia type 1)
        elif corner_case == 'cc12':

            if (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # g) Corner Case 1 --> 3: decoded_y_truth equals to '1' (arrithmia type 1)
        elif corner_case == 'cc13':

            if (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # h) Corner Case 1 --> 4: decoded_y_truth equals to '1' (arrithmia type 1)
        elif corner_case == 'cc14':

            if (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # i) Corner Case 2 --> 0: decoded_y_truth equals to '2' (arrithmia type 2)
        elif corner_case == 'cc20':

            if (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(2))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # j) Corner Case 2 --> 1: decoded_y_truth equals to '2' (arrithmia type 2)
        elif corner_case == 'cc21':

            if (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 3 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # k) Corner Case 2 --> 3: decoded_y_truth equals to '2' (arrithmia type 2)
        elif corner_case == 'cc23':

            if (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # l) Corner Case 2 --> 4: decoded_y_truth equals to '2' (arrithmia type 2)
        elif corner_case == 'cc24':

            if (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # m) Corner Case 3 --> 0: decoded_y_truth equals to '3' (arrithmia type 3)
        elif corner_case == 'cc30':

            if (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(2))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # n) Corner Case 3 --> 1: decoded_y_truth equals to '3' (arrithmia type 3)
        elif corner_case == 'cc31':

            if (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # o) Corner Case 3 --> 2: decoded_y_truth equals to '3' (arrithmia type 3)
        elif corner_case == 'cc32':

            if (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 4):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # p) Corner Case 3 --> 4: decoded_y_truth equals to '3' (arrithmia type 3)
        elif corner_case == 'cc34':

            if (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # q) Corner Case 4 --> 0: decoded_y_truth equals to '4' (arrithmia type 4)
        elif corner_case == 'cc40':

            if (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(2))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(7))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # r) Corner Case 4 --> 1: decoded_y_truth equals to '4' (arrithmia type 4)
        elif corner_case == 'cc41':

            if (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 1):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 2 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)
        
        # s) Corner Case 4 --> 2: decoded_y_truth equals to '4' (arrithmia type 4)
        elif corner_case == 'cc42':

            if (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 2):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 3):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # t) Corner Case 4 --> 3: decoded_y_truth equals to '4' (arrithmia type 4)
        elif corner_case == 'cc43':

            if (decoded_y_pred[i] == 4):
                y_comparison.append(np.array(1))
            elif (decoded_y_pred[i] == 3):
                y_comparison.append(np.array(6))
            elif (decoded_y_pred[i] == 1 or decoded_y_pred[i] == 2):
                y_comparison.append(np.array(7))
            elif (decoded_y_pred[i] == 0):
                y_comparison.append(np.array(3))
            else:
                print("Error on comparison_result: unexpected classification on " + corner_case)

        # Error
        else:
            print("Error on comparison_result: unexpected corner case. Received " + corner_case)
    

    # Writes the 'fileName' CSV file
    return np.array(y_comparison)

""" Function write_corner_case_results_xlsx
- Inputs: a) "id": Array with the list of corner case heartbeat IDs defined in the "mitbih_train_sa.csv" and "mitbih_test_sa.csv" files.
          b) "y_truth": Array with the heartbeats' ground truth category, as per the "mitbih_train_sa.csv" and "mitbih_test_sa.csv" files,
              but with one-hot encoding.
          c) "y_pred": List of arrays with the category predicted by the classifier for the corner case for each fold.
              All categories have a discrete probability of occurrence in an one-hot encoding fashion.
          d) "corner_case": String with the identification of the set of corner cases dealt with.
          e) "classifier": String with the identification of the classifier that lead to the results, as per the original
             design of Kozal and Ksieniewicz.
          g) "fold_number": Indication of the latest analyzed folder (for UMCE batch printing only).

- Outputs: A .xlsx file named as per the inputs "corner_case" and "classifier" string with several columns:
           "id", "y_truth", "y_pred" for each fold, and the result of the comparison between "y_truth" and "y_pred"
            for each "id" and fold, as per the function "comparison_result".

- Summary: Writes a .xlsx file named as per the inputs "corner_case" and "classifier" reporting the full results of a corner case group.
""" 
def write_corner_case_results_xlsx(id, y_truth, y_pred, corner_case, classifier, fold_number):
    
    # Transforms the array of single arrays "id" into an array of integers
    id_array = array_of_arrays_to_array_of_ints(id)

    # Decodes the one-hot encoding of y_truth
    decoded_y_truth = y_truth.argmax(axis=1)
    
    # Categorizes 'y_pred' in case it has discrete values by making its highest category equal to '1' and the rest equal to '0'
    # and, afterwards, decodes the one-hot encoding.

    # a) Initializes decoded_y_pred as an empty list
    decoded_y_pred = []

    for i in range (0, len(y_pred)):
        decoded_y_pred.append(y_pred[i].argmax(axis=1))
    
    # c) Transforms decoded_y_pred into an array
    decoded_y_pred = np.array(decoded_y_pred)    

    # Variable to store the results of the comparison between decoded_y_truth and decoded_y_pred
    y_comparison = []

    # Compares "decoded_y_truth" to "decoded_y_pred" and saves the result on "y_comparison" for each fold of 'decoded_y_truth'
    # Gets the length (number of lines) of "decoded_y_pred". "columns_decoded_y_pred" is declared just to 
    # allow reading "lines_y_truth" through "shape" and are unused at the rest of the function.
    lines_y_truth, columns_y_truth = decoded_y_pred.shape

    for i in range (0, lines_y_truth):
        y_comparison.append(comparison_result(decoded_y_pred[i], corner_case))    

    # Creates pandas dataframe with "id", "decoded_y_truth", "decoded_y_pred" and "y_comparison".
    # Since each of them is a line, the dataframe shall be transposed so that its columns are
    # "id", "decoded_y_truth", "decoded_y_pred" and "y_comparison".

    # a) Creates the names of each field. 'Heartbeat ID' and 'Ground Truth' are valid for every case. Moreover,
    # 'Predicted Category Fold X' and 'Comparison Result Fold X' are created for each of the folds / ensemble elements
    # within the scope of the experiment.
    index_names = ['Hearbeat ID', 'Ground Truth']

    # For ResNets, both SMOTE variants, and UMCE, the columns only have fields 'Predicted Category Fold X' and 'Comparison Result Fold X'
    # Specifically for UMCE, however, the ID of each fold depends not only on lines_y_truth, but also on 'fold_number'. 
    if (classifier == 'ResNet' or classifier == 'SMOTE' or classifier == 'SMOTE_Aug'):
        for i in range (0, lines_y_truth):
            index_names.append('Predicted Category Fold ' + str(i + 1).zfill(2))
            index_names.append('Comparison Result Fold ' + str(i + 1).zfill(2))

    # Specific labeling for UMCE due to fold ID differences
    elif (classifier == 'UMCE'):
        for i in range (0, lines_y_truth):
            # Case 1: fold_number == 4 --> Folds shall be numbered from 1 to 5
            if (fold_number == 4):
                index_names.append('Predicted Category Fold ' + str(i + 1).zfill(2))
                index_names.append('Comparison Result Fold ' + str(i + 1).zfill(2))
            
            # Case 2: fold_number == 9 --> Folds shall be numbered from 6 to 10
            elif (fold_number == 9):
                index_names.append('Predicted Category Fold ' + str(i + 6).zfill(2))
                index_names.append('Comparison Result Fold ' + str(i + 6).zfill(2))

            # Case 3: Other fold_number values --> Invalid scenario to call 'write_corner_case_results_xlsx'
            else:
                print("Error on write_corner_case_results_xlsx table creation for UMCE: Function called with fold_number = " + fold_number + " instead of 4 or 9")
    
    # Error if other classifier is used:
    else:
        print("Error on write_corner_case_results_xlsx table creation: Invalid classifier named " + classifier)

    # b) Creates the vertical array with each line comprising one of the variables.
    # id_array and decoded_y_truth are the two first elements and they are always present.
    # Moreover, adds each element of decoded_y_pred and y_comparison according to the number of folds / UMCE elements
    # within the scope of the experiment

    data_for_dataframe = np.vstack((id_array, decoded_y_truth))
    for i in range (0, lines_y_truth):
        data_for_dataframe = np.vstack((data_for_dataframe, decoded_y_pred[i], y_comparison[i]))

    # c) Creates the dataframe with each line comprising one of the variables
    dataframe = pd.DataFrame(data = data_for_dataframe, index = index_names)

    # c) Transposes the dataframe so that each of the variables corresponds to a dataframe column
    dataframe = dataframe.transpose()

    # Defines the XLSX filename with the name given by combining the strings "classifier" and "corner_case" with "_"
    # If 'UMCE', adds to the XLSX filename the ID of the printed fold batch
    if (classifier == 'ResNet' or classifier == 'SMOTE' or classifier == 'SMOTE_Aug'):
        fileName = classifier + '_' + corner_case + '.xlsx'
    elif (classifier == 'UMCE'):
        if (fold_number == 4):
            fileName = classifier + '_' + corner_case + '_folds1-5.xlsx'
        elif (fold_number == 9):
            fileName = classifier + '_' + corner_case + '_folds6-10.xlsx'
        else:
            print("Error on write_corner_case_results_xlsx file creation: Invalid fold_number for batch report:" + str(fold_number))
    else:
        print("Error on write_corner_case_results_xlsx file creation: Invalid classifier named " + classifier)

    # Writes the 'fileName' XLSX file
    with pd.ExcelWriter(fileName) as writer:
        dataframe.to_excel(writer, sheet_name = fileName, index = False)