#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/matrix.h"
#include "../headers/array.h"

// enum e struct
enum Dimensao
{
    DOIS = 2,
    TRES = 3
};

enum Operadores
{
    ADICAO = '+',
    SUBTRACAO = '-',
    IGUAL = '='
};

bool isNumeric(char c)
{
    return c > 47 && c < 58;
}

bool isOperator(char c)
{
    return c == ADICAO || c == SUBTRACAO || c == IGUAL;
}

double strtoDouble(char *str)
{
    char *endptr;
    return strtod(str, &endptr);
}

double **allocateMatrixDouble(int m, int n)
{
    double **matrix = (double **)malloc(m * sizeof(double *));

    for (int i = 0; i < m; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }

    return matrix;
}

char **allocateMatrixChar(int m, int n)
{
    // Aloca memória para o array de ponteiros para as linhas
    char **matrix = (char **)malloc(m * sizeof(char *));

    // Verifica se a alocação para as linhas foi bem-sucedida
    if (matrix == NULL)
    {
        perror("Failed to allocate memory for rows");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para cada linha e inicializa com '\0'
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (char *)malloc(n * sizeof(char));

        // Verifica se a alocação para as colunas foi bem-sucedida
        if (matrix[i] == NULL)
        {
            perror("Failed to allocate memory for columns");
            // Libera a memória já alocada antes de sair
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }

        // Inicializa a linha com '\0'
        memset(matrix[i], '\0', n * sizeof(char));
    }

    return matrix;
}

void freeMatrixChar(char **matrix, int m)
{
    // Libera a memória de cada linha
    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    // Libera o array de ponteiros para as linhas
    free(matrix);
}

void printMatrixDouble(double **matrix, int m, int n)
{
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixChar(char **matrix, int m)
{
    for (int i = 0; i < m; i++)
    {
        printString(matrix[i]);
    }
}

double **scheduleMatrix(double **matrix, int m, int n)
{

    // Escalonamento
    int row = 0;

    do
    {
        int col = row;

        // Divide a linha atual por ela mesmo para criar o pivô 1
        double termToPivot = matrix[row][row];

        if (termToPivot != 1)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[row][j] /= termToPivot;
            }
        }

        // Divide demais linhas pela linha do pivô
        for (int i = 0; i < m; i++)
        {
            if (i != row)
            {
                double termo = matrix[i][col];
                for (int j = 0; j < n; j++)
                {
                    matrix[i][j] -= termo * matrix[row][j];
                }
            }
        }

        row++;

    } while (row < m);

    return matrix;
}

int rankMatrix(double **matrix, int m, int n)
{
}

double **systemToMatrix(char **system, int m)
{

    double **matrix = allocateMatrixDouble(m, m + 1);

    for (int i = 0; i < m; i++)
    {
        // Valida se sistema informado na linha é válido
        int coefsAdd = 0;
        int len = strlen(system[i]);
        for (int j = 0; j < len; j++)
        {

            // Reserva coef. atual da linha
            char number[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
            int charsInNumber = 0;

            // Coleta coef. negativo
            if (system[i][j] == SUBTRACAO)
            {
                number[0] = SUBTRACAO;
                charsInNumber++;

                for (int x = j + 1; x < len; x++)
                {
                    if (isNumeric(system[i][x]))
                    {
                        number[charsInNumber] = system[i][x];
                        charsInNumber++;
                    }
                    else if (system[i][x] == ' ')
                    {
                        continue;
                    }
                    else
                    {
                        j += x - j;
                        break;
                    }
                }

                matrix[i][coefsAdd] = strtoDouble(number);
                coefsAdd++;
            }
            else if (isNumeric(system[i][j]))
            {
                number[0] = system[i][j];
                for (int x = j + 1; x < len; x++)
                {
                    if (isNumeric(system[i][x]))
                    {
                        number[x - j] = system[i][x];
                    }
                    else
                    {
                        j += x - j;
                        break;
                    }
                }
                matrix[i][coefsAdd] = strtoDouble(number);
                coefsAdd++;
            }
        }
    }
    return matrix;
}