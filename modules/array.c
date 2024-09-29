#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/array.h"

void printString(char *arr)
{
    int len = strlen(arr);
    for (int i = 0; i < len; i++)
    {
        printf("%c", arr[i]);
    }

    printf("\n");
}

void printArrayDouble(double *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%.2lf\t", arr[i]);
    }

    printf("\n");
}

// Função que retorna o índice de um caracter em uma string, e -1 caso não encontre
int stringFindIndex(char *arr, char c)
{
    int len = strlen(arr);
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == c)
            return i;
    }
    return -1;
}

double* allocateVetor(int tamanho) {
    double* vetor = (double*)malloc(tamanho * sizeof(double));
    if (vetor == NULL) {
        printf("Erro: falha ao alocar memória.\n");
        exit(1); // Encerrar o programa se a alocação falhar
    }
    
    // Inicializar todos os elementos com zero
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = 0.0;
    }
    
    return vetor;
}
