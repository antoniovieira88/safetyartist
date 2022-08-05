# Safety ArtISt: Workaround to avoid NumPy importing issues when using Keras and TensorFlow together on an Anaconda environment.
import os

from regex import I
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1'

from keras.utils.np_utils import to_categorical
from sklearn.model_selection import StratifiedKFold

from base_model import *
from dataset_utils.read_MIT_dataset import *
from ensamble.fusion_methods import *
from ensamble.umce import *
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

    # List of the number of UMCE elements per fold
    num_classifiers_folds = []

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
        # from "x_train" and "x_test". It is performed here so as to deliver pure heartbeat data to the classifiers that will
        # be trained as part of the UMCE.
        x_train, x_test, x_safety_train, x_safety_test = filterSafetyData(x_train, x_test)

        # prepare data for training        

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
        umce = MuticlassUMCE(sample_base_model, avrg_fusion)
        umce.fit(x_train, y_train)

        # Safety ArtISt - Save the number of classifiers per fold for printing the corner case reports
        num_classifiers_folds.append(umce.get_num_classifiers())

        # evaluate metrics
        y_pred = umce.predict(x_test)
        # Safety ArtISt - Updated the call of "metrics_values" to include the generation of a CSV report with the results
        a, p, r, f = metrics_values(y_pred, y_test, 'holdout_test', 'UMCE_Fold' + str(fold_number + 1).zfill(2))
        acc.append(a)
        precision.append(p)
        recall.append(r)
        f1.append(f)

        # Safety ArtISt - Evaluate corner cases tests and compile their results on the arrays for all folds and for each UMCE element
        # Calculations are performed only to the non-null sets of corner cases
        # a) 0 similar to 1
        if x_cc01_data.size > 0:
            y_cc01_pred.append(umce.predict(x_cc01_data))
        
        # b) 1 similar to 0
        if x_cc10_data.size > 0:
            y_cc10_pred.append(umce.predict(x_cc10_data))

        # c) 0 similar to 2
        if x_cc02_data.size > 0:
            y_cc02_pred.append(umce.predict(x_cc02_data))

        # d) 2 similar to 0
        if x_cc20_data.size > 0:
            y_cc20_pred.append(umce.predict(x_cc20_data))

        # e) 0 similar to 3
        if x_cc03_data.size > 0:
            y_cc03_pred.append(umce.predict(x_cc03_data))

        # f) 3 similar to 0
        if x_cc30_data.size > 0:
            y_cc30_pred.append(umce.predict(x_cc30_data))

        # g) 0 similar to 4
        if x_cc04_data.size > 0:
            y_cc04_pred.append(umce.predict(x_cc04_data))

        # h) 4 similar to 0
        if x_cc40_data.size > 0:
            y_cc40_pred.append(umce.predict(x_cc40_data))

        # i) 1 similar to 2
        if x_cc12_data.size > 0:
            y_cc12_pred.append(umce.predict(x_cc12_data))

        # j) 2 similar to 1
        if x_cc21_data.size > 0:
            y_cc21_pred.append(umce.predict(x_cc21_data))

        # k) 1 similar to 3
        if x_cc13_data.size > 0:
            y_cc13_pred.append(umce.predict(x_cc13_data))

        # l) 3 similar to 1
        if x_cc31_data.size > 0:
            y_cc31_pred.append(umce.predict(x_cc31_data))

        # m) 1 similar to 4 - empty
        if x_cc14_data.size > 0:
            y_cc14_pred.append(umce.predict(x_cc14_data))

        # n) 4 similar to 1
        if x_cc41_data.size > 0:
            y_cc41_pred.append(umce.predict(x_cc41_data))

        # o) 2 similar to 3
        if x_cc23_data.size > 0:
            y_cc23_pred.append(umce.predict(x_cc23_data))

        # p) 3 similar to 2
        if x_cc32_data.size > 0:
            y_cc32_pred.append(umce.predict(x_cc32_data))

        # q) 2 similar to 4
        if x_cc24_data.size > 0:
            y_cc24_pred.append(umce.predict(x_cc24_data))

        # r) 4 similar to 2
        if x_cc42_data.size > 0:
            y_cc42_pred.append(umce.predict(x_cc42_data))

        # s) 3 similar to 4
        if x_cc34_data.size > 0:
            y_cc34_pred.append(umce.predict(x_cc34_data))

        # t) 4 similar to 3
        if x_cc43_data.size > 0:
            y_cc43_pred.append(umce.predict(x_cc43_data))    

        # Safety ArtISt - Prints reports for all 20 possible types of corner cases every 5 folds and resets the corresponding
        # 'y_ccXX_pred' and 'num_classifiers_folds' after each report is printed.
        # Splitting the report printing was necessary to avoid RAM overflow on the Dell Inspiron N4010 notebook
        # As per testes carried out in August 2nd and 3rd, 2022, the running of this experiment crashes the machine
        # due to RAM overflow after accumulating the results of 8 folds.
        if fold_number == 4 or fold_number == 9:

            # Write reports for all 20 possible types of corner cases
            if x_cc01_data.size > 0:
                write_corner_case_results_xlsx(x_cc01_safety[:, 0], y_cc01, y_cc01_pred, 'cc01', 'UMCE', num_classifiers_folds, fold_number)
    
            if x_cc02_data.size > 0:
                write_corner_case_results_xlsx(x_cc02_safety[:, 0], y_cc02, y_cc02_pred, 'cc02', 'UMCE', num_classifiers_folds, fold_number)
    
            if x_cc03_data.size > 0:
                write_corner_case_results_xlsx(x_cc03_safety[:, 0], y_cc03, y_cc03_pred, 'cc03', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc04_data.size > 0:
                write_corner_case_results_xlsx(x_cc04_safety[:, 0], y_cc04, y_cc04_pred, 'cc04', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc10_data.size > 0:
                write_corner_case_results_xlsx(x_cc10_safety[:, 0], y_cc10, y_cc10_pred, 'cc10', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc12_data.size > 0:
                write_corner_case_results_xlsx(x_cc12_safety[:, 0], y_cc12, y_cc12_pred, 'cc12', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc13_data.size > 0:
                write_corner_case_results_xlsx(x_cc13_safety[:, 0], y_cc13, y_cc13_pred, 'cc13', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc14_data.size > 0:
                write_corner_case_results_xlsx(x_cc14_safety[:, 0], y_cc14, y_cc14_pred, 'cc14', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc20_data.size > 0:
                write_corner_case_results_xlsx(x_cc20_safety[:, 0], y_cc20, y_cc20_pred, 'cc20', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc21_data.size > 0:
                write_corner_case_results_xlsx(x_cc21_safety[:, 0], y_cc21, y_cc21_pred, 'cc21', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc23_data.size > 0:
                write_corner_case_results_xlsx(x_cc23_safety[:, 0], y_cc23, y_cc23_pred, 'cc23', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc24_data.size > 0:
                write_corner_case_results_xlsx(x_cc24_safety[:, 0], y_cc24, y_cc24_pred, 'cc24', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc30_data.size > 0:
                write_corner_case_results_xlsx(x_cc30_safety[:, 0], y_cc30, y_cc30_pred, 'cc30', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc31_data.size > 0:
                write_corner_case_results_xlsx(x_cc31_safety[:, 0], y_cc31, y_cc31_pred, 'cc31', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc32_data.size > 0:
                write_corner_case_results_xlsx(x_cc32_safety[:, 0], y_cc32, y_cc32_pred, 'cc32', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc34_data.size > 0:
                write_corner_case_results_xlsx(x_cc34_safety[:, 0], y_cc34, y_cc34_pred, 'cc34', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc40_data.size > 0:
                write_corner_case_results_xlsx(x_cc40_safety[:, 0], y_cc40, y_cc40_pred, 'cc40', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc41_data.size > 0:
                write_corner_case_results_xlsx(x_cc41_safety[:, 0], y_cc41, y_cc41_pred, 'cc41', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc42_data.size > 0:
                write_corner_case_results_xlsx(x_cc42_safety[:, 0], y_cc42, y_cc42_pred, 'cc42', 'UMCE', num_classifiers_folds, fold_number)

            if x_cc43_data.size > 0:
                write_corner_case_results_xlsx(x_cc43_safety[:, 0], y_cc43, y_cc43_pred, 'cc43', 'UMCE', num_classifiers_folds, fold_number)

            # Reset all 'y_ccXX_pred' and 'num_classifiers_folds'
            # List of arrays to store the results of the corner cases analyses for each cross-validation fold
            (y_cc01_pred, y_cc10_pred, y_cc02_pred,
            y_cc20_pred, y_cc03_pred, y_cc30_pred,
            y_cc04_pred, y_cc40_pred, y_cc12_pred,
            y_cc21_pred, y_cc13_pred, y_cc31_pred,
            y_cc14_pred, y_cc41_pred, y_cc23_pred,
            y_cc32_pred, y_cc24_pred, y_cc42_pred,
            y_cc34_pred, y_cc43_pred)               = [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []

            # List of the number of UMCE elements per fold
            num_classifiers_folds = []

        print("\n\n")    

    precision = np.vstack(precision)
    recall = np.vstack(recall)
    f1 = np.vstack(f1)
    metrics_report(acc, precision, recall, f1)
