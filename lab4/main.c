/*

Tarefa 4 – Árvores binárias, árvores binárias de busca e árvores AVL

1) Fazer programa em C para incluir as chaves: 15, 17, 3, 5, 2, 20, 25, 13, 10 e 16 em uma árvore binária qualquer e calcular o número de nós das sub árvores de cada nó, armazenando este valor no nó correspondente. Exiba a árvore inicial (com zeros no número de sub árvores) e a árvore resultante.

2) Verificar se uma dada árvore é binária de busca ou não, exibindo mensagem correspondente.

3) Verificar se uma dada árvore é AVL ou não, exibindo mensagem correspondente.

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
    int qtd_esq;
    int qtd_dir;
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

Nodo* cria_nodo(int x, int n, int h, Nodo* pai) {

    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->chave = x;
    nodo->nivel = n;
    nodo->altura = h;
    nodo->qtd_esq = 0;
    nodo->qtd_dir = 0;
    nodo->pai = pai;
    nodo->esq = NULL;
    nodo->dir = NULL;
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

void incrementa_qtd(Nodo* p) {

    while (p->pai != NULL) {
        if (p->pai->esq == p) {
            p = p->pai;
            p->qtd_esq++;
        }
        else {
            p = p->pai;
            p->qtd_dir++;
        }
    }

    return;
}

Nodo *realiza_insercao(Nodo *p, int x, char direcao)
{
    Nodo *aux = cria_nodo(x,p->nivel+1,0,p);
    if (direcao == 'e') {
        p->esq = aux;
        incrementa_altura(p);
        incrementa_qtd(aux);
    } else if (direcao == 'd') {
        p->dir = aux;
        incrementa_qtd(aux);
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
        p = cria_nodo(x,0,0,NULL);
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

int checa_ABB(Nodo* p) {
    int qual_null = 0;
    if (p->esq == NULL && p->dir == NULL) return 1;
    if (p->esq == NULL) qual_null = 1;
    else if (p->esq->chave >= p->chave) return 0;
    if (p->dir == NULL) qual_null = 2;
    else if (p->dir->chave <= p->chave) return 0;
    if (qual_null == 1) return checa_ABB(p->dir);
    else if (qual_null == 2) return checa_ABB(p->esq);
    return checa_ABB(p->esq) & checa_ABB(p->dir);
}

void exibe_checa_ABB(Nodo* raiz) {

    int res = checa_ABB(raiz);
    if (res) printf("esta arvore e ABB\n");
}

void checa_AVL(Nodo* p) {

    return;
}

void exibe_preordem(Nodo *p)
{
    if (p == NULL)
        printf("arvore nao foi criada\n");
        
    printf("ptr_no=%p, chave=%d\tnivel=%d\taltura=%d qtd_esq=%d qtd_dir=%d pai=",\
                    p, p->chave, p->nivel, p->altura,p->qtd_esq,p->qtd_dir);
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
    int chaves[10] = {15, 17, 3, 5, 2, 20, 25, 13, 10, 16};
    Nodo *arvore = NULL;
    Elemento *fila = NULL;
    for (int i = 0; i < 10; i++)
    {
        fila = insere(fila, &arvore, chaves[i]);
        exibe_preordem(arvore);
        exibe_checa_ABB(arvore);
        printf("\n\n");
    }

    return 0;
}