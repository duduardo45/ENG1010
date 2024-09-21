/*

Tarefa 3 – Árvores Binárias

a)       a) Inserir por nível as chaves: 10, 5, 15, 3, 7, 13, 20, 1, 4, 6 em uma árvore binária

b)      b) Adicionar à estrutura o nível de cada nó e listar a estrutura

c)       c) Adicionar à estrutura a altura de cada nó e listar a estrutura

d)      d) Adicionar à estrutura o ponteiro para o pai de cada nó e listar a estrutura

*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct nodo
{
    int chave;
    int nivel;
    int altura;
    struct nodo *pai;
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

Nodo* cria_nodo(int x, int n, int h, Nodo* pai, Nodo* esq, Nodo* dir) {

    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->chave = x;
    nodo->nivel = n;
    nodo->altura = h;
    nodo->pai = pai;
    nodo->esq = esq;
    nodo->dir = dir;
    return nodo;
}

Elemento* cria_elemento(Nodo* nodo, Elemento* prox) {

    Elemento* el = (Elemento *)malloc(sizeof(Elemento));
    el->nodo = nodo;
    el->prox = prox;
    return el;
}

void incrementa_altura(Nodo* p) {
    p->altura++;
    while (p->pai != NULL) {
        if (p->pai->esq == p) {
            p = p->pai;
            p->altura++;
        }
        else return;
    }
    return;
}

Nodo *realiza_insercao(Nodo *p, int x, char direcao)
{
    Nodo *aux = cria_nodo(x,p->nivel+1,0,p,NULL,NULL);
    if (direcao == 'e') {
        p->esq = aux;
        incrementa_altura(p);
    } else if (direcao == 'd') {
        p->dir = aux;
    }
    return aux;
}

Elemento *insere_fila(Elemento *fila, Nodo *nodo)
{
    Elemento *aux;
    if (fila == NULL)
    {
        aux = cria_elemento(nodo, NULL);
        return aux;
    }
    Elemento *atual = fila;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    aux = cria_elemento(nodo, NULL);
    atual->prox = aux;
    return fila;
}

Elemento *insere(Elemento *fila, Nodo **pp, int x)
{
    Nodo *p = *pp;
    if (p == NULL)
    {
        p = cria_nodo(x,0,0,NULL,NULL,NULL);
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
        
    printf("ptr_no=%p, chave=%d\tnivel=%d\taltura=%d pai=", p, p->chave, p->nivel, p->altura);
    printf("%p\t",p->pai);
    if (p->pai == NULL) printf("\t");
    printf("esq=");
    printf("%p\t",p->esq);
    if (p->esq == NULL) printf("\t");
    printf("dir=%p\n",p->dir);

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