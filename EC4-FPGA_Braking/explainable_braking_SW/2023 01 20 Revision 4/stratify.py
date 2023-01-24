import pandas as pd
from numpy import ceil

# Apenas para testes
def pre_processing(address):
    dataColumns = ["Distância Ruidosa", "Velocidade Ruidosa", "Capacidade de Frenagem Ruidosa",
                    "Decisão"]
    
    dataset = pd.read_csv(address, header = None, names = dataColumns)
    return dataset

# Gerar um split de treino e teste, note que há intersecção entre treino e teste.
def train_test_split_stratified(data, test_size, prop_zeros, random_state, shuffle): # Se prop_zeros = 0.6 então 60% dos dados de treinamento são zeros
    # Calcula o número de elementos no dataset
    n_data = len(data)

    # Calcula o número de elementos dedicados para teste
    n_data_train = ceil((1-test_size)*n_data)

    # Calcula o número de saídas iguais a 1 no dataset de entrada
    n_data_ones = len(data[data['Decisão'] == 1])

    # Calcula proporção mínima de zeros
    prop_zeros_min = (1-((n_data_ones)/(ceil((1-test_size)*n_data)))).round(4)

    # Retorna erro se a proporção mínima não é satisfeita
    if(prop_zeros < prop_zeros_min):
        raise ValueError(f"For test_size = {test_size*100}%, prop_zeros must be {prop_zeros_min*100}% or higher")


    # Calcula número de zeros e uns que devem estar presentes na partição de treino
    n_data_train_ones = ceil((1-prop_zeros)*n_data_train).astype(int)
    n_data_train_zeros = (n_data_train - n_data_train_ones).astype(int)

    # Amostra os "n" 1's necessários aleatoriamente dentro do dataset de entrada
    data_one_train = data[data['Decisão'] == 1].sample(n = n_data_train_ones, random_state = random_state)

    # Amostra os "n" 0's necessários aleatoriamente dentro do dataset de entrada
    data_zero_train = data[data['Decisão'] == 0].sample(n = n_data_train_zeros, random_state = random_state)

    # Junta os zeros e uns para formar a partição de treino
    data_train = pd.merge(data_one_train, data_zero_train, how = 'outer')

    # Mistura os zeros e uns, se assim desejado
    if(shuffle == True):
        data_train = data_train.sample(frac = 1, random_state = random_state)
    
    # Separa entrada e saída
    data_input_train = data_train.drop(columns = ['Decisão'])
    data_output_train = data_train[['Decisão']]

    # Amostra uma parcela "test_size" do dataset de entrada
    data_test = data.sample(frac = test_size, random_state = random_state)
    
    # Separa entrada e saída
    data_input_test = data_test.drop(columns = ['Decisão'])
    data_output_test = data_test[['Decisão']]

    # Devolve as partições de treino e teste
    return data_input_train, data_input_test, data_output_train, data_output_test

def StratifyData(data, frac, prop_zeros, random_state, shuffle):
    # Calcula o número de elementos no dataset de entrada
    n_data = len(data)

    # Calcula o número de elementos no dataset estratificado
    n_data_stratified = ceil(frac*n_data)

    # Calcula o número de saídas iguais a 1 no dataset de entrada
    n_data_ones = len(data[data['Decisão'] == 1])
    
    # Calcula proporção mínima de zeros
    prop_zeros_min = (1-((n_data_ones)/(ceil(frac*n_data)))).round(4)

    # Retorna erro se a proporção mínima não é satisfeita
    if(prop_zeros < prop_zeros_min):
        raise ValueError(f"For frac = {frac*100}%, prop_zeros must be {prop_zeros_min*100}% or higher")

    # Calcula número de zeros e uns que devem estar presentes no dataset estratificado
    n_data_stratified_ones = ceil((1-prop_zeros)*n_data_stratified).astype(int)
    n_data_stratified_zeros = (n_data_stratified - n_data_stratified_ones).astype(int)

    # Amostra os "n" zeros e uns do dataset de entrada aletoriamente
    data_one_stratified = data[data['Decisão'] == 1].sample(n = n_data_stratified_ones, random_state = random_state).reset_index(drop=True)
    data_zero_stratified = data[data['Decisão'] == 0].sample(n = n_data_stratified_zeros, random_state = random_state).reset_index(drop=True)

    # Junta os zeros e uns para formar o dataset estratificado
    data_stratified = pd.merge(data_one_stratified, data_zero_stratified, how = 'outer')

    # Mistura os zeros e uns, se assim desejado
    if(shuffle == True):
        data_stratified = data_stratified.sample(frac = 1, random_state = random_state)

    # Devolve a base de dados estratificada
    return data_stratified.reset_index(drop=True)

# Teste para ver dispersão dos 1's dentro do dataset
# pp_dataset = pre_processing("./Dataset/DatasetT&V.csv")


# pp_dataset_ones = pp_dataset[pp_dataset['Decisão'] == 1]
# pp_dataset_ones_index = pp_dataset_ones.index.tolist() 

# dist_max = 1

# for k in range(len(pp_dataset_ones_index)-1):
#     dist = pp_dataset_ones_index[k+1] - pp_dataset_ones_index[k]

#     if(dist_max < dist):
#         dist_max = dist
#         print(f"Indíce {k+1} distância aumenta para {dist}")

# print("Quantidade de 'Decisão = 1' no dataset:", len(pp_dataset_ones))

# print("\n ************************************************************************************* \n")
# print(pp_dataset_ones)
# print("\n ************************************************************************************* \n")    

# pp_dataset_zeros = pp_dataset[pp_dataset['Decisão'] == 0]

