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
    int nv;               /* numero de nos ou vertices */
    int na;               /* numero de arestas */
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

int *busca_em_amplitude(Grafo *grafo, int no_inicio)
{
    int *visitados = (int *)malloc(grafo->nv * sizeof(int));
    int *fila = (int *)malloc(grafo->nv * sizeof(int));
    int inicio_fila = 0;
    int fim_fila = 0;
    int contador = 0;

    // vetor visitados dá a ordem de visitação

    // Inicializa vetor de visitados com -1
    for (int i = 0; i < grafo->nv; i++)
    {
        visitados[i] = -1;
    }

    // Adiciona no inicial na fila e marca como visitado
    fila[fim_fila++] = no_inicio;
    visitados[contador++] = no_inicio;

    // Enquanto houver nos na fila
    while (inicio_fila < fim_fila)
    {
        int no_atual = fila[inicio_fila++];

        // Percorre todos os vizinhos do no atual
        for (Viz *v = grafo->viz[no_atual]; v != NULL; v = v->prox)
        {
            int ja_visitado = 0;

            // Verifica se ja foi visitado
            for (int i = 0; i < contador; i++)
            {
                if (visitados[i] == v->noj)
                {
                    ja_visitado = 1;
                    break;
                }
            }

            // Se nao foi visitado, adiciona na fila e marca como visitado
            if (!ja_visitado)
            {
                fila[fim_fila++] = v->noj;
                visitados[contador++] = v->noj;
            }
        }
    }

    free(fila);
    return visitados;
}


int find(int* pai, int v) {
    if (pai[v] == v)
        return v;
    return pai[v] = find(pai, pai[v]);
}

// Função para unir dois conjuntos
void union_sets(int* pai, int u, int v) {
    int raiz_u = find(pai, u);
    int raiz_v = find(pai, v);
    if (raiz_u != raiz_v) {
        pai[raiz_v] = raiz_u; // União simples
    }
}

void exibe_kruskal(Grafo *grafo)
{
    // ordena as arestas
    Viz **arestas = (Viz **)malloc(grafo->na * sizeof(Viz *));

    int index = 0;

    // criando a lista de arestas
    for (int i = 0; i < grafo->nv; i++)
    {
        Viz *atual = grafo->viz[i];
        while (atual != NULL)
        {
            if (i < atual->noj)
            { // Evita arestas duplicadas em grafos não direcionados
                arestas[index++] = atual;
            }
            atual = atual->prox;
        }
    }

    // ordenando as arestas
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = i + 1; j < index; j++)
        {
            if (arestas[i]->peso > arestas[j]->peso)
            {
                Viz *aux = arestas[i];
                arestas[i] = arestas[j];
                arestas[j] = aux;
            }
        }
    }

    // implementar kruskal com union find
    int *pai = (int *)malloc(grafo->nv * sizeof(int));
    for (int i = 0; i < grafo->nv; i++)
    {
        pai[i] = i;
    }

    printf("Arestas na árvore geradora mínima (Kruskal):\n");
    for (int i = 0; i < index; i++)
    {
        int u = arestas[i]->noj; // nó inicial da aresta
        int v = -1;             // nó final será identificado

        // Encontrar o índice do vizinho no vetor grafo->viz
        for (int j = 0; j < grafo->nv; j++)
        {
            Viz *atual = grafo->viz[j];
            while (atual != NULL)
            {
                if (atual == arestas[i])
                {
                    v = j; // Encontrado o nó final (posição no vetor grafo->viz)
                    break;
                }
                atual = atual->prox;
            }
            if (v != -1)
                break; // Já encontrado, parar a busca
        }

        if (v == -1)
        {
            fprintf(stderr, "Erro: Não foi possível determinar o nó final.\n");
            exit(1);
        }

        // Verificar se os nós u e v pertencem a componentes diferentes
        if (find(pai, u) != find(pai, v))
        {
            printf("Aresta (%d, %d) com peso %.2f\n", u, v, arestas[i]->peso);
            union_sets(pai, u, v);
        }
    }
}

int main(void)
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->nv = NUMERO_NOS;
    grafo->na = 0;
    for (int i = 0; i < NUMERO_NOS; i++)
        grafo->viz[i] = NULL;
    adicionar_link(grafo, 0, 1, 4.0);
    adicionar_link(grafo, 0, 8, 8.0);
    adicionar_link(grafo, 1, 8, 11.0);
    adicionar_link(grafo, 1, 3, 8.0);
    adicionar_link(grafo, 3, 4, 7.0);
    adicionar_link(grafo, 8, 2, 7.0);
    adicionar_link(grafo, 8, 7, 1.0);
    adicionar_link(grafo, 2, 7, 6.0);
    adicionar_link(grafo, 2, 3, 2.0);
    adicionar_link(grafo, 3, 6, 4.0);
    adicionar_link(grafo, 6, 5, 10.0);
    adicionar_link(grafo, 4, 5, 9.0);
    adicionar_link(grafo, 7, 6, 2.0);
    adicionar_link(grafo, 4, 6, 14.0);
    // adicionar os links reversos agora
    adicionar_link(grafo, 1, 0, 4.0);
    adicionar_link(grafo, 8, 0, 8.0);
    adicionar_link(grafo, 8, 1, 11.0);
    adicionar_link(grafo, 3, 1, 8.0);
    adicionar_link(grafo, 4, 3, 7.0);
    adicionar_link(grafo, 2, 8, 7.0);
    adicionar_link(grafo, 7, 8, 1.0);
    adicionar_link(grafo, 7, 2, 6.0);
    adicionar_link(grafo, 3, 2, 2.0);
    adicionar_link(grafo, 6, 3, 4.0);
    adicionar_link(grafo, 5, 6, 10.0);
    adicionar_link(grafo, 5, 4, 9.0);
    adicionar_link(grafo, 6, 7, 2.0);
    adicionar_link(grafo, 6, 4, 14.0);
    int *visitados = busca_em_amplitude(grafo, 0);
    printf("Busca em amplitude:\n");
    for (int i = 0; i < NUMERO_NOS; i++)
    {
        printf("%d ", visitados[i]);
    }
    printf("\n");

    exibe_kruskal(grafo);
}
