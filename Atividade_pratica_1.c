/*
Guilherme Araújo Mendes de Souza - 156437
UNIFESP - ICT
IA

beecrowd | 3247 | Robôs em uma Grade
*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

/*
As estruturas abaixo foram retiradas do livro Algoritmos para Grafos via Sedgewick do Paulo Feofiloff
Disponível em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/

#define vertex int

//Estruturas do Grafo
typedef struct no *conecta;
struct no {
    vertex w;
    conecta prox;
};

struct grafo {
    int V;
    int A;
    conecta *adj;
};
typedef struct grafo *Grafo;

//Funções da estrutura
static conecta NovoNo( vertex w, conecta prox) { 
   conecta a = malloc( sizeof (struct no));
   a->w = w; 
   a->prox = prox;     
   return a;                         
}

Grafo IniciaGrafo( int V) { 
   Grafo G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc( V * sizeof (conecta));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void insereAresta( Grafo G, vertex v, vertex w) { 
   for (conecta a = G->adj[v]; a != NULL; a = a->prox) 
      if (a->w == w) return;
   G->adj[v] = NovoNo( w, G->adj[v]);
   G->A++;
}

void LimpaGrafo(Grafo G) {
    if (G == NULL) {
        return; // Verificação de segurança para um grafo nulo
    }

    for (vertex v = 0; v < G->V; ++v) {
        conecta atual = G->adj[v];
        while (atual != NULL) {
            conecta proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(G->adj);
    free(G);
}

/*
Algoritmo busca em profundidade (DFS) do Paulo Feofiloff
Disponível em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/
int dfsR(Grafo G, vertex v, vertex destino) {
    if (v == destino) {
        return 1; // Encontrou um caminho para o destino
    }

    int contador = 0;

    for (conecta a = G->adj[v]; a != NULL; a = a->prox) {
        vertex w = a->w;
        contador += dfsR(G, w, destino);
    }

    LimpaGrafo(G);
    return contador;
}

void percorre(int tamanho, char **grade) {
    Grafo grafo = IniciaGrafo(tamanho * tamanho);

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (grade[i][j] == '.') {
                if (i + 1 < tamanho && grade[i + 1][j] == '.') {
                    insereAresta(grafo, i * tamanho + j, (i + 1) * tamanho + j);
                }
                if (j + 1 < tamanho && grade[i][j + 1] == '.') {
                    insereAresta(grafo, i * tamanho + j, i * tamanho + j + 1);
                }
            }
        }
    }

    int numeroDeCaminhos = dfsR(grafo, 0, (tamanho * tamanho) - 1);
    if (numeroDeCaminhos == 0) {
        percorre2(tamanho, grade);
    } else {
        printf("%d\n", numeroDeCaminhos);
    }
}

void percorre2(int tamanho, char **grade) {
    Grafo grafo = IniciaGrafo(tamanho * tamanho);

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (grade[i][j] == '.') {
                if (i + 1 < tamanho && grade[i + 1][j] == '.') {
                    insereAresta(grafo, i * tamanho + j, (i + 1) * tamanho + j);
                }
                if (i - 1 > 0 && grade[i - 1][j] == '.') {
                    insereAresta(grafo, i * tamanho + j, (i + 1) * tamanho + j);
                }
                if (j + 1 < tamanho && grade[i][j + 1] == '.') {
                    insereAresta(grafo, i * tamanho + j, i * tamanho + j + 1);
                }
                 if (j - 1 > 0 && grade[i][j + 1] == '.') {
                    insereAresta(grafo, i * tamanho + j, i * tamanho + j - 1);
                }
            }
        }
    }

    int numeroDeCaminhos2 = dfsR(grafo, 0, (tamanho * tamanho) - 1);
    if (numeroDeCaminhos2 == 0) {
        printf("INCONCEIVABLE\n");
    } else {
        printf("THE GAME IS A LIE\n");
    }
}

//Função Principal
int main(){
    int tamanho;

    scanf("%d", &tamanho);

    // Aloca espaço para a matriz de caracteres
    char **matriz = (char **)malloc(tamanho * sizeof(char *));
    for (int i = 0; i < tamanho; i++) {
        matriz[i] = (char *)malloc(tamanho * sizeof(char));
    }


    // Preenche a matriz com caracteres lidos da entrada
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }

    percorre(tamanho, matriz);

    return 0;
}