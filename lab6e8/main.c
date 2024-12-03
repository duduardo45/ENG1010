#include <stdlib.h>

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

    // Inicializa vetor de visitados com -1 (não visitado)
    for (int i = 0; i < grafo->nv; i++) {
        visitados[i] = -1;
    }

    // Marca nó inicial como visitado
    visitados[no_inicio] = 0;
    int nivel = 1;

    // Enquanto houver nós para visitar
    int mudou = 1;
    while (mudou) {
        mudou = 0;
        // Para cada nó do grafo
        for (int i = 0; i < grafo->nv; i++) {
            // Se foi visitado no nível anterior
            if (visitados[i] == nivel - 1) {
                // Visita todos os vizinhos não visitados
                for (Viz* v = grafo->viz[i]; v != NULL; v = v->prox) {
                    if (visitados[v->noj] == -1) {
                        visitados[v->noj] = nivel;
                        mudou = 1;
                    }
                }
            }
        }
        nivel++;
    }

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
}
