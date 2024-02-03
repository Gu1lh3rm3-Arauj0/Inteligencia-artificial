"""
Guilherme AraÃºjo Mendes de Souza - 156437
UNIFESP - ICT
IA

Aula 07 - ExercÃ­cio prÃ¡tico algoritmos bioinspirados
"""

def funcao_fitness(x):
    return 1 + 2 * x - x ** 2

num_particulas = int(input('Informe o número de partículas: '))
num_iteracoes = int(input('Informe o número de iterações: '))
c1 = float(input('Informe o valor de c1: '))
c2 = float(input('Informe o valor de c2: '))
w = float(input('Informe o valor de w: '))
r1 = float(input('Informe o valor de r1: '))
r2 = float(input('Informe o valor de r2: '))

X = [0.4657, 0.8956, 0.3877, 0.4902, 0.5039]
V = [0.5319, 0.8185, 0.8331, 0.7677, 0.1708]
F = []

pbest = X.copy()
gbest = X.copy()

lista_x = [[] for _ in range(num_iteracoes)]
lista_v = [[] for _ in range(num_iteracoes)]

lista_x[0].append(X.copy())
lista_v[0].append(V.copy())

for i in range(num_particulas):
    X[i] = 10 * (X[i] - 0.5)
    F.append(funcao_fitness(X[i]))

GBF = max(F)
posicao_GBF = F.index(GBF)
gbest = X[posicao_GBF]

print('1ª Interação:')
print(lista_x[0])
print(lista_v[0])
print(F)
print('Melhor solução encontrada: ', gbest)
print('Valor da função fitness: ', GBF)
print('\n')

for j in range(1, num_iteracoes):
    for i in range(num_particulas):
        velocidade_anterior = lista_v[j-1][i]
        posicao_anterior = lista_x[j-1][i]
        
        
        nova_velocidade = w * velocidade_anterior[i] + c1 * r1 * (pbest[i] - posicao_anterior[i]) + c2 * r2 * (gbest - posicao_anterior[i])
        nova_posicao = posicao_anterior[i] + nova_velocidade

        lista_v[j].append(nova_velocidade)
        lista_x[j].append(nova_posicao)

        fitness_atual = funcao_fitness(lista_x[j][i])

        if fitness_atual < F[i]:
            F[i] = fitness_atual
            pbest[i] = lista_x[j][i]

        if fitness_atual < GBF:
            GBF = fitness_atual
            posicao_GBF = i
            gbest = lista_x[j][i]

    print(j+1, "ª Interação:")
    print(lista_x[j])
    print(lista_v[j])
    print(F)
    print('Melhor solução encontrada: ', gbest)
    print('Valor da função fitness: ', GBF)
    print('\n')