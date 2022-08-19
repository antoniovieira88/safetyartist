# Safety ArtISt - Module created to run tests on the applicable functions of 'ensamble.fusion_methods' component

# Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

# Importing the corresponding components
from ensamble.fusion_methods import *
from tests.fusion_methods_test import *

if __name__ == '__main__':
    
    # Runs all 'tests.fusion_methods_test' tests on the proper order

    # Tests with knowingly consistent decision
    test_avrg_fusion__consistent_decisions__returns_array_with_right_values()
    test_avrg_fusion__consistent_decisions__returns_array_with_valid_shape()
    test_avrg_fusion__consistent_decisions__returns_array_with_valid_ndim()

    # Tests with knowingly inconsistent decisions
    test_avrg_fusion__inconsistent_decisions__returns_array_with_right_values()
    test_avrg_fusion__inconsistent_decisions__returns_array_with_valid_shape()
    test_avrg_fusion__inconsistent_decisions__returns_array_with_valid_ndim()