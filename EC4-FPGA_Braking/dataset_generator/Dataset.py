###########################################################################################################################
#
# Antonio Vieira da Silva Neto - NUSP  5690149 - Doutorando em Ciências
# Henrique Lefundes da Silva   - NUSP 11808280 - Pesquisador de Iniciação Científica e Graduando em Engenharia Elétrica
#
# Escola Politécnica da Universidade de São Paulo
# Programa de Pós-Graduação em Engenharia Elétrica
# Departamento de Engenharia de Computação e Sistemas Digitais
# Área de Concentração: Confiabilidade e Segurança
#
# Tese de Doutorado: Safety ArtISt: Um Método para a Garantia de Segurança Crítica de Sistemas com Inteligência Artificial
#
# Estudo de Caso 4 - Sistema de Controle de Frenagem de Veículos
#
# Arquivo para Geração de Base de Dados Simulada
#
###########################################################################################################################

###########################################################################################################################
#
# Tabela de Controle de Versões do Código
#
#--------|-------------------|------------------------------|--------------------------------------------------------------
# Versão | Data (dd/mm/aaaa) | Autor                        | Descrição da Versão
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   01   |    26/05/2022     | Henrique Lefundes da Silva   | Versão inicial.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   02   |    02/06/2022     | Henrique Lefundes da Silva   | Versão atualizada incluindo mecanismos de depuração em Excel.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   03   |    08/06/2022     | Henrique Lefundes da Silva   | Versão atualizada incluindo ruídos pseudoaleatórios aos sen-
#        |                   |                              | sores de distância e velocidade e melhorias no tempo de pro-
#        |                   |                              | cessamento e nos mecanismos de depuração.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   04   |    09/06/2022     | Antonio Vieira da Silva Neto | Versão atualizada com semente entrópica do Sistema Operacio-
#        |                   |                              | nal para os sorteios pseudoaleatórios, correção (sem impacto
#        |                   |                              | prático) na equação de "DS" e novas melhorias nos mecanismos
#        |                   |                              | de depuração.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   05   |    13/06/2022     | Antonio Vieira da Silva Neto | Problemas encontrados após verificação exaustiva dos resul-
#        |                   |                              | tados:
#        |                   |                              | a) A massa do trem era sempre considerada "zero", independen-
#        |                   |                              | temente do valor atribuído inicialmente a ela. --> Corrigido
#        |                   |                              | nesta revisão forçando a atualização da variável global "M".
#        |                   |                              | b) A fórmula de cálculo do erro de distância está incorreta.
#        |                   |                              | Faltou incluir um desvio constante de 0,87m em todas as dis-
#        |                   |                              | tâncias e limitar o sorteio do erro aleatório a até duas 
#        |                   |                              | vezes o desvio padrão.
#        |                   |                              | c) A fórmula do cálculo do erro de velocidade está incorreta.
#        |                   |                              | Faltou limiar o sorteio do erro aleatório a até duas vezes o
#        |                   |                              | desvio padrão.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   06   |    14/06/2022     | Henrique Lefundes da Silva   | Correções dos problemas descritos na revisão 5.
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   07   |    21/06/2022     | Antonio Vieira da Silva Neto | Correções na fórmula de cálculo de "devpadDistancia" para
#        |                   |                              | distâncias maiores do que 30m. A parcela "0,5*TCY" estava
#        |                   |                              | indevidamente grafada como "0,05*TCY".
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   08   |    12/10/2022     | Henrique Lefundes da Silva   | Adição de novas funções; Possibilidade de gerar bases de
#        |                   |                              | dados estratificadas, com a proporção de zeros desejada.
#        |                   |                              | Alterações nas funções existentes; Documentação das fun-
#        |                   |                              | ções presentes no programa
#--------|-------------------|------------------------------|--------------------------------------------------------------
#   09   |    28/10/2022     | Henrique Lefundes da Silva   | Refatoração do código para melhoria de desempenho (proces-
#        |                   |                              | samento de dados como tabelas NumPy e geração de dataframes
#        |                   |                              | apenas ao final), implementação de comentários gerais de AVSN 
#        |                   |                              | (menu para geração configurável de dados, melhoria de comen-
#        |                   |                              | tários no código).
#--------|-------------------|------------------------------|--------------------------------------------------------------

###########################################################################################################################

import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1' #Evita problemas de versão do NumPy com Conda

import time
import pandas as pd
import numpy as np
from numpy import ceil, floor
np.random.seed(None)

distance = np.arange(start=0, stop=2010, step=10)   #Cria vetor distancia [m]
speed = np.arange(start=0, stop=28.5, step=0.5)     #Cria vetor velocidade [m/s]
brake = [1.395, 1.1625, 0.93, 0.78, 0.65]           #Cria vetor de desaceleracao (baseado nos valores de AEB da tabela) [m/s^2] 

TCY = 0.5
AH = 1.12       #Aceleracao com 
                #-- baixa aderencia = 0.84 
                # -- aderencia normal = 1.12 [m/s^2]               
M = 0           #Massa do trem  
                #-- com 8 passageiros/m^2 = 382617 
                #-- com 6 passageiros/m^2 = 348687.25
                #-- com 4 passageiros/m^2 = 314757.5
                #-- com 2 passageiros/m^2 = 280827.75
                #-- sem passageiros = 246898 [kg]

MRI = 24689     #Massa Equiv ao Momento de Inercia do Trem [kg]
AEB = 0         #Desaceleracao dos freios de emergencia para diferentes aderencias e falhas no freio [m/s^2] -- Utilizar os valores do vetor brake
VW = 4          #Velocidade do Vento na via [m/s]
GR = 0          #Máximo gradiente da Via ==> nao ha inclinacao no plano
g = 9.81        #Aceleracao da gravidade [m/s^2]
ATS = 9.898     #Area da Seccao Transversal do carro [m^2]
RHO = 1.2       #Densidade do ar na via [kg/m^3]
Cd = 1.1        #Coeficiente de Arrasto Aerodinamico
VA = 0          #Velocidade do Trem antes da Hiperaceleracao [m/s] -- Utilizar os valores do vetor speed
TH = 0.7        #Tempo de hiperaceleracao [s]
V = VA          #Velocidade instantânea do trem (pior caso)
TC = 1.5        #Tempo de duracao do corte de tracao sem aplicacao de freios [s]
T50 = 0.5       #Tempo de duracao da aplicacao do freio com metade da capacidade [s]

############# Equacoes utilizadas ##############

# AW = (0.5*RHO*Cd*ATS*((VW-V)**2))/(M+MRI)
# AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
# VH = VA + (AH+AW-AG)*TH
# VC = VH + (AW-AG)*TC
# V50 = VC + (0.5*AEB+AW-AG)*T50
# DS = ((VA*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*AEB+AW-AG)*T50**2))+(V50**2/(2*(AEB+AW-AG)))

################################################

def cls():
    os.system('cls' if os.name == 'nt' else 'clear')

def write_dataset(data, name = "Dataset"):
    """
    Write the data in a .csv and .xlsx 
    
    Parameters
    ----------
    data : pandas Dataframe
        The data that will be written
    name : string, default="Dataset"
        File's name, it will also generate a .csv file with the suffix "Debug"
    """
    print("---- Writing Dataset ----")

    dataCompressed = data[['Distancia Ruidosa', 'Velocidade Ruidosa', 'Capacidade de Frenagem Ruidosa', 'Decisao']]

    print("Writing .csv file...", end = '', flush=True)
    if(debug_mode == True):
        data.to_csv(name + "Debug.csv", header = False, index = False) # Cria o dataframe completo em csv
    print("OK")
    dataCompressed.to_csv(name + ".csv", header = False, index = False) # Cria o dataframe reduzido em csv

    if(generate_xlsx == True):
        print("Writing .xlsx file...", end = '', flush=True)
        with pd.ExcelWriter(name + ".xlsx") as writer:  # Cria duas abas em arquivo Excel: uma com o dataframe reduzido e, outra, com o dataframe completo.
            if(debug_mode == True):
                data.to_excel(writer, sheet_name = name + "Debug", index = False)
            dataCompressed.to_excel(writer, sheet_name = name, index = False)
        print("OK")

def create_dataset(distancia, velocidade, desaceleracao, massa):
    """
    Generates one dataset

    Parameters
    ----------
    distancia : array
        The array of distances.
    velocidade : array
        The array of speeds.
    desaceleracao : array
        The array of deceleration (braking capacity).
    massa : int or float
        Vehicle's mass.

    Returns
    -------
    Returns a dataframe with noisy and non-noisy inputs/outputs, includes intermediate results.
    """

    size = len(distancia)*len(velocidade)*len(desaceleracao)

    data = np.zeros((size, 22))

    #Cria um Dataframe vazio com as colunas descritas 

    global M
    M = massa 
    l = 0 #Contador de linhas

    print("Generating dataset...", end = '', flush = True)

    for i in range(len(distancia)):
        for j in range(len(velocidade)):
            for k in range(len(desaceleracao)):
                #Calcula o desvio padrão da distância
                if(distance[i] <= 30):
                    devpadDistancia = 0.05 + 0.87 + 0.05*TCY
                else: 
                    devpadDistancia = 0.5 + 0.87 + 0.5*TCY
                distanciaRuido = np.random.normal(distance[i], devpadDistancia) #Gera o ruído
                if(distanciaRuido < 0):
                    distanciaRuido = 0
                elif(distance[i] + 2*devpadDistancia < distanciaRuido):
                    distanciaRuido = distance[i] + 2*devpadDistancia
                elif(distance[i] - 2*devpadDistancia > distanciaRuido):
                    distanciaRuido = distance[i] - 2*devpadDistancia
                
                devpadVelocidade = 0.03*speed[j] #Calcula o desvio padrão da velocidade
                velocidadeRuido = np.random.normal(speed[j], devpadVelocidade) #Gera o ruído
                if(velocidadeRuido < 0):
                    velocidadeRuido = 0
                elif(speed[j] + 2*devpadVelocidade < velocidadeRuido):
                    velocidadeRuido = speed[j] + 2*devpadVelocidade
                elif(speed[j] - 2*devpadVelocidade > velocidadeRuido):
                    velocidadeRuido = speed[j] - 2*devpadVelocidade

                ruidos = np.array([distanciaRuido, velocidadeRuido, brake[k]]) #Define vetores para facilitar a chamada do concatenate
                sinais = np.array([distance[i], speed[j], brake[k]])
                
                #Escreve o resultado como uma linha no dataframe
                data[l] = np.concatenate((ruidos, sinais, calcula_distancia(distance[i],speed[j],brake[k]), 
                                            calcula_distancia(distanciaRuido, velocidadeRuido, brake[k])), 
                                            axis = None)
                l += 1 
    
    data = pd.DataFrame(data, columns=['Distancia Ruidosa', 'Velocidade Ruidosa', 'Capacidade de Frenagem Ruidosa', 'Distancia', 
    'Velocidade', 'Capacidade de Frenagem', 'Decisao', 'Aceleracao', 'AW', 'AG', 'VH', 'VC', 'V50', 'DS', 'Decisao Ruidosa', 
    'Aceleracao Ruidosa', 'AW Ruidosa', 'AG Ruidosa', 'VH Ruidosa', 'VC Ruidosa', 'V50 Ruidosa', 'DS Ruidosa'])

    print("OK")

    return data

def calcula_distancia(distancia, velocidade, aceleracao):
    """
    Compute the secure braking's distance

    Paramenters
    -----------
    distancia : int or float
        Distance between the vehicle and the object.
    velocidade : int or float
        Vehicle's speed
    aceleracao : int or float
        Vehicle's deceleration (braking capacity).
    """

    D = np.double(distancia)
    VE = np.double(velocidade)
    A = np.double(aceleracao)

    if(aceleracao > 0.8): #Se a desaceleração for de aderencia normal
        AH = 1.12 #Utilizar aderencia normal
    else:
        AH = 0.84 #Utilizar baixa aderencia

    AW = (0.5*RHO*Cd*ATS*((VW-VE)**2))/(M+MRI)
    AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
    VH = VE + (AH+AW-AG)*TH
    VC = VH + (AW-AG)*TC
    V50 = VC + (0.5*A+AW-AG)*T50
    DS = ((VE*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*A+AW-AG)*T50**2))+(V50**2/(2*(A+AW-AG)))

    if DS >= D: #Se a distancia para parada >= distancia para obstaculo
        return 1, AH, AW, AG, VH, VC, V50, DS #Frenagem necessaria
    else:   
        return 0, AH, AW, AG, VH, VC, V50, DS #Frenagem desnecessaria

def create_stratifiedDataset(distancia, velocidade, desaceleracao, massa, prop_zeros=0.8):
    """
    Generates dataset with the desired proportion of zeros

    Parameters
    ----------
    distancia : array
        The array of distances.
    velocidade : array
        The array of speeds.
    desaceleracao : array
        The array of deceleration (braking capacity).
    massa : int or float
        Vehicle's mass.
    prop_zeros : float in [0,1], default=0.8
        Proportion of zeros in the dataset. If prop_zeros=0.6, the generate dataset will have 60% of its outputs equals to zero.
        The default 0.8 figure is a de-facto sub-optimal decision based on the balance of precision and recall of preliminary tests with decision trees.

    Returns
    -------
    Returns a stratified dataframe with noisy and non-noisy inputs/outputs, includes intermediate results.
    """
    print("---- Stratifying Dataset ----")
    data = create_dataset(distancia, velocidade, desaceleracao, massa)
    n_data = len(data)

    n_data_ones = len(data[data['Decisao'] == 1])
    expected_ones = ceil(n_data*(1-prop_zeros)).astype(int)

    minimum_dataset = floor(expected_ones/n_data_ones).astype(int)

    for i in range(minimum_dataset):
        print(f"Generating {i+1} of {minimum_dataset} dataset needed")
        data_aux = create_dataset(distancia, velocidade, desaceleracao, massa)
        data = pd.concat([data, data_aux])

    data = stratify_data(data, frac = 1/(minimum_dataset+1), prop_zeros = prop_zeros).reset_index(drop = True)

    return data

def stratify_data(data, frac=0.7, prop_zeros=0.8, random_state=None, shuffle=True):
    """
    Creates a new dataset with stratified outputs.

    Parameters
    ----------
    data : pandas DataFrame
        The original dataset that will be stratified.

    frac: float in [0,1], default=0.7
        The percentage of the original dataset that will be 
        used to generate the new dataset.

    prop_zeros: float in [0,1], default=0.8
        The desired proportion of zeros in the output.
    
    random_state: int, RandomState instance or None, default=None
        Controls the randomness of the data selected.
        With the default 'None' figure, the randomness is augmented.
    
    shuffle: bool, default=True
        Decides if the new dataset will be shuffled at the end.

    Returns
    -------
        Return a dataframe with a new proportion of zeros

    Examples
    --------
    >>> StratifyData(data = dataset, frac=0.7, prop_zeros=0.6)

        That call will return a new dataset with 60% of its outputs equals to zero. The new dataset will have 70% of the original size.
    """

    # Calcula o número de elementos no dataset de entrada
    n_data = len(data)

    # Calcula o número de elementos no dataset estratificado
    n_data_stratified = ceil(frac*n_data)

    # Calcula o número de saídas iguais a 1 no dataset de entrada
    n_data_ones = len(data[data['Decisao'] == 1])
    
    # Calcula proporção mínima de zeros
    prop_zeros_min = (1-((n_data_ones)/(ceil(frac*n_data)))).round(4)

    # Retorna erro se a proporção mínima não é satisfeita
    if(prop_zeros < prop_zeros_min):
        raise ValueError(f"For frac = {frac*100}%, prop_zeros must be {prop_zeros_min*100}% or higher")

    # Calcula número de zeros e uns que devem estar presentes no dataset estratificado
    n_data_stratified_ones = ceil((1-prop_zeros)*n_data_stratified).astype(int)
    n_data_stratified_zeros = (n_data_stratified - n_data_stratified_ones).astype(int)

    # Amostra os "n" zeros e uns do dataset de entrada aletoriamente
    data_one_stratified = data[data['Decisao'] == 1].sample(n = n_data_stratified_ones, random_state = random_state).reset_index(drop=True)
    data_zero_stratified = data[data['Decisao'] == 0].sample(n = n_data_stratified_zeros, random_state = random_state).reset_index(drop=True)

    # Junta os zeros e uns para formar o dataset estratificado
    data_stratified = pd.concat([data_one_stratified, data_zero_stratified]).reset_index(drop=True)

    # Mistura os zeros e uns, se assim desejado
    if(shuffle == True):
        data_stratified = data_stratified.sample(frac = 1, random_state = random_state)

    # Devolve a base de dados estratificada
    return data_stratified.reset_index(drop=True)

def print_menu():
    for key in menu_options.keys():
        print(menu_options[key])

def option1():
    print("Suggestions: ")
    print("-- 8 passengers/m^2 = 382617")
    print("-- 6 passengers/m^2 = 348687.25")
    print("-- 4 passengers/m^2 = 314757.5")
    print("-- 0 passengers/m^2 (empty) = 246898")
    print("All values in [kg]")
    print("The suggestions are based on the data provided by Metro of São Paulo. Intermediate values were found by linear interpolation.")
    
    print("")
    M = float(input("Insert the mass of the vehicle: "))
    name = str(input("Insert the name of the file: "))
    print("")

    print("---- Generating Dataset ----")
    startGenData = time.time()
    data = create_dataset(distance, speed, brake, M)
    print("")

    write_dataset(data, name)
    endGenData = time.time()
    execution_timeGenData = round(endGenData - startGenData, 2)
    print("")
    print(f"Execution time (generation + writing): {execution_timeGenData} seconds",)

def option2():
    print("Suggestions: ")
    print("-- 8 passengers/m^2 = 382617")
    print("-- 6 passengers/m^2 = 348687.25")
    print("-- 4 passengers/m^2 = 314757.5")
    print("-- no passengers (empty)  = 246898")
    print("All values in [kg]")
    print("The suggestions are based on the data provided by Metro of São Paulo. Intermediate values were found by linear interpolation.")

    print("")
    M = float(input("Insert the mass of the vehicle: "))
    prop_zeros = float(input("Insert the proportion of zeros in the output: "))
    name = str(input("Insert the name of the file: "))
    print("")

    startGenDataStrat = time.time()
    data = create_stratifiedDataset(distance, speed, brake, M, prop_zeros)
    print("")

    write_dataset(data, name)
    endGenDataStrat = time.time()
    execution_timeGenDataStrat = round(endGenDataStrat - startGenDataStrat, 2)
    print("")
    print(f"Execution time (generation + writing): {execution_timeGenDataStrat} seconds",)

def option3(debug_mode):
    cls()
    if(debug_mode == 1):
        print("Debug deactivated - Debug files will NOT be generated.")
        return False
    elif(debug_mode == 0):
        print("Debug activated - Debug files will be generated.")
        return True

def option4(generate_xlsx):
    cls()
    if(generate_xlsx == 1):
        print(".xlsx files deactivated - .xlsx will NOT be generated.")
        return False
    elif(generate_xlsx == 0):
        print(".xlsx files activated - .xlsx files will be generated.")
        return True

def option5():
    cls()
    print("[1] Generates a dataset using the Emergency Brake Curve.")
    print("[2] Combines multiple datasets to generate a new dataset with a different proportion of zeros on the output.")
    print("[3] Selects whether debug files will be generated or not.")
    print("[4] Selects whether .xlsx files will be generated or not, makes execution faster.")
    input("Press enter to return ")
    cls()

debug_mode = True
generate_xlsx = True

menu_options = {
    1: '[1] Generate dataset',
    2: '[2] Generate stratified dataset',
    3: '[3] Activate/Deactivate debug files (deactivate for faster execution)',
    4: '[4] Activate/Deactivate .xlsx files, .csv files will always be generated. (deactivate for faster execution)',
    5: '[5] Help',
    6: '[0] Exit',
}

cls()

while (True):
    print_menu()
    option = ''
    try:
        option = int(input('Select one option: '))
    except:
        print('Invalid input, insert a number')
    if option == 1:
        cls()
        start1 = time.time()
        option1()
        end1 = time.time()
        execution_time1 = round(end1 - start1, 2)
        print(f"Execution time (total): {execution_time1} seconds\n",)

    elif option == 2:
        cls()
        start2 = time.time()
        option2()
        end2 = time.time()
        execution_time2 = round(end2 - start2, 2)
        print(f"Execution time (total): {execution_time2} seconds\n",)

    elif option == 3:
        cls()
        debug_mode = option3(debug_mode)

    elif option == 4:
        cls()
        generate_xlsx = option4(generate_xlsx)

    elif option == 5:
        cls()
        option5()
        
    elif option == 0:
        cls()
        exit()
    else:
        cls()
        print('Invalid input, please enter a number between 0 and 5')