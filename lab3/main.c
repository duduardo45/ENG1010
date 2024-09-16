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

Nodo *realiza_insercao(Nodo *p, int x)
{
    Nodo *aux = (Nodo *)malloc(sizeof(Nodo));
    aux->chave = x;
    aux->esq = aux->dir = NULL;
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
        inserido = realiza_insercao(nodo_para_inserir->esq, x);
        return insere_fila(fila, inserido);
    }
    else
    {
        inserido = realiza_insercao(nodo_para_inserir->dir, x);
        fila = insere_fila(fila, inserido);
        return fila->prox;
    }
}

Nodo *busca_nodo(Nodo *arvore, int chave)
{
    if (arvore == NULL || arvore->chave == chave)
    {
        return arvore;
    }
    Nodo *a = busca_nodo(arvore->esq, chave);
    Nodo *b = busca_nodo(arvore->dir, chave);
    if (a != NULL)
    {
        return a;
    }
    else if (b != NULL)
    {
        return b;
    }
    else
    {
        return NULL;
    }
}

Nodo *cria(int c, Nodo *sae, Nodo *sad)
{
    Nodo *p = (Nodo *)malloc(sizeof(Nodo));
    p->chave = c;
    p->esq = sae;
    p->dir = sad;
    return p;
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
    Nodo *arvore = NULL;
    Elemento *fila = NULL;
    fila = insere(fila, arvore, 10);
    exibe_preordem(arvore);
}