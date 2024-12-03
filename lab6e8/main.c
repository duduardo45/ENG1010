#include <stdlib.h>
#include <stdio.h>

#define NUMERO_NOS 9

typedef struct _viz Viz;
struct _viz
{
    int noj;
    float peso;
    Viz *prox;
};
struct _grafo
{
    int nv;    /* numero de nos ou vertices */
    int na;    /* numero de arestas */
    Viz *viz[NUMERO_NOS]; /* viz[i] aponta para a lista de arestas incidindo em i */
};
typedef struct _grafo Grafo;

void adicionar_link(Grafo *grafo, int noi, int noj, float peso)
{
    Viz *viz = (Viz *)malloc(sizeof(Viz));
    viz->noj = noj;
    viz->peso = peso;
    viz->prox = grafo->viz[noi];
    grafo->viz[noi] = viz;
    grafo->na++;
}

int* busca_em_amplitude(Grafo* grafo, int no_inicio)
{
    int* visitados = (int*)malloc(grafo->nv * sizeof(int));
    int* fila = (int*)malloc(grafo->nv * sizeof(int));
    int inicio_fila = 0;
    int fim_fila = 0;
    int contador = 0;
    
    // vetor visitados dá a ordem de visitação

    // Inicializa vetor de visitados com -1
    for (int i = 0; i < grafo->nv; i++) {
        visitados[i] = -1;
    }

    // Adiciona no inicial na fila e marca como visitado
    fila[fim_fila++] = no_inicio;
    visitados[contador++] = no_inicio;

    // Enquanto houver nos na fila
    while (inicio_fila < fim_fila) {
        int no_atual = fila[inicio_fila++];
        
        // Percorre todos os vizinhos do no atual
        for (Viz* v = grafo->viz[no_atual]; v != NULL; v = v->prox) {
            int ja_visitado = 0;
            
            // Verifica se ja foi visitado
            for (int i = 0; i < contador; i++) {
                if (visitados[i] == v->noj) {
                    ja_visitado = 1;
                    break;
                }
            }
            
            // Se nao foi visitado, adiciona na fila e marca como visitado
            if (!ja_visitado) {
                fila[fim_fila++] = v->noj;
                visitados[contador++] = v->noj;
            }
        }
    }

    free(fila);
    return visitados;
}



int main(void)
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->nv = NUMERO_NOS;
    grafo->na = 0;
    for (int i = 0; i < NUMERO_NOS; i++)
        grafo->viz[i] = NULL;
    adicionar_link(grafo, 0, 1, 4);
    adicionar_link(grafo, 0, 8, 8);
    adicionar_link(grafo, 1, 8, 11);
    adicionar_link(grafo, 1, 3, 8);
    adicionar_link(grafo, 3, 4, 7);
    adicionar_link(grafo, 8, 2, 7);
    adicionar_link(grafo, 8, 7, 1);
    adicionar_link(grafo, 2, 7, 6);
    adicionar_link(grafo, 2, 3, 2);
    adicionar_link(grafo, 3, 6, 4);
    adicionar_link(grafo, 6, 5, 10);
    adicionar_link(grafo, 4, 5, 9);
    adicionar_link(grafo, 7, 6, 2);
    adicionar_link(grafo, 4, 6, 14);
    int* visitados = busca_em_amplitude(grafo, 0);
    for (int i = 0; i < NUMERO_NOS; i++) {
        printf("%d ", visitados[i]);
    }
    printf("\n");
}
