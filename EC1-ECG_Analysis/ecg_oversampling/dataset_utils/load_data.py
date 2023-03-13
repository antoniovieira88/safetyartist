import pandas as pd

from dataset_utils.utils import *


def load_data(filename):
    # Safety ArtISt correction: Reading CSV files originally omitted the first line, which was considered a header.
    # This has been corrected by adding 'header=None' to the call of 'read_csv'.
    dataframe = pd.read_csv(filename, engine='python', header=None)
    dataset = dataframe.values
    return dataset.astype('float32')


def load_file(filename):
    train = load_data(filename)
    input = train[:, :-1]
    target = train[:, -1]

    return expand_dims(input, target)
