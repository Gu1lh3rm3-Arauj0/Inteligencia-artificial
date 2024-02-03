"""
Guilherme AraÃºjo Mendes de Souza - 156437
UNIFESP - ICT
IA
Aula 4
"""
ladoEsq = ['c', 'c', 'c', 'm', 'm', 'm']
ladoDir = []
barco = 0 
grafo = {} 
k = 0
estado = {}


def verifica(lista):
    if (lista.count('c') > lista.count('m')) and ('m' in lista):
        return False
    else:
        return True

    
def adiciona_aresta(a, b, meu_dicionario):
    if a in meu_dicionario:
        meu_dicionario[a].append(b)
    else:
        meu_dicionario[a] = [b]

'''
dfs_recursiva do algoritmos em python

Diponível em: https://algoritmosempython.com.br/cursos/algoritmos-python/algoritmos-grafos/busca-profundidade/
'''     
def dfs_recursiva(grafo, vertice, visitados):
    visitados.add(vertice)
    for vizinho in grafo[vertice]:
        if vizinho not in visitados:
            dfs_recursiva(grafo, vizinho, visitados)
            
    
def salva_estado(k, lista1, lista2, barco_estado, estado):
    if k in estado:
        estado[k].append((lista1, lista2, barco_estado))
    else:
        estado[k] = [(lista1, lista2, barco_estado)]


def joga(estado_atual, meu_dicionario, k):
    profundidade_maxima = 10000
    
    estados_para_iterar = estado.copy()
    
    for chave_k in estados_para_iterar:
        estados_k = estados_para_iterar[chave_k]
        for estado_atual in estados_k:
            ladoEsq, ladoDir, barco = estado_atual
            
            if k >= profundidade_maxima:
                return
            
        if (barco == 0):
            for i in range(5):
                aux_ladoEsq = ladoEsq.copy()
                aux_ladoDir = ladoDir.copy()
                    
                    
                if (i == 2 and ladoEsq.count('m') > 1):
                    aux_ladoEsq.remove('m')
                    aux_ladoEsq.remove('m')
                    aux_ladoDir.append('m')
                    aux_ladoDir.append('m')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 1, estado)     
                     
                if (i == 3 and ladoEsq.count('c') > 1):
                    aux_ladoEsq.remove('c')
                    aux_ladoEsq.remove('c')
                    aux_ladoDir.append('c')
                    aux_ladoDir.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 1, estado)    
                        
                if (i == 4 and ladoEsq.count('m') > 0 and ladoEsq.count('c') > 0 ):
                    aux_ladoEsq.remove('m')
                    aux_ladoEsq.remove('c')
                    aux_ladoDir.append('m')
                    aux_ladoDir.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 1, estado)
                            
                if (i == 0 and ladoEsq.count('m') > 0):
                    aux_ladoEsq.remove('m')
                    aux_ladoDir.append('m')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 1, estado)
                    
                if (i == 1 and ladoEsq.count('c') > 0):
                    aux_ladoEsq.remove('c')
                    aux_ladoDir.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 1, estado)             
                        
        if (barco == 1):              
                
            for i in range(5):
                aux_ladoEsq = ladoEsq.copy()
                aux_ladoDir = ladoDir.copy()

                if (i == 2 and ladoDir.count('m') > 1):
                    aux_ladoDir.remove('m')
                    aux_ladoDir.remove('m')
                    aux_ladoEsq.append('m')
                    aux_ladoEsq.append('m')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 0, estado)    
                    
                if (i == 3 and ladoDir.count('c') > 1):
                    aux_ladoDir.remove('c')
                    aux_ladoDir.remove('c')
                    aux_ladoEsq.append('c')
                    aux_ladoEsq.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 0, estado)    
                            
                if (i == 4 and ladoDir.count('m') > 0 and ladoDir.count('c') > 0):
                    aux_ladoDir.remove('m')
                    aux_ladoDir.remove('c')
                    aux_ladoEsq.append('m')
                    aux_ladoEsq.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 0, estado)    
                             
                if (i == 0 and ladoDir.count('m') > 0):
                    aux_ladoDir.remove('m')
                    aux_ladoEsq.append('m')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                           adiciona_aresta(k, 5*k + i, meu_dicionario)
                           salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 0, estado)   
                    
                if (i == 1 and ladoDir.count('c') > 0):
                    aux_ladoDir.remove('c')
                    aux_ladoEsq.append('c')
                    if(verifica(aux_ladoEsq) and verifica(aux_ladoDir)):
                        adiciona_aresta(k, 5*k + i, meu_dicionario)
                        salva_estado((5*k + i), aux_ladoEsq, aux_ladoDir, 0, estado)           
                            
                              
    joga(estado, grafo, (k+1))    
            

salva_estado(k, ladoEsq, ladoDir, barco, estado)

joga(estado, grafo, k)