#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/*
As estruturas abaixo foram retiradas do livro Algoritmos para Grafos via Sedgewick do Paulo Feofiloff
Disponível em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/

#define vertex int

static int cnt;
int pre[1000];

typedef struct NoLista {
    char valor;
    struct NoLista *prox;
} NoLista;

typedef struct Lista {
    NoLista *cabeca;
} Lista;

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

static conecta NovoNo(vertex w, conecta prox) { 
    conecta a = malloc(sizeof(struct no));
    a->w = w; 
    a->prox = prox;     
    return a;                         
}

Grafo IniciaGrafo(int V) { 
    Grafo G = malloc(sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = malloc(V * sizeof(conecta));
    for (vertex v = 0; v < V; ++v) 
        G->adj[v] = NULL;
    return G;
}

void insereAresta(Grafo G, vertex v, vertex w) { 
    for (conecta a = G->adj[v]; a != NULL; a = a->prox) 
        if (a->w == w) return;
    G->adj[v] = NovoNo(w, G->adj[v]);
    G->A++;
}

void LimpaGrafo(Grafo G) {
    if (G == NULL) {
        return;
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

NoLista *NovoNoLista(char valor) {
    NoLista *novo = malloc(sizeof(NoLista));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

void AdicionarElemento(Lista *lista, char valor) {
    NoLista *novo = NovoNoLista(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
    } else {
        NoLista *atual = lista->cabeca;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

void RemoverElemento(Lista *lista, char valor) {
    NoLista *atual = lista->cabeca;
    NoLista *anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            lista->cabeca = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

bool verificaLista(NoLista *esq, NoLista *dir) {
    int count_c_esq = 0;
    int count_m_esq = 0;
    int count_c_dir = 0;
    int count_m_dir = 0;

    NoLista *atual = esq;

    while (atual != NULL) {
        if (atual->valor == 'c') {
            count_c_esq++;
        } else if (atual->valor == 'm') {
            count_m_esq++;
        }
        atual = atual->prox;
    }

    atual = dir;

    while (atual != NULL) {
        if (atual->valor == 'c') {
            count_c_dir++;
        } else if (atual->valor == 'm') {
            count_m_dir++;
        }
        atual = atual->prox;
    }

    if ((count_c_esq > count_m_esq && count_m_esq > 0) ||
        (count_c_dir > count_m_dir && count_m_dir > 0)) {
        return false;
    } else {
        return true;
    }
}


int tamanhoLista(NoLista *cabeca) {
    int tamanho = 0;
    NoLista *atual = cabeca;

    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }

    return tamanho;
}

void dfs(Grafo G, vertex v, int dist[], vertex parent[]) {
    for (conecta a = G->adj[v]; a != NULL; a = a->prox) {
        vertex w = a->w;
        if (dist[w] == INT_MAX) {
            dist[w] = dist[v] + 1;
            parent[w] = v;
            dfs(G, w, dist, parent);
        }
    }
}

int menorCaminho(Grafo G, vertex origem, vertex destino) {
    int *dist = malloc(G->V * sizeof(int));
    vertex *parent = malloc(G->V * sizeof(vertex));

    for (vertex v = 0; v < G->V; ++v) {
        dist[v] = INT_MAX;
        parent[v] = -1;
    }

    dist[origem] = 0;
    dfs(G, origem, dist, parent);

    printf("Menor caminho de %d para %d:\n", origem, destino);
    vertex v = destino;
    while (v != origem) {
        printf("%d ", v);
        v = parent[v];
    }
    printf("%d\n", origem);

    free(dist);
    free(parent);

    return 0;
}

void joga(Lista esq, Lista dir, int barco, Grafo grafo, int k) {
    //printf("%d\n", tamanhoLista(dir.cabeca));

    if (tamanhoLista(esq.cabeca) == 0) {
        menorCaminho(grafo, 0, k);
    }
   
    for(int i = 0; i < 4; i++){

        if(barco == 0){
            if (i == 0){
                RemoverElemento(&esq, 'c');
                AdicionarElemento(&dir, 'c');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 0, grafo, 4*k+i);
                }
            }

            if (i == 1){
                RemoverElemento(&esq, 'm');
                AdicionarElemento(&dir, 'm');
                 if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 0, grafo, 4*k+i);
                }
            }
            if (i == 2){
                RemoverElemento(&esq, 'c');
                AdicionarElemento(&dir, 'c');
                RemoverElemento(&esq, 'c');
                AdicionarElemento(&dir, 'c');
                 if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 0, grafo, 4*k+i);
                }
            }
            if (i == 3){
                RemoverElemento(&esq, 'm');
                AdicionarElemento(&dir, 'm');
                RemoverElemento(&esq, 'm');
                AdicionarElemento(&dir, 'm');
                 if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 0, grafo, 4*k+i);
                }

            }
            if (i == 4){
                RemoverElemento(&esq, 'm');
                AdicionarElemento(&dir, 'm');
                RemoverElemento(&esq, 'c');
                AdicionarElemento(&dir, 'c');
                  if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 0, grafo, 4*k+i);
                }
             }
        }else{
            if (i == 0){
                RemoverElemento(&dir, 'c');
                AdicionarElemento(&esq, 'c');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 1, grafo, 4*k+i);
                }
            }
            if (i == 1){
                RemoverElemento(&dir, 'm');
                AdicionarElemento(&esq, 'm');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 1, grafo, 4*k+i);
                }

            }
            if (i == 2){
                RemoverElemento(&dir, 'c');
                AdicionarElemento(&esq, 'c');
                RemoverElemento(&dir, 'c');
                AdicionarElemento(&esq, 'c');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 1, grafo, 4*k+i);
                }

            }
            if (i == 3){
                RemoverElemento(&dir, 'm');
                AdicionarElemento(&esq, 'm');
                RemoverElemento(&dir, 'm');
                AdicionarElemento(&esq, 'm');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 1, grafo, 4*k+i);
                }

            }
            if (i == 4){
                RemoverElemento(&dir, 'm');
               AdicionarElemento(&esq, 'm');
                RemoverElemento(&dir, 'c');
                AdicionarElemento(&esq, 'c');
                if(verificaLista(esq.cabeca, dir.cabeca)){
                    insereAresta(grafo, k, 4*k+i);
                    joga(esq, dir, 1, grafo, 4*k+i);
                }
             }
        }
    }
}

int main() {
    Lista lado_esq;
    Lista lado_dir;
    int k = 0;
    int barco = 0;
    
    lado_esq.cabeca = NULL;
    lado_dir.cabeca = NULL;

    AdicionarElemento(&lado_esq, 'c');
    AdicionarElemento(&lado_esq, 'c');
    AdicionarElemento(&lado_esq, 'c');
    AdicionarElemento(&lado_esq, 'm');
    AdicionarElemento(&lado_esq, 'm');
    AdicionarElemento(&lado_esq, 'm');

    Grafo grafo = IniciaGrafo(1000);

    joga(lado_esq, lado_dir, barco, grafo, k);

    return 0;
}