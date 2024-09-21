#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct nodo
{
    int chave;
    struct nodo *esq;
    struct nodo *dir;
};
typedef struct nodo Nodo;

struct elemento_fila
{
    Nodo *nodo;
    struct elemento_fila *prox;
};
typedef struct elemento_fila Elemento;

Elemento *insere_fila(Elemento *fila, Nodo *nodo)
{
    Elemento *aux;
    if (fila == NULL)
    {
        aux = (Elemento *)malloc(sizeof(Elemento));
        aux->nodo = nodo;
        aux->prox = NULL;
        return aux;
    }
    Elemento *atual = fila;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    aux = (Elemento *)malloc(sizeof(Elemento));
    aux->nodo = nodo;
    aux->prox = NULL;
    atual->prox = aux;
    return fila;
}

Nodo *realiza_insercao(Nodo *p, int x, char direcao)
{
    Nodo *aux = (Nodo *)malloc(sizeof(Nodo));
    aux->chave = x;
    aux->esq = aux->dir = NULL;
    if (direcao == 'e')
        p->esq = aux;
    else if (direcao == 'd')
        p->dir = aux;
    return aux;
}

Elemento *insere(Elemento *fila, Nodo **pp, int x)
{
    Nodo *p = *pp;
    if (p == NULL)
    {
        p = (Nodo *)malloc(sizeof(Nodo));
        p->chave = x;
        p->esq = p->dir = NULL;
        *pp = p;
        return insere_fila(fila, p);
    }
    Nodo *nodo_para_inserir = fila->nodo;
    Nodo *inserido;
    if (nodo_para_inserir->esq == NULL)
    {
        inserido = realiza_insercao(nodo_para_inserir, x, 'e');
        return insere_fila(fila, inserido);
    }
    else
    {
        inserido = realiza_insercao(nodo_para_inserir, x, 'd');
        fila = insere_fila(fila, inserido);
        return fila->prox;
    }
}

void exibe_preordem(Nodo *p)
{
    if (p == NULL)
        printf("arvore nao foi criada\n");
    printf("ptr_no=%p, chave=%d esq=%p dir=%p\n", p, p->chave, p->esq, p->dir);
    if (p->esq != NULL)
        exibe_preordem(p->esq);
    if (p->dir != NULL)
        exibe_preordem(p->dir);
}

int main(void)
{
    int chaves[10] = {10, 5, 15, 3, 7, 13, 20, 1, 4, 6};
    Nodo *arvore = NULL;
    Elemento *fila = NULL;
    for (int i = 0; i < 10; i++)
    {
        fila = insere(fila, &arvore, chaves[i]);
        exibe_preordem(arvore);
        printf("\n\n");
    }

    return 0;
}