#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// condicao quanto mais baixo mais critico.
typedef struct {
    int chegada;
    unsigned short condicao;
} Paciente;

struct fila_paciente {
    Paciente* paciente;
    struct fila_paciente* prox;
};
typedef struct fila_paciente Fila;

Fila* insere_paciente(Paciente* p, Fila* f);
Fila* atende_paciente(int pos, Fila* f);
char* acha_condicao(unsigned short condicao);
void exibe_paciente(Paciente* p);
void exibe_fila(Fila* f);


Fila* insere_paciente(Paciente* p, Fila* f) {
    Fila* pf = malloc(sizeof(Fila));
    pf->paciente = p;
    pf->prox = NULL;

    // caso de fila vazia
    if (f == NULL) return pf;

    // guarda o comeco da fila
    Fila* prim = f;
    Fila* ant = NULL;

    // procura na fila algum paciente com a condicao mais leve que p
    while (f != NULL && f->paciente->condicao <= p->condicao) {
        ant = f;
        f = f->prox;
    }

    // Insere o novo paciente
    if (ant != NULL) {
        ant->prox = pf;
        pf->prox = f;
    }
    else {
        pf->prox = prim;
        return pf;
    }

    // se nao achou, insere no final
    if (f == NULL) {
        ant->prox = pf;
    }
    return prim;
}

Fila* atende_paciente(int pos, Fila* f) {
    Fila* ant = f;
    Fila* prim = f;
    while (f != NULL) {
        if (f->paciente->chegada == pos){
            ant->prox = f->prox;
            break;
        }

        ant = f;
        f = f->prox;
    }
    return prim;
}

char* acha_condicao(unsigned short condicao) {
    if (condicao == 0) return "Vermelha";
    else if (condicao == 1) return "Amarela";
    else if (condicao == 2) return "Verde";
    return "";
}

void exibe_paciente(Paciente* p) {
    printf("%d - %s\n", p->chegada, acha_condicao(p->condicao));
    return;
}

void exibe_fila(Fila* f) {
    int contagem[] = {0, 0, 0};
    printf("\nA fila está assim:\n");
    while (f != NULL) {
        exibe_paciente(f->paciente);
        contagem[f->paciente->condicao]++;
        f = f->prox;
    }
    for (int i = 0; i < 3; i++) {
        if (contagem[i]) printf("\npacientes %s na fila: %d", acha_condicao(i), contagem[i]);
    };
    printf("\n\n");
    return;
}

void free_fila(Fila* f) {
    Fila* p = NULL;
    while(f !=NULL) {
        p = f->prox;
        free(f->paciente);
        free(f);
        f = p;
    }
    return;
}

int main(void) {
    // ler o arquivo de pacientes
    FILE* entradas = fopen("pacientes.txt", "r");
    if (entradas == NULL) exit(1);

    Fila* fila = NULL;
    char cor[100], atividade;
    int pos, condicao;

    while (fscanf(entradas, " %c - %d - %s", &atividade, &pos, cor) == 3) {
        if (atividade == 'E') {
            if (strcmp(cor, "Vermelha") == 0) condicao = 0;
            else if (strcmp(cor, "Amarela") == 0) condicao = 1;
            else if (strcmp(cor, "Verde") == 0) condicao = 2;
            else exit(2);
            Paciente* p = malloc(sizeof(Paciente));
            p->chegada = pos;
            p->condicao = condicao;
            fila = insere_paciente(p, fila);
        }
        else if (atividade == 'S') {
            atende_paciente(pos, fila);
        }


        exibe_fila(fila);
    }
    free_fila(fila);
    fclose(entradas);
}