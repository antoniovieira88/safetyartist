import csv
import numpy as np

distance = np.arange(start=0, stop=2010, step=10)   #Cria vetor distancia [m]
speed = np.arange(start=0, stop=28.5, step=0.5)     #Cria vetor velocidade [m/s]
brake = [1.395, 1.1625, 0.93, 0.78, 0.65]           #Cria vetor de desaceleracao (baseado nos valores de AEB da tabela) [m/s^2] 

AH = 1.12       #Aceleracao com -- baixa aderencia = 0.84 -- aderencia normal = 1.12 [m/s^2]
M = 382617      #Massa do trem  -- com 8 passageiros/m^2 = 382617 -- sem passageiros = 246898 [kg]
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

############# Equacoes utilizadas ###############

# AW = (0.5*RHO*Cd*ATS*(VW-V)**2)/(M+MRI)
# AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
# VH = VA + (AH+AW-AG)*TH
# VC = VH + (AW-AG)*TC
# V50 = VC + (0.5*AEB+AW-AG)*T50
# DS = ((VA*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*AEB+AW-AG)*T50**2))+(V50**2/(2*(AEB+AW+AG)))

################################################


def calcula_distancia(distancia, velocidade, aceleracao):

    D = float(distancia)
    VE = float(velocidade)
    A = float(aceleracao)

    AW = (0.5*RHO*Cd*ATS*(VW-VE)**2)/(M+MRI)
    AG = (M*np.sin(np.arctan(GR))*g)/(M+MRI)
    VH = VE + (AH+AW-AG)*TH
    VC = VH + (AW-AG)*TC
    V50 = VC + (0.5*A+AW-AG)*T50

    DS = ((VE*TH)+(0.5*(AH+AW-AG)*TH**2))+((VH*TC)+(0.5*(AW-AG)*TC**2))+((VC*T50)+(0.5*(0.5*A+AW-AG)*T50**2))+(V50**2/(2*(A+AW+AG)))

    if DS >= D: #Se a distancia para parada >= distancia para obstaculo
        return 1 #Frenagem necessaria
    else:   
        return 0 #Frenagem desnecessaria

with open('Dataset.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    for i in distance:
        for j in range(len(speed)):
            for k in range(len(brake)):
                writer.writerow([distance[i],speed[j], brake[k], calcula_distancia(distance[i],speed[j],brake[k])])
