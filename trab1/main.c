#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 1031
#define VAZIO -1

int hash_function(long cpf, int tentativa) {
    unsigned int temp = ((unsigned int)(cpf >> 32)) ^ ((unsigned int) cpf);
    return (3*temp + tentativa) % TABLE_SIZE;
}

void solve_collision(long* table, long cpf, int* collision_count, int num_chaves){

    // registra toda vez que acontece uma colisao, mesmo em tentativas subsequentes
    // int i;
    // for(i=0; collision_num[i] != VAZIO;) i++;
    // collision_num[i] = num_chaves;

    int hash;
    int tentativa = 1;
    do {
        // se tentou demais a tabela esta efetivamente cheia
        if (tentativa > TABLE_SIZE){
            printf("Função hash falhou\n");
            exit(1);
        }
        collision_count[num_chaves] += 1;

        hash = hash_function(cpf, tentativa);
        tentativa++;
    } while(table[hash] != VAZIO);

    table[hash] = cpf;
}

int main() {
    int num_chaves = 0;
    int total_collisions;

    // guarda onde aconteceram as colisões para mostrar depois
    // int collision_num[TABLE_SIZE];
    int collision_count[TABLE_SIZE];

    // hash table
    long hash_table[TABLE_SIZE];

    // inicializa os vetores
    for(int i = 0; i< TABLE_SIZE; i++){
        hash_table[i] = VAZIO;
        // collision_num[i] = VAZIO;
        collision_count[i] = 0;
    }
    
    FILE *file = fopen("cpfs.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    long int cpf;
    while (fscanf(file, " %ld", &cpf) == 1) {
        printf("colocando cpf %ld\n", cpf);
        int hash = hash_function(cpf, 0);
        if (hash_table[hash] != VAZIO){
            total_collisions++;
            solve_collision(hash_table, cpf, collision_count, num_chaves);
        }
        else{
            hash_table[hash] = cpf;
        }
        num_chaves++;
    }

    // close file
    fclose(file);

    FILE *output = fopen("hash.csv", "w");
    if (output == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    FILE *collisions = fopen("colisoes.csv", "w");
    if (collisions == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fprintf(output, "cpf\n");
    fprintf(collisions, "colision,count\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        fprintf(output, "%ld\n",hash_table[i]);
        if (i < num_chaves) fprintf(collisions, "%d,%d\n",i+1,collision_count[i]);
    }

    fclose(output);
    fclose(collisions);

    printf("Houve %d colisões no total\n", total_collisions);
    printf("Sobraram %d posições vazias no vetor\n", TABLE_SIZE - 1000);
    return 0;
}