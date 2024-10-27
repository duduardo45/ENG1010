#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 1543
#define VAZIO -1

long int hash_function(long int cpf, int tentativa) {
    return cpf % TABLE_SIZE;
}

void solve_collision(long int* table, long int cpf, int* collision_num, int num_chaves){
    int i;
    for(i=0; collision_num[i] == VAZIO; i++);
    collision_num[i] = num_chaves;

    int hash;
    int tentativa = 1;
    do {
        hash = hash_function(cpf, tentativa);
        tentativa++;
    } while(table[hash] != VAZIO);

    if (tentativa > TABLE_SIZE){
        printf("Função hash falhou\n");
        exit(1);
    }
    table[hash] = cpf;
}

int main() {
    int num_chaves = 0;

    int collision_num[TABLE_SIZE];

    // hash table
    long int hash_table[TABLE_SIZE];

    for(int i = 0; i< TABLE_SIZE; i++){
        hash_table[i] = VAZIO;
    }

    for(int i = 0; i< TABLE_SIZE; i++){
        collision_num[i] = VAZIO;
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
            solve_collision(hash_table, cpf, collision_num, num_chaves);
        }
        else{
            hash_table[hash] = cpf;
        }
        num_chaves++;
    }

    // close file
    fclose(file);
    return 0;
}