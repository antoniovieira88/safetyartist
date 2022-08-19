# Safety ArtISt - Module created to run tests on the applicable functions of 'oversampling.smote' (including both SMOTE variants)

# Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

# Importing the corresponding components
from oversampling.smote import *
from tests.umce_test import *

if __name__ == '__main__':

    # Sets up the TestUMCE class
    TestUMCE.setup(TestUMCE)
    
    # Instantiates 'TestsUMCE' class with umce_test object
    umce_test = TestUMCE()

    # Initializes variables used in iterative tests
    num_features = np.arange(start = 1, stop = 101, step = 1) 
    class_counts_numbers = np.arange(start = 1, stop = 513, step = 1)
    # TODO: Create lists with 2 to 10 elements of class_counts_numbers    

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

    

    
