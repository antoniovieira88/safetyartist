# Safety ArtISt - Module created to run tests on the applicable functions of 'oversampling.smote' (including both SMOTE variants)

# Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

# Importing the corresponding components
from oversampling.smote import *
from tests.smote_test import *

if __name__ == '__main__':
    
    # Runs all 'tests.fusion_methods_test' tests on the proper order
    sample_dataset = imbalanced_iris()

    # Regular SMOTE
    test_after_smote_bincount_is_equal(sample_dataset)
    test_after_smote_there_is_right_number_of_examples_in_dataset(sample_dataset)
    test_after_smote_shape_of_dataset_is_correct(sample_dataset)
    test_after_smote_ndim(sample_dataset)

    # SMOTE with Data Augmentation
    test_after_smote_with_augmentation_bincount_is_equal(sample_dataset)
    test_after_smote_with_augmentation_there_is_right_number_of_examples_in_dataset(sample_dataset)
    test_after_smote_with_augmentation_shape_of_dataset_is_correct(sample_dataset)
    test_after_smote_with_augmentation_ndim(sample_dataset)
