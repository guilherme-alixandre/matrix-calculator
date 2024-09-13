#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int n = 0;

// enum e struct
enum Dimensao
{
	DOIS = 2,
	TRES = 3
};

typedef enum Operadores
{
	ADICAO = '+',
	SUBTRACAO = '-',
	IGUAL = '='
};

// funções
void inputDimension()
{
	do
	{
		printf("Informe a dimensao da matriz (2 ou 3):");
		scanf("%d", &n);
		if (n != DOIS && n != TRES)
		{
			printf("Entrada Invalida!!\n");
		}
		getchar();
	} while (n != DOIS && n != TRES);
}

bool isNumeric(char c)
{
	return c > 47 && c < 58;
}

bool isOperator(char c)
{
	return c == ADICAO || c == SUBTRACAO || c == IGUAL;
}

void printMatrizFinal(int x, double **matriz)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x + 1; j++)
		{
			printf("%.2lf ", matriz[i][j]);
		}
		printf("\n");
	}
}

double strtoDouble(char *y)
{
	char *endptr;
	return strtod(y, &endptr);
}

#endif

/*
1. Criar um validador de coluna zerada.

*/