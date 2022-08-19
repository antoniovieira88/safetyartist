# Safety ArtISt - Module created to run tests on the applicable functions of 'oversampling.smote' (including both SMOTE variants)

# Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

# Importing the corresponding components
from tests.umce_test import *

""" Function create_class_counts_array

- Inputs: None.

- Outputs: An array of lists to perform a subset of the 'umce_test.py' component tests which requires generating different datasets.
           The array has 225 elements, with each element 'i' from 'i+4', with i = {0; 5; ...; 220} being equal among themselves.
           Each of the 45 different elements is a list from 2 to 10 elements, with 5 different sets of elements per list size.

- Summary: Generates a set of 270 int random numbers and sort them as a set of 45 lists: 5 with 2 elements, 5 with 3 elements, 5 with 4 elements,
           5 with 5 elements, 5 with 6 elements, 5 with 7 elements, 5 with 8 elements, 5 with 9 elements, and 5 with 10 elements. An array with
           all the lists, each of which replicated in five consecutive positions, is returned by the function. Such replicas are made to make it
           easier to map each 'class_counts' to the different 'num_features' exercised along with them during the tests. 
           Random numbers are generated within the set [1; 512], which was defined following the same specification of the built-in, pytest-based
           tests within the component 'umce_test.py'. The list sizing ranging from 2 to 10 also stems from the same reason and origin.
""" 
def create_class_counts_array ():

    array_of_lists = []
    
    # Generates all random numbers that will populate class_counts
    generated_numbers = np.random.randint(low = 1, high = 513, size = 270)

    # Initializes i iterator with 0
    i = 0

    # Generates 2-D lists    
    while i < 10:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1]])
        i = i + 2

    # Generates 3-D lists    
    while i < 25:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2]])
        i = i + 3

    # Generates 4-D lists    
    while i < 45:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3]])
        i = i + 4

    # Generates 5-D lists    
    while i < 70:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4]])
        i = i + 5

    # Generates 6-D lists    
    while i < 100:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4],
                                   generated_numbers[i+5]])
        i = i + 6

    # Generates 7-D lists    
    while i < 135:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4],
                                   generated_numbers[i+5], generated_numbers[i+6]])
        i = i + 7

    # Generates 8-D lists    
    while i < 175:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4],
                                   generated_numbers[i+5], generated_numbers[i+6], generated_numbers[i+7]])
        i = i + 8

    # Generates 9-D lists    
    while i < 220:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4],
                                   generated_numbers[i+5], generated_numbers[i+6], generated_numbers[i+7], generated_numbers[i+8]])
        i = i + 9

    # Generates 10-D lists    
    while i < 270:

        for j in range (5):
            array_of_lists.append([generated_numbers[i], generated_numbers[i+1], generated_numbers[i+2], generated_numbers[i+3], generated_numbers[i+4],
                                   generated_numbers[i+5], generated_numbers[i+6], generated_numbers[i+7], generated_numbers[i+8], generated_numbers[i+9]])
        i = i + 10

    return array_of_lists

if __name__ == '__main__':

    # Initializes variables used in iterative tests

    # a) num_features: According to the original tests on 'umce_test.py', elements within the interval [1; 100] shall be
    #    exercised. A total of 5 random numbers within that interval is generated for each list within 'class_counts'.
    #    Since class_counts has 5 different lists for each of the 9 different sizes, a total of 5 x 9 x 5 = 225 numbers are
    #    generated.
    num_features = np.random.randint(low = 1, high = 101, size = 225)

    # b) class_counts: According to the original tests on 'umce_test.py', 2-D to 10-D lists with elements within the
    #                  interval [1; 512] shall be exercised. 5 different lists of each size are randomly generated.
    #                  Each list is repeated 5 times to make it easier to map it with each 'num_features' element.
    class_counts = create_class_counts_array ()

    # Sets up the TestUMCE class
    TestUMCE.setup(TestUMCE)
    
    # Instantiates 'TestsUMCE' class with umce_test object
    umce_test = TestUMCE()
    
    # Runs tests
    umce_test.test_get_samples_in_classes_for_simple_dataset_all_returned_y_arrays_contain_only_one_label()
    umce_test.test_get_samples_in_classes_for_simple_dataset_all_returned_arrays_have_valid_ndim()
    umce_test.test_get_samples_in_classes_for_simple_dataset_all_returned_x_y_have_same_number_of_examples()
    umce_test.test_get_samples_in_classes_for_simple_dataset_all_classes_found()
    umce_test.test_get_num_samples_in_each_class_returns_right_number()
    umce_test.test_after_fit_simple_dataset_num_classifiers_is_3()
    umce_test.test_k_fold_for_each_class_returns_right_number_of_folds()
    umce_test.test_k_fold_for_each_class_number_samples_in_each_fold_close_to_minimal_num_of_samples()
    umce_test.test_k_fold_for_each_class_number_each_fold_for_x_and_y_have_the_same_len()
    umce_test.test_k_fold_for_each_class_ndim_of_folds_is_correct()
    umce_test.test_simple_dataset_after_fit_dummy_classifiers_are_fitted()
    umce_test.test_simple_dataset_after_predict_reutrns_array_with_valid_size()
    umce_test.test_ModelMock_fit_called_3_times()
    umce_test.test_ModelMock_predict_called_3_times()
    umce_test.test_get_samples_in_classes_all_returned_y_arrays_contain_only_one_label()
    umce_test.test_get_samples_in_classes_all_returned_arrays_have_valid_ndim()
    umce_test.test_get_samples_in_classes_all_returned_x_y_have_same_number_of_examples()
    umce_test.test_get_samples_in_classes_all_classes_found()
    umce_test.test_after_fit_dummy_classifiers_are_fitted()
    umce_test.test_after_predict_reutrns_array_with_valid_size()

    for i in range (num_features.size):
        umce_test.test_get_samples_in_classes_fuzzer_all_returned_y_arrays_contain_only_one_label(class_counts[i], num_features[i])
        umce_test.test_get_samples_in_classes_fuzzer_all_returned_arrays_have_valid_ndim(class_counts[i], num_features[i])
        umce_test.test_get_samples_in_classes_fuzzer_all_returned_x_y_have_same_number_of_examples(class_counts[i], num_features[i])
        umce_test.test_get_samples_in_classes_fuzzer_all_classes_found(class_counts[i], num_features[i])
        umce_test.test_fuzzer_after_fit_dummy_classifiers_are_fitted(class_counts[i], num_features[i])
        umce_test.test_fuzzer_after_predict_reutrns_array_with_valid_size(class_counts[i], num_features[i])

    umce_test.test_single_samples_in_two_classes_after_predict_reutrns_array_with_valid_size()
    umce_test.test_many_samples_after_fit_dummy_classifiers_are_fitted()


    

    
