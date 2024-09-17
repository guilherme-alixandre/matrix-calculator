#include <stdio.h>
#include <string.h>
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
