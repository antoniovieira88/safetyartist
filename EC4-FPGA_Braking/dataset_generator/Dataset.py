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
###########################################################################################################################

import os
os.environ['CONDA_DLL_SEARCH_MODIFICATION_ENABLE'] = '1' #Evita problemas de versão do NumPy com Conda

import pandas as pd
import numpy as np
np.random.seed(None)

import time
start = time.time()

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


def create_Dataset(nome, distancia, velocidade, desaceleracao, massa):

    size = len(distancia)*len(velocidade)*len(desaceleracao)

    data = pd.DataFrame(columns=['Distancia Ruidosa', 'Velocidade Ruidosa', 'Capacidade de Frenagem Ruidosa', 'Distancia', 'Velocidade', 'Capacidade de Frenagem', 'Decisao', 'Aceleracao', 'AW', 'AG', 'VH', 'VC', 'V50', 'DS', 'Decisao Ruidosa', 'Aceleracao Ruidosa', 'AW Ruidosa', 'AG Ruidosa', 'VH Ruidosa', 'VC Ruidosa', 'V50 Ruidosa', 'DS Ruidosa'], index = range(size)) #Cria um Dataframe vazio com as colunas descritas

    global M
    M = massa 
    l = 0 #Contador de linhas

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

                data.loc[l] = np.concatenate((ruidos, sinais, calcula_distancia(distance[i],speed[j],brake[k]), calcula_distancia(distanciaRuido, velocidadeRuido, brake[k])), axis = None) #Escreve o como uma linha no dataframe
                l += 1 

    dataCompressed = data[['Distancia Ruidosa', 'Velocidade Ruidosa', 'Capacidade de Frenagem Ruidosa', 'Decisao']] #Cria um segundo dataframe reduzindo o número de colunas

    data.to_csv(nome + "Debug.csv", header = False, index = False) #Cria o dataframe completo em csv
    dataCompressed.to_csv(nome + ".csv", header = False, index = False) #Cria o dataframe reduzido em csv

    with pd.ExcelWriter(nome + ".xlsx") as writer:  #Cria o dataframe reduzido em Excel (arquivo unico)
        data.to_excel(writer, sheet_name = nome + "Debug", index = False)
        dataCompressed.to_excel(writer, sheet_name= nome, index = False)

def calcula_distancia(distancia, velocidade, aceleracao):

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

# Programa Principal
create_Dataset("Dataset", distance, speed, brake, 246898)   ## Cria dataset para trem vazio, para calcular outros basta Copy/Paste e trocar o nome e valor da massa
end = time.time()
print("Tempo de execução: ", end - start)