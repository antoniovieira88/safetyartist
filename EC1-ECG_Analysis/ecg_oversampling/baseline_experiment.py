# Safety ArtISt: Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

from keras.utils.np_utils import to_categorical
from sklearn.model_selection import StratifiedKFold

from base_model import *
from dataset_utils.read_MIT_dataset import *
from ensamble.fusion_methods import *
from ensamble.umce import *
from experiment_utils.metrics import *
from oversampling.reduce_imbalance import *

# Safety ArtISt - Import functions to support safety assurance
from safetyArtist.saUtils import *

if __name__ == '__main__':
    num_classes = 5
    
    
    # Safety ArtISt: Replaced 'load_whole_dataset' with 'load_whole_dataset_safety'.
    x, y = load_whole_dataset_safety()
    
    # Safety ArtISt: Computation of all groups of corner cases.
    (x_cc01_data, x_cc01_safety, y_cc01,
     x_cc10_data, x_cc10_safety, y_cc10,
     x_cc02_data, x_cc02_safety, y_cc02,
     x_cc20_data, x_cc20_safety, y_cc20,
     x_cc03_data, x_cc03_safety, y_cc03,
     x_cc30_data, x_cc30_safety, y_cc30,
     x_cc04_data, x_cc04_safety, y_cc04,
     x_cc40_data, x_cc40_safety, y_cc40,
     x_cc12_data, x_cc12_safety, y_cc12,
     x_cc21_data, x_cc21_safety, y_cc21,
     x_cc13_data, x_cc13_safety, y_cc13,
     x_cc31_data, x_cc31_safety, y_cc31,
     x_cc14_data, x_cc14_safety, y_cc14,
     x_cc41_data, x_cc41_safety, y_cc41,
     x_cc23_data, x_cc23_safety, y_cc23,
     x_cc32_data, x_cc32_safety, y_cc32,
     x_cc24_data, x_cc24_safety, y_cc24,
     x_cc42_data, x_cc42_safety, y_cc42,
     x_cc34_data, x_cc34_safety, y_cc34,
     x_cc43_data, x_cc43_safety, y_cc43) = filterCornerCases (x, y)

    sets_shapes_report(x, y)

    kf = StratifiedKFold(n_splits=10, shuffle=True, random_state=None)

    # Safety ArtISt: Replaced "x" with "x[:, :-22] to filter out the safety-related columns" from the input_shape
    # variable, which is used for defining the ResNet actual input shape. It shall be equal to (187, 1).
    input_shape = x[:, :-22].shape[1:]

    acc, precision, recall, f1 = [], [], [], []

    for fold_number, (train_index, test_index) in enumerate(kf.split(x, y)):
        print("fold ", fold_number+1)
        x_train, x_test = x[train_index], x[test_index]
        y_train, y_test = y[train_index], y[test_index]

        # prepare data for traning
        num_undersample = np.min(np.bincount(
            y_train.astype('int16').flatten()))
        x_train, y_train = reduce_imbalance(
            x_train, y_train, None, num_examples=num_undersample)  # No oversampling technique

        # Safety ArtISt - Filter data added for safety assurance purposes (heartbeat ID, hearbeat size and corner case flags)
        # from "x_train" and "x_test"
        x_train, x_test, x_safety_train, x_safety_test = filterSafetyData(x_train, x_test)
        
        # Safety ArtISt - Lines of Code enabled to check for oversampling / undersampling shapes
        sets_shapes_report(x_train, y_train)
        sets_shapes_report(x_test, y_test)

        # Safety ArtISt - Lines of Code introduced to check for proper filtering of safety-critical data
        sets_shapes_report_sa(x_safety_train, None)
        sets_shapes_report_sa(x_safety_test, None)
        
        y_train = to_categorical(y_train)
        y_test = to_categorical(y_test)

        # sample and train model

        def sample_base_model():
            return BaseModel(input_shape, batch_size=32)
        base_model = BaseModel(input_shape, batch_size=32)
        base_model.fit(x_train, y_train, x_test, y_test)

        # evaluate metrics
        y_pred = base_model.predict(x_test)
        a, p, r, f = metrics_values(y_pred, y_test)
        acc.append(a)
        precision.append(p)
        recall.append(r)
        f1.append(f)

        print("\n\n")

    precision = np.vstack(precision)
    recall = np.vstack(recall)
    f1 = np.vstack(f1)
    metrics_report(acc, precision, recall, f1)
