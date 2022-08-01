import pandas as pd
import numpy as np

distance = np.arange(start=0, stop=2010, step=10)   #Cria vetor distancia [m]
speed = np.arange(start=0, stop=28.5, step=0.5)     #Cria vetor velocidade [m/s]
brake = [1.395, 1.1625, 0.93, 0.78, 0.65]           #Cria vetor de desaceleracao (baseado nos valores de AEB da tabela) [m/s^2] 

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
V = VA          #Velocidade instantenea do trem (pior caso)
TC = 1.5        #Tempo de duracao do corte de tracao sem aplicacao de freios [s]
T50 = 0.5       #Tempo de duracao da aplicacao do freio com metade da capacidade [s]

############# Equacoes utilizadas ##############

# AW = (0.5*RHO*Cd*ATS*(VW-V)**2)/(M+MRI)
# AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
# VH = VA + (AH+AW-AG)*TH
# VC = VH + (AW-AG)*TC
# V50 = VC + (0.5*AEB+AW-AG)*T50
# DS = ((VA*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*AEB+AW-AG)*T50**2))+(V50**2/(2*(AEB+AW+AG)))

################################################


def create_Dataset(nome, distancia, velocidade, desaceleracao, massa):

    data = pd.DataFrame(columns=['Distancia', 'Velocidade', 'Capacidade de Frenagem', 'Decisao', 'AW', 'AG', 'VH', 'VC', 'V50', 'DS']) #Cria um Dataframe vazio com as colunas descritas

    M = massa 
    l = 0 #Serve apenas para contar em qual linhas do Dataframe 

    for i in range(len(distancia)):
        for j in range(len(velocidade)):
            for k in range(len(desaceleracao)):
                l += 1 
                if(brake[k] > 0.8): #Se a desaceleração for de aderencia normal
                    AH = 1.12 #Utilizar aderencia normal
                else:
                    AH = 0.84 #Utilizar baixa aderencia
                data.loc[l] = np.concatenate((np.array([distance[i], speed[j], brake[k]]), calcula_distancia(distance[i],speed[j],brake[k])), axis = None) #Escreve o como uma linha no dataframe

    dataCompressed = data[['Distancia', 'Velocidade', 'Capacidade de Frenagem', 'Decisao']] #Cria um segundo dataframe reduzindo o número de colunas

    data.to_csv(nome + "Debug.csv", header = False, index = False) #Cria o dataframe completo em csv
    dataCompressed.to_csv(nome + ".csv", header = False, index = False) #Cria o dataframe reduzido em csv

    with pd.ExcelWriter(nome + ".xlsx") as writer:  #Cria o dataframe reduzido em excel (arquivo unico)
        data.to_excel(writer, sheet_name = nome + "Debug", index = False)
        dataCompressed.to_excel(writer, sheet_name= nome, index = False)

def calcula_distancia(distancia, velocidade, aceleracao):

    D = np.double(distancia)
    VE = np.double(velocidade)
    A = np.double(aceleracao)

    AW = (0.5*RHO*Cd*ATS*(VW-VE)**2)/(M+MRI)
    AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
    VH = VE + (AH+AW-AG)*TH
    VC = VH + (AW-AG)*TC
    V50 = VC + (0.5*A+AW-AG)*T50
    DS = ((VE*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*A+AW-AG)*T50**2))+(V50**2/(2*(A+AW+AG)))

    if DS >= D: #Se a distancia para parada >= distancia para obstaculo
        return 1, AW, AG, VH, VC, V50, DS #Frenagem necessaria
    else:   
        return 0, AW, AG, VH, VC, V50, DS #Frenagem desnecessaria

create_Dataset("Dataset", distance, speed, brake, 246898)   ## Cria dataset para trem vazio, para calcular outros basta Copy/Paste e trocar o nome e valor da massa


