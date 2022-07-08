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

    # Testing code for debugging saUtils.py - START
    write_corner_case_csv(x_cc10_safety[:, 0], y_cc10, y_cc10, 'cc10', 'ResNet_Fold' + str(4)) 

    y_cc10_debug = np.copy(y_cc10)
    y_cc10_debug[0] = np.array([1, 0, 0, 0, 0])
    y_cc10_debug[1] = np.array([0, 0, 1, 0, 0])
    y_cc10_debug[2] = np.array([0, 0, 0, 1, 0])
    y_cc10_debug[3] = np.array([0, 0, 0, 0, 1])

    write_corner_case_csv(x_cc10_safety[:, 0], y_cc10, y_cc10_debug, 'cc10_debug', 'ResNet_Fold' + str(9)) 

    # Testing code for debugging saUtils.py - END

    sets_shapes_report(x, y)

    kf = StratifiedKFold(n_splits=10, shuffle=True, random_state=None)

    # Safety ArtISt: Replaced "x" with "x[:, :-22] to filter out the safety-related columns" from the input_shape
    # variable, which is used for defining the ResNet actual input shape. It shall be equal to (187, 1).
    input_shape = x[:, :-22].shape[1:]

    acc, precision, recall, f1 = [], [], [], []

    # Safety ArtISt: Included accuracy, precision, recall and f1-score metrics to assess the performance with corner cases on all folds
    # a) 0 similar to 1
    acc_cc01, precision_cc01, recall_cc01, f1_cc01 = [], [], [], []

    # b) 1 similar to 0
    acc_cc10, precision_cc10, recall_cc10, f1_cc10 = [], [], [], []

    # c) 0 similar to 2
    acc_cc02, precision_cc02, recall_cc02, f1_cc02 = [], [], [], []

    # d) 2 similar to 0
    acc_cc20, precision_cc20, recall_cc20, f1_cc20 = [], [], [], []

    # e) 0 similar to 3
    acc_cc03, precision_cc03, recall_cc03, f1_cc03 = [], [], [], []

    # f) 3 similar to 0
    acc_cc30, precision_cc30, recall_cc30, f1_cc30 = [], [], [], []

    # g) 0 similar to 4
    acc_cc04, precision_cc04, recall_cc04, f1_cc04 = [], [], [], []

    # h) 4 similar to 0
    acc_cc40, precision_cc40, recall_cc40, f1_cc40 = [], [], [], []

    # i) 1 similar to 2
    acc_cc12, precision_cc12, recall_cc12, f1_cc12 = [], [], [], []

    # j) 2 similar to 1
    acc_cc21, precision_cc21, recall_cc21, f1_cc21 = [], [], [], []

    # k) 1 similar to 3
    acc_cc13, precision_cc13, recall_cc13, f1_cc13 = [], [], [], []

    # l) 3 similar to 1
    acc_cc31, precision_cc31, recall_cc31, f1_cc31 = [], [], [], []

    # m) 1 similar to 4
    acc_cc14, precision_cc14, recall_cc14, f1_cc14 = [], [], [], []

    # n) 4 similar to 1
    acc_cc41, precision_cc41, recall_cc41, f1_cc41 = [], [], [], []

    # o) 2 similar to 3
    acc_cc23, precision_cc23, recall_cc23, f1_cc23 = [], [], [], []

    # p) 3 similar to 2
    acc_cc32, precision_cc32, recall_cc32, f1_cc32 = [], [], [], []

    # q) 2 similar to 4
    acc_cc24, precision_cc24, recall_cc24, f1_cc24 = [], [], [], []

    # r) 4 similar to 2
    acc_cc42, precision_cc42, recall_cc42, f1_cc42 = [], [], [], []

    # s) 3 similar to 4
    acc_cc34, precision_cc34, recall_cc34, f1_cc34 = [], [], [], []

    # t) 4 similar to 3
    acc_cc43, precision_cc43, recall_cc43, f1_cc43 = [], [], [], []

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

        # Safety ArtISt - Evaluate metrics of corner cases tests, compile them on the arrays for all folds and print the results on CSV files
        # a) 0 similar to 1
        y_cc01_pred = base_model.predict(x_cc01_data)
        a_cc01, p_cc01, r_cc01, f_cc01 = metrics_values(y_cc01_pred, y_cc01)
        acc_cc01.append(a_cc01)
        precision_cc01.append(p_cc01)
        recall_cc01.append(r_cc01)
        f1_cc01.append(f_cc01)
        write_corner_case_csv(x_cc01_safety[:, 0], y_cc01, y_cc01_pred, 'cc01', 'ResNet_Fold' + str(fold_number))
        
        # b) 1 similar to 0
        y_cc10_pred = base_model.predict(x_cc10_data)
        a_cc10, p_cc10, r_cc10, f_cc10 = metrics_values(y_cc10_pred, y_cc10)
        acc_cc10.append(a_cc10)
        precision_cc10.append(p_cc10)
        recall_cc10.append(r_cc10)
        f1_cc10.append(f_cc10)
        write_corner_case_csv(x_cc10_safety[:, 0], y_cc10, y_cc10_pred, 'cc10', 'ResNet_Fold' + str(fold_number))

        # c) 0 similar to 2
        y_cc02_pred = base_model.predict(x_cc02_data)
        a_cc02, p_cc02, r_cc02, f_cc02 = metrics_values(y_cc02_pred, y_cc02)
        acc_cc02.append(a_cc02)
        precision_cc02.append(p_cc02)
        recall_cc02.append(r_cc02)
        f1_cc02.append(f_cc02)
        write_corner_case_csv(x_cc02_safety[:, 0], y_cc02, y_cc02_pred, 'cc02', 'ResNet_Fold' + str(fold_number))

        # d) 2 similar to 0
        y_cc20_pred = base_model.predict(x_cc20_data)
        a_cc20, p_cc20, r_cc20, f_cc20 = metrics_values(y_cc20_pred, y_cc20)
        acc_cc20.append(a_cc20)
        precision_cc20.append(p_cc20)
        recall_cc20.append(r_cc20)
        f1_cc20.append(f_cc20)
        write_corner_case_csv(x_cc20_safety[:, 0], y_cc20, y_cc20_pred, 'cc20', 'ResNet_Fold' + str(fold_number))

        # e) 0 similar to 3
        y_cc03_pred = base_model.predict(x_cc03_data)
        a_cc03, p_cc03, r_cc03, f_cc03 = metrics_values(y_cc03_pred, y_cc03)
        acc_cc03.append(a_cc03)
        precision_cc03.append(p_cc03)
        recall_cc03.append(r_cc03)
        f1_cc03.append(f_cc03)
        write_corner_case_csv(x_cc03_safety[:, 0], y_cc03, y_cc03_pred, 'cc03', 'ResNet_Fold' + str(fold_number))

        # f) 3 similar to 0
        y_cc30_pred = base_model.predict(x_cc30_data)
        a_cc30, p_cc30, r_cc30, f_cc30 = metrics_values(y_cc30_pred, y_cc30)
        acc_cc30.append(a_cc30)
        precision_cc30.append(p_cc30)
        recall_cc30.append(r_cc30)
        f1_cc30.append(f_cc30)
        write_corner_case_csv(x_cc30_safety[:, 0], y_cc30, y_cc30_pred, 'cc30', 'ResNet_Fold' + str(fold_number))

        # g) 0 similar to 4
        y_cc04_pred = base_model.predict(x_cc04_data)
        a_cc04, p_cc04, r_cc04, f_cc04 = metrics_values(y_cc04_pred, y_cc04)
        acc_cc04.append(a_cc04)
        precision_cc04.append(p_cc04)
        recall_cc04.append(r_cc04)
        f1_cc04.append(f_cc04)
        write_corner_case_csv(x_cc04_safety[:, 0], y_cc04, y_cc04_pred, 'cc04', 'ResNet_Fold' + str(fold_number))

        # h) 4 similar to 0
        y_cc40_pred = base_model.predict(x_cc40_data)
        a_cc40, p_cc40, r_cc40, f_cc40 = metrics_values(y_cc40_pred, y_cc40)
        acc_cc40.append(a_cc40)
        precision_cc40.append(p_cc40)
        recall_cc40.append(r_cc40)
        f1_cc40.append(f_cc40)
        write_corner_case_csv(x_cc40_safety[:, 0], y_cc40, y_cc40_pred, 'cc40', 'ResNet_Fold' + str(fold_number))

        # i) 1 similar to 2
        y_cc12_pred = base_model.predict(x_cc12_data)
        a_cc12, p_cc12, r_cc12, f_cc12 = metrics_values(y_cc12_pred, y_cc12)
        acc_cc12.append(a_cc12)
        precision_cc12.append(p_cc12)
        recall_cc12.append(r_cc12)
        f1_cc12.append(f_cc12)
        write_corner_case_csv(x_cc12_safety[:, 0], y_cc12, y_cc12_pred, 'cc12', 'ResNet_Fold' + str(fold_number))

        # j) 2 similar to 1
        y_cc21_pred = base_model.predict(x_cc21_data)
        a_cc21, p_cc21, r_cc21, f_cc21 = metrics_values(y_cc21_pred, y_cc21)
        acc_cc21.append(a_cc21)
        precision_cc21.append(p_cc21)
        recall_cc21.append(r_cc21)
        f1_cc21.append(f_cc21)
        write_corner_case_csv(x_cc21_safety[:, 0], y_cc21, y_cc21_pred, 'cc21', 'ResNet_Fold' + str(fold_number))

        # k) 1 similar to 3
        y_cc13_pred = base_model.predict(x_cc13_data)
        a_cc13, p_cc13, r_cc13, f_cc13 = metrics_values(y_cc13_pred, y_cc13)
        acc_cc13.append(a_cc13)
        precision_cc13.append(p_cc13)
        recall_cc13.append(r_cc13)
        f1_cc13.append(f_cc13)
        write_corner_case_csv(x_cc13_safety[:, 0], y_cc13, y_cc13_pred, 'cc13', 'ResNet_Fold' + str(fold_number))

        # l) 3 similar to 1
        y_cc31_pred = base_model.predict(x_cc31_data)
        a_cc31, p_cc31, r_cc31, f_cc31 = metrics_values(y_cc31_pred, y_cc31)
        acc_cc31.append(a_cc31)
        precision_cc31.append(p_cc31)
        recall_cc31.append(r_cc31)
        f1_cc31.append(f_cc31)
        write_corner_case_csv(x_cc31_safety[:, 0], y_cc31, y_cc31_pred, 'cc31', 'ResNet_Fold' + str(fold_number))

        # m) 1 similar to 4
        y_cc14_pred = base_model.predict(x_cc14_data)
        a_cc14, p_cc14, r_cc14, f_cc14 = metrics_values(y_cc14_pred, y_cc14)
        acc_cc14.append(a_cc14)
        precision_cc14.append(p_cc14)
        recall_cc14.append(r_cc14)
        f1_cc14.append(f_cc14)
        write_corner_case_csv(x_cc14_safety[:, 0], y_cc14, y_cc14_pred, 'cc14', 'ResNet_Fold' + str(fold_number))

        # n) 4 similar to 1
        y_cc41_pred = base_model.predict(x_cc41_data)
        a_cc41, p_cc41, r_cc41, f_cc41 = metrics_values(y_cc41_pred, y_cc41)
        acc_cc41.append(a_cc41)
        precision_cc41.append(p_cc41)
        recall_cc41.append(r_cc41)
        f1_cc41.append(f_cc41)
        write_corner_case_csv(x_cc41_safety[:, 0], y_cc41, y_cc41_pred, 'cc41', 'ResNet_Fold' + str(fold_number))

        # o) 2 similar to 3
        y_cc23_pred = base_model.predict(x_cc23_data)
        a_cc23, p_cc23, r_cc23, f_cc23 = metrics_values(y_cc23_pred, y_cc23)
        acc_cc23.append(a_cc23)
        precision_cc23.append(p_cc23)
        recall_cc23.append(r_cc23)
        f1_cc23.append(f_cc23)
        write_corner_case_csv(x_cc23_safety[:, 0], y_cc23, y_cc23_pred, 'cc23', 'ResNet_Fold' + str(fold_number))

        # p) 3 similar to 2
        y_cc32_pred = base_model.predict(x_cc32_data)
        a_cc32, p_cc32, r_cc32, f_cc32 = metrics_values(y_cc32_pred, y_cc32)
        acc_cc32.append(a_cc32)
        precision_cc32.append(p_cc32)
        recall_cc32.append(r_cc32)
        f1_cc32.append(f_cc32)
        write_corner_case_csv(x_cc32_safety[:, 0], y_cc32, y_cc32_pred, 'cc32', 'ResNet_Fold' + str(fold_number))

        # q) 2 similar to 4
        y_cc24_pred = base_model.predict(x_cc24_data)
        a_cc24, p_cc24, r_cc24, f_cc24 = metrics_values(y_cc24_pred, y_cc24)
        acc_cc24.append(a_cc24)
        precision_cc24.append(p_cc24)
        recall_cc24.append(r_cc24)
        f1_cc24.append(f_cc24)
        write_corner_case_csv(x_cc24_safety[:, 0], y_cc24, y_cc24_pred, 'cc24', 'ResNet_Fold' + str(fold_number))

        # r) 4 similar to 2
        y_cc42_pred = base_model.predict(x_cc42_data)
        a_cc42, p_cc42, r_cc42, f_cc42 = metrics_values(y_cc42_pred, y_cc42)
        acc_cc42.append(a_cc42)
        precision_cc42.append(p_cc42)
        recall_cc42.append(r_cc42)
        f1_cc42.append(f_cc42)
        write_corner_case_csv(x_cc42_safety[:, 0], y_cc42, y_cc42_pred, 'cc42', 'ResNet_Fold' + str(fold_number))

        # s) 3 similar to 4
        y_cc34_pred = base_model.predict(x_cc34_data)
        a_cc34, p_cc34, r_cc34, f_cc34 = metrics_values(y_cc34_pred, y_cc34)
        acc_cc34.append(a_cc34)
        precision_cc34.append(p_cc34)
        recall_cc34.append(r_cc34)
        f1_cc34.append(f_cc34)
        write_corner_case_csv(x_cc34_safety[:, 0], y_cc34, y_cc34_pred, 'cc34', 'ResNet_Fold' + str(fold_number))

        # t) 4 similar to 3
        y_cc43_pred = base_model.predict(x_cc43_data)
        a_cc43, p_cc43, r_cc43, f_cc43 = metrics_values(y_cc43_pred, y_cc43)
        acc_cc43.append(a_cc43)
        precision_cc43.append(p_cc43)
        recall_cc43.append(r_cc43)
        f1_cc43.append(f_cc43)
        write_corner_case_csv(x_cc43_safety[:, 0], y_cc43, y_cc43_pred, 'cc43', 'ResNet_Fold' + str(fold_number))

        print("\n\n")

    # Safety ArtISt - Stacking of accuracy was not performed by Kozal and Ksieniewicz
    acc = np.vstack(acc)

    precision = np.vstack(precision)
    recall = np.vstack(recall)
    f1 = np.vstack(f1)
    metrics_report(acc, precision, recall, f1)

    # Safety ArtISt - Stacking of metrics for the corner cases
    # a) 0 similar to 1
    acc_cc01 = np.vstack(acc_cc01)
    precision_cc01 = np.vstack(precision_cc01)
    recall_cc01 = np.vstack(recall_cc01)
    f1_cc01 = np.vstack(f1_cc01)
    print("Results for Corner Case 0 --> 1:")
    metrics_report(acc_cc01, precision_cc01, recall_cc01, f1_cc01)

    # b) 1 similar to 0
    acc_cc10 = np.vstack(acc_cc10)
    precision_cc10 = np.vstack(precision_cc10)
    recall_cc10 = np.vstack(recall_cc10)
    f1_cc10 = np.vstack(f1_cc10)
    print("Results for Corner Case 1 --> 0:")
    metrics_report(acc_cc10, precision_cc10, recall_cc10, f1_cc10)

    # c) 0 similar to 2
    acc_cc02 = np.vstack(acc_cc02)
    precision_cc02 = np.vstack(precision_cc02)
    recall_cc02 = np.vstack(recall_cc02)
    f1_cc02 = np.vstack(f1_cc02)
    print("Results for Corner Case 0 --> 2:")
    metrics_report(acc_cc02, precision_cc02, recall_cc02, f1_cc02)

    # d) 2 similar to 0
    acc_cc20 = np.vstack(acc_cc20)
    precision_cc20 = np.vstack(precision_cc20)
    recall_cc20 = np.vstack(recall_cc20)
    f1_cc20 = np.vstack(f1_cc20)
    print("Results for Corner Case 2 --> 0:")
    metrics_report(acc_cc20, precision_cc20, recall_cc20, f1_cc20)

    # e) 0 similar to 3
    acc_cc03 = np.vstack(acc_cc03)
    precision_cc03 = np.vstack(precision_cc03)
    recall_cc03 = np.vstack(recall_cc03)
    f1_cc03 = np.vstack(f1_cc03)
    print("Results for Corner Case 0 --> 3:")
    metrics_report(acc_cc03, precision_cc03, recall_cc03, f1_cc03)

    # f) 3 similar to 0
    acc_cc30 = np.vstack(acc_cc30)
    precision_cc30 = np.vstack(precision_cc30)
    recall_cc30 = np.vstack(recall_cc30)
    f1_cc30 = np.vstack(f1_cc30)
    print("Results for Corner Case 3 --> 0:")
    metrics_report(acc_cc30, precision_cc30, recall_cc30, f1_cc30)

    # g) 0 similar to 4
    acc_cc04 = np.vstack(acc_cc04)
    precision_cc04 = np.vstack(precision_cc04)
    recall_cc04 = np.vstack(recall_cc04)
    f1_cc04 = np.vstack(f1_cc04)
    print("Results for Corner Case 0 --> 4:")
    metrics_report(acc_cc04, precision_cc04, recall_cc04, f1_cc04)

    # h) 4 similar to 0
    acc_cc40 = np.vstack(acc_cc40)
    precision_cc40 = np.vstack(precision_cc40)
    recall_cc40 = np.vstack(recall_cc40)
    f1_cc40 = np.vstack(f1_cc40)
    print("Results for Corner Case 4 --> 0:")
    metrics_report(acc_cc40, precision_cc40, recall_cc40, f1_cc40)

    # i) 1 similar to 2
    acc_cc12 = np.vstack(acc_cc12)
    precision_cc12 = np.vstack(precision_cc12)
    recall_cc12 = np.vstack(recall_cc12)
    f1_cc12 = np.vstack(f1_cc12)
    print("Results for Corner Case 1 --> 2:")
    metrics_report(acc_cc12, precision_cc12, recall_cc12, f1_cc12)

    # j) 2 similar to 1
    acc_cc21 = np.vstack(acc_cc21)
    precision_cc21 = np.vstack(precision_cc21)
    recall_cc21 = np.vstack(recall_cc21)
    f1_cc21 = np.vstack(f1_cc21)
    print("Results for Corner Case 2 --> 1:")
    metrics_report(acc_cc21, precision_cc21, recall_cc21, f1_cc21)

    # k) 1 similar to 3
    acc_cc13 = np.vstack(acc_cc13)
    precision_cc13 = np.vstack(precision_cc13)
    recall_cc13 = np.vstack(recall_cc13)
    f1_cc13 = np.vstack(f1_cc13)
    print("Results for Corner Case 1 --> 3:")
    metrics_report(acc_cc13, precision_cc13, recall_cc13, f1_cc13)

    # l) 3 similar to 1
    acc_cc31 = np.vstack(acc_cc31)
    precision_cc31 = np.vstack(precision_cc31)
    recall_cc31 = np.vstack(recall_cc31)
    f1_cc31 = np.vstack(f1_cc31)
    print("Results for Corner Case 3 --> 1:")
    metrics_report(acc_cc31, precision_cc31, recall_cc31, f1_cc31)

    # m) 1 similar to 4
    acc_cc14 = np.vstack(acc_cc14)
    precision_cc14 = np.vstack(precision_cc14)
    recall_cc14 = np.vstack(recall_cc14)
    f1_cc14 = np.vstack(f1_cc14)
    print("Results for Corner Case 1 --> 4:")
    metrics_report(acc_cc14, precision_cc14, recall_cc14, f1_cc14)

    # n) 4 similar to 1
    acc_cc41 = np.vstack(acc_cc41)
    precision_cc41 = np.vstack(precision_cc41)
    recall_cc41 = np.vstack(recall_cc41)
    f1_cc41 = np.vstack(f1_cc41)
    print("Results for Corner Case 4 --> 1:")
    metrics_report(acc_cc41, precision_cc41, recall_cc41, f1_cc41)

    # o) 2 similar to 3
    acc_cc23 = np.vstack(acc_cc23)
    precision_cc23 = np.vstack(precision_cc23)
    recall_cc23 = np.vstack(recall_cc23)
    f1_cc23 = np.vstack(f1_cc23)
    print("Results for Corner Case 2 --> 3:")
    metrics_report(acc_cc23, precision_cc23, recall_cc23, f1_cc23)

    # p) 3 similar to 2
    acc_cc32 = np.vstack(acc_cc32)
    precision_cc32 = np.vstack(precision_cc32)
    recall_cc32 = np.vstack(recall_cc32)
    f1_cc32 = np.vstack(f1_cc32)
    print("Results for Corner Case 3 --> 2:")
    metrics_report(acc_cc32, precision_cc32, recall_cc32, f1_cc32)

    # q) 2 similar to 4
    acc_cc24 = np.vstack(acc_cc24)
    precision_cc24 = np.vstack(precision_cc24)
    recall_cc24 = np.vstack(recall_cc24)
    f1_cc24 = np.vstack(f1_cc24)
    print("Results for Corner Case 2 --> 4:")
    metrics_report(acc_cc24, precision_cc24, recall_cc24, f1_cc24)

    # r) 4 similar to 2
    acc_cc42 = np.vstack(acc_cc42)
    precision_cc42 = np.vstack(precision_cc42)
    recall_cc42 = np.vstack(recall_cc42)
    f1_cc42 = np.vstack(f1_cc42)
    print("Results for Corner Case 4 --> 2:")
    metrics_report(acc_cc42, precision_cc42, recall_cc42, f1_cc42)

    # s) 3 similar to 4
    acc_cc34 = np.vstack(acc_cc34)
    precision_cc34 = np.vstack(precision_cc23)
    recall_cc34 = np.vstack(recall_cc34)
    f1_cc34 = np.vstack(f1_cc34)
    print("Results for Corner Case 3 --> 4:")
    metrics_report(acc_cc34, precision_cc34, recall_cc34, f1_cc34)

    # t) 4 similar to 3
    acc_cc43 = np.vstack(acc_cc43)
    precision_cc42 = np.vstack(precision_cc43)
    recall_cc43 = np.vstack(recall_cc43)
    f1_cc43 = np.vstack(f1_cc43)
    print("Results for Corner Case 4 --> 3:")
    metrics_report(acc_cc43, precision_cc43, recall_cc43, f1_cc43)