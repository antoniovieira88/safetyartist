# Safety ArtISt: Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

from keras.utils.np_utils import to_categorical
from sklearn.model_selection import StratifiedKFold

from base_model import *
from dataset_utils.read_MIT_dataset import *
from oversampling.smote import *
from experiment_utils.metrics import *

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
    
    # List of arrays to store the results of the corner cases analyses for each cross-validation fold
    (y_cc01_pred, y_cc10_pred, y_cc02_pred,
     y_cc20_pred, y_cc03_pred, y_cc30_pred,
     y_cc04_pred, y_cc40_pred, y_cc12_pred,
     y_cc21_pred, y_cc13_pred, y_cc31_pred,
     y_cc14_pred, y_cc41_pred, y_cc23_pred,
     y_cc32_pred, y_cc24_pred, y_cc42_pred,
     y_cc34_pred, y_cc43_pred)               = [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []

    sets_shapes_report(x, y)

    kf = StratifiedKFold(n_splits=10, shuffle=True, random_state=None)
    # Safety ArtISt: Replaced "x" with "x[:, :-22]" to filter out the safety-related columns from the input_shape
    # variable, which is used for defining the ResNet actual input shape. It shall be equal to (187, 1).
    input_shape = x[:, :-22].shape[1:]

    acc, precision, recall, f1 = [], [], [], []

    for fold_number, (train_index, test_index) in enumerate(kf.split(x, y)):
        print("fold ", fold_number+1)
        x_train, x_test = x[train_index], x[test_index]
        y_train, y_test = y[train_index], y[test_index]

        # Safety ArtISt - Filter data added for safety assurance purposes (heartbeat ID, hearbeat size and corner case flags)
        # from "x_train" and "x_test". It has to be done here because, since SMOTE performs oversampling of infrequent categories,
        # it would oversample safety-critical data as well, which does not make sense for the traning of SMOTE-based classifiers.
        x_train, x_test, x_safety_train, x_safety_test = filterSafetyData(x_train, x_test)

        # prepare data for training
        x_train, y_train = smote_with_data_agumentation(x_train, y_train)

        # Safety ArtISt - Lines of Code enabled to check for oversampling / undersampling shapes
        sets_shapes_report(x_train, y_train)
        sets_shapes_report(x_test, y_test)

        # Safety ArtISt - Lines of Code introduced to check for proper filtering of safety-critical data
        sets_shapes_report_sa(x_safety_train, None)
        sets_shapes_report_sa(x_safety_test, None)
        
        y_train = to_categorical(y_train)
        y_test = to_categorical(y_test)

        # sample and train model
        base_model = BaseModel(input_shape, batch_size=32)
        base_model.fit(x_train, y_train)

        # evaluate metrics - [Safety ArtISt Comment] Holdout Test per Fold
        y_pred = base_model.predict(x_test)
        # Safety ArtISt - Updated the call of "metrics_values" to include the generation of a CSV report with the results
        a, p, r, f = metrics_values(y_pred, y_test, 'holdout_test', 'SMOTE_Aug_Fold' + str(fold_number + 1).zfill(2))
        acc.append(a)
        precision.append(p)
        recall.append(r)
        f1.append(f)

        # Safety ArtISt - Evaluate corner cases tests and compile their results on the arrays for all folds
        # Calculations are performed only to the non-null sets of corner cases
        # a) 0 similar to 1
        if x_cc01_data.size > 0:
            y_cc01_pred.append(base_model.predict(x_cc01_data))
        
        # b) 1 similar to 0
        if x_cc10_data.size > 0:
            y_cc10_pred.append(base_model.predict(x_cc10_data))

        # c) 0 similar to 2
        if x_cc02_data.size > 0:
            y_cc02_pred.append(base_model.predict(x_cc02_data))

        # d) 2 similar to 0
        if x_cc20_data.size > 0:
            y_cc20_pred.append(base_model.predict(x_cc20_data))

        # e) 0 similar to 3
        if x_cc03_data.size > 0:
            y_cc03_pred.append(base_model.predict(x_cc03_data))

        # f) 3 similar to 0
        if x_cc30_data.size > 0:
            y_cc30_pred.append(base_model.predict(x_cc30_data))

        # g) 0 similar to 4
        if x_cc04_data.size > 0:
            y_cc04_pred.append(base_model.predict(x_cc04_data))

        # h) 4 similar to 0
        if x_cc40_data.size > 0:
            y_cc40_pred.append(base_model.predict(x_cc40_data))

        # i) 1 similar to 2
        if x_cc12_data.size > 0:
            y_cc12_pred.append(base_model.predict(x_cc12_data))

        # j) 2 similar to 1
        if x_cc21_data.size > 0:
            y_cc21_pred.append(base_model.predict(x_cc21_data))

        # k) 1 similar to 3
        if x_cc13_data.size > 0:
            y_cc13_pred.append(base_model.predict(x_cc13_data))

        # l) 3 similar to 1
        if x_cc31_data.size > 0:
            y_cc31_pred.append(base_model.predict(x_cc31_data))

        # m) 1 similar to 4 - empty
        if x_cc14_data.size > 0:
            y_cc14_pred.append(base_model.predict(x_cc14_data))

        # n) 4 similar to 1
        if x_cc41_data.size > 0:
            y_cc41_pred.append(base_model.predict(x_cc41_data))

        # o) 2 similar to 3
        if x_cc23_data.size > 0:
            y_cc23_pred.append(base_model.predict(x_cc23_data))

        # p) 3 similar to 2
        if x_cc32_data.size > 0:
            y_cc32_pred.append(base_model.predict(x_cc32_data))

        # q) 2 similar to 4
        if x_cc24_data.size > 0:
            y_cc24_pred.append(base_model.predict(x_cc24_data))

        # r) 4 similar to 2
        if x_cc42_data.size > 0:
            y_cc42_pred.append(base_model.predict(x_cc42_data))

        # s) 3 similar to 4
        if x_cc34_data.size > 0:
            y_cc34_pred.append(base_model.predict(x_cc34_data))

        # t) 4 similar to 3
        if x_cc43_data.size > 0:
            y_cc43_pred.append(base_model.predict(x_cc43_data))

        print("\n\n")

    # Safety ArtISt - Write reports for all 20 possible types of corner cases
    if x_cc01_data.size > 0:
        write_corner_case_results_xlsx(x_cc01_safety[:, 0], y_cc01, y_cc01_pred, 'cc01', 'SMOTE_Aug', None, None)
    
    if x_cc02_data.size > 0:
        write_corner_case_results_xlsx(x_cc02_safety[:, 0], y_cc02, y_cc02_pred, 'cc02', 'SMOTE_Aug', None, None)
    
    if x_cc03_data.size > 0:
        write_corner_case_results_xlsx(x_cc03_safety[:, 0], y_cc03, y_cc03_pred, 'cc03', 'SMOTE_Aug', None, None)

    if x_cc04_data.size > 0:
        write_corner_case_results_xlsx(x_cc04_safety[:, 0], y_cc04, y_cc04_pred, 'cc04', 'SMOTE_Aug', None, None)

    if x_cc10_data.size > 0:
        write_corner_case_results_xlsx(x_cc10_safety[:, 0], y_cc10, y_cc10_pred, 'cc10', 'SMOTE_Aug', None, None)

    if x_cc12_data.size > 0:
        write_corner_case_results_xlsx(x_cc12_safety[:, 0], y_cc12, y_cc12_pred, 'cc12', 'SMOTE_Aug', None, None)

    if x_cc13_data.size > 0:
        write_corner_case_results_xlsx(x_cc13_safety[:, 0], y_cc13, y_cc13_pred, 'cc13', 'SMOTE_Aug', None, None)

    if x_cc14_data.size > 0:
        write_corner_case_results_xlsx(x_cc14_safety[:, 0], y_cc14, y_cc14_pred, 'cc14', 'SMOTE_Aug', None, None)

    if x_cc20_data.size > 0:
        write_corner_case_results_xlsx(x_cc20_safety[:, 0], y_cc20, y_cc20_pred, 'cc20', 'SMOTE_Aug', None, None)

    if x_cc21_data.size > 0:
        write_corner_case_results_xlsx(x_cc21_safety[:, 0], y_cc21, y_cc21_pred, 'cc21', 'SMOTE_Aug', None, None)

    if x_cc23_data.size > 0:
        write_corner_case_results_xlsx(x_cc23_safety[:, 0], y_cc23, y_cc23_pred, 'cc23', 'SMOTE_Aug', None, None)

    if x_cc24_data.size > 0:
        write_corner_case_results_xlsx(x_cc24_safety[:, 0], y_cc24, y_cc24_pred, 'cc24', 'SMOTE_Aug', None, None)

    if x_cc30_data.size > 0:
        write_corner_case_results_xlsx(x_cc30_safety[:, 0], y_cc30, y_cc30_pred, 'cc30', 'SMOTE_Aug', None, None)

    if x_cc31_data.size > 0:
        write_corner_case_results_xlsx(x_cc31_safety[:, 0], y_cc31, y_cc31_pred, 'cc31', 'SMOTE_Aug', None, None)

    if x_cc32_data.size > 0:
        write_corner_case_results_xlsx(x_cc32_safety[:, 0], y_cc32, y_cc32_pred, 'cc32', 'SMOTE_Aug', None, None)

    if x_cc34_data.size > 0:
        write_corner_case_results_xlsx(x_cc34_safety[:, 0], y_cc34, y_cc34_pred, 'cc34', 'SMOTE_Aug', None, None)

    if x_cc40_data.size > 0:
        write_corner_case_results_xlsx(x_cc40_safety[:, 0], y_cc40, y_cc40_pred, 'cc40', 'SMOTE_Aug', None, None)

    if x_cc41_data.size > 0:
        write_corner_case_results_xlsx(x_cc41_safety[:, 0], y_cc41, y_cc41_pred, 'cc41', 'SMOTE_Aug', None, None)

    if x_cc42_data.size > 0:
        write_corner_case_results_xlsx(x_cc42_safety[:, 0], y_cc42, y_cc42_pred, 'cc42', 'SMOTE_Aug', None, None)

    if x_cc43_data.size > 0:
        write_corner_case_results_xlsx(x_cc43_safety[:, 0], y_cc43, y_cc43_pred, 'cc43', 'SMOTE_Aug', None, None)
    
    precision = np.vstack(precision)
    recall = np.vstack(recall)
    f1 = np.vstack(f1)
    metrics_report(acc, precision, recall, f1)
