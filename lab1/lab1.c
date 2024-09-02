#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int compara_int(const void* a, const void* b) {
    int* pa = (int*) a;
    int* pb = (int*) b;
    if (*pa < *pb) return -1;
    else if (*pa > *pb) return 1;
    return 0;
}

int busca_no_vetor(int* v, int valor, int tam) {
    for (int i = 0; i < tam; i++) {
        if (v[i] == valor) return i;
    }
    return -1;
}

int main(void) {
    
    clock_t start, end, diff;
    srand(time(NULL));

    start = clock();
    int v[10000];
    for (int i = 0; i<10000; i++) {
        v[i] = rand() % 10000;
    }

    qsort(v,10000, sizeof(int), compara_int);
    end = clock();
    diff = end - start;

    for (int i = 0; i < 10000; i++) {
        printf("%d ", v[i]);
    }
    printf("tempo levado: %d\n", diff);

    srand(time(NULL));
    for (int i = 0; i<10000; i++) {
        v[i] = rand() % 10000;
    }
    int idx;
    for (int i =0; i<10; i++){
        
        int k = rand() % 10000;
        start = clock();
        idx = busca_no_vetor(v, k, 10000);
        end = clock();
        diff = end - start;
        printf("procurando %d:\n", k);
        if (idx == -1) printf("nao foi achado o valor %d no vetor, demorando %d\n", k, diff);
        else printf("valor %d foi achado na posicao %d do vetor, demorando %d\n", k, idx, diff);
    }

    return 0;
}