#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../headers/matrix.h"
#include "../headers/array.h"

// Definições de cores ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

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
    // Aloca memória para o array de ponteiros para as linhas
    double **matrix = (double **)malloc(m * sizeof(double *));

    // Verifica se a alocação para o array de ponteiros foi bem-sucedida
    if (matrix == NULL)
    {
        perror("Failed to allocate memory for row pointers");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para cada linha
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));

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
    }

    return matrix;
}

void freeMatrixDouble(double **matrix, int m)
{
    // Libera a memória de cada linha
    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    // Libera o array de ponteiros para as linhas
    free(matrix);
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

double **copyMatrix(double **matrix, int m, int n)
{
    // Aloca nova matriz
    double **newMatrix = allocateMatrixDouble(m, n);

    // Copia valores da matriz original para a nova
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

double **scheduleMatrix(double **matrix, int m, int n)
{
    double **scheduledMatrix = copyMatrix(matrix, m, n);

    // Escalonamento
    int row = 0;

    do
    {
        int col = row;

        // Divide a linha atual por ela mesmo para criar o pivô 1
        double termToPivot = scheduledMatrix[row][row];

        if (termToPivot != 0)
        {
            if (termToPivot != 1)
            {
                for (int j = 0; j < n; j++)
                {
                    // Operador ternário apenas para remover sinal de negativo do zero
                    scheduledMatrix[row][j] = (scheduledMatrix[row][j] / termToPivot != 0) ? scheduledMatrix[row][j] / termToPivot : 0;
                }
            }

            // Divide demais linhas pela linha do pivô
            for (int i = 0; i < m; i++)
            {
                if (i != row)
                {
                    double termo = scheduledMatrix[i][col];

                    if (termo != 0)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            // Operador ternário apenas para remover sinal de negativo do zero
                            scheduledMatrix[i][j] = (scheduledMatrix[i][j] - (termo * scheduledMatrix[row][j]) != 0) ? scheduledMatrix[i][j] - (termo * scheduledMatrix[row][j]) : 0;
                        }
                    }
                }
            }
        }

        row++;

    } while (row < m);

    return scheduledMatrix;
}

int rankMatrix(double **matrix, int m, int n)
{
    int rank = m;
    for (int i = 0; i < m; i++)
    {
        bool isZero = true;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != 0)
            {
                isZero = false;
            }
        }

        if (isZero)
            rank--;
    }
    return rank;
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
                    if (isNumeric(system[i][x]) || system[i][x] == '.')
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
                    if (isNumeric(system[i][x]) || system[i][x] == '.')
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

void classifyScheduledMatrix(double **matrix, int m, int n)
{
    // Valida se matriz escalonada representa um sistema impossível!
    /**
     * Verificando se em alguma linha todas as variáveis são 0 e o resultado não.
     */
    for (int i = 0; i < m; i++)
    {
        bool allVariablesZero = true;
        for (int j = 0; j < n - 1; j++)
        {
            if (matrix[i][j] != 0)
            {
                allVariablesZero = false;
                break;
            }
        }

        if (allVariablesZero && matrix[i][n - 1] != 0)
        {
            printf(GREEN "\n> Classificacao do sistema: " RESET);
            printf("(SI) Sistema impossivel!\n");
            return;
        }
        else if (allVariablesZero && matrix[i][n - 1] == 0)
        {
            printf(GREEN "\n> Classificacao do sistema: " RESET);
            printf("(SPI) Sistema possivel e indeterminado!\n");
            return;
        }
    }

    printf(GREEN "\n> Classificacao do sistema: " RESET);
    printf("(SPD) Sistema possivel e determinado!\n");
}

double calcDeterminant(double **matrix, int m)
{
    // Calculo do determinante.

    int row = 0, columAdd = 0;
    double determinant = 0;

    if (m == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i <= 2 / 2 - 1)
            {
                determinant += matrix[i][i - i] * matrix[1 - i][1];
            }
            else
            {
                determinant -= matrix[i][i - i] * matrix[1 - i][1];
            }
        }
    }
    else
    {
        columAdd = 0;
        double matrixExpand[3][5];
        for (int i = 0; i < 3; i++)
        {
            columAdd = 0;
            for (int j = 0; j < 5; j++)
            {
                if (j > 2)
                {
                    matrixExpand[i][j] = matrix[i][columAdd];
                    columAdd++;
                }
                else
                {
                    matrixExpand[i][j] = matrix[i][j];
                }
            }
        }
        for (int j = 0; j < 6; j++)
        {
            if (j <= 6 / 2 - 1)
            {
                determinant += matrixExpand[0][j] * matrixExpand[1][j + 1] * matrixExpand[2][j + 2];
            }
            else
            {
                determinant -= matrixExpand[0][j - 1] * matrixExpand[1][j - 2] * matrixExpand[2][j - 3];
            }
        }
    }
    return determinant;
}

void classifyTransformation(double **matrix, int m)
{
    // Matrizes N x N representam sempre imagens e dominios N x N, logo, ou atendem os requisitos para ser injetora e sobrejetora = bijetora
    // ou não atendem nenhum, e assim são singulares.
    double determinant = calcDeterminant(matrix, m);
    double **scheduledMatrix = scheduleMatrix(matrix, m, m + 1);
    int rank = rankMatrix(scheduledMatrix, m, m + 1);

    if (determinant != 0 && rank == m)
    {
        printf("A matriz e bijetora, pois e quadrada e seu determinate e diferente de 0!\n");
    }
    else if (determinant == 0 && rank < m)
    {
        printf("A matriz e singular (Nao representa transformacao linear), pois seu determinate e igual a 0!\n");
    }
}

void baseVerification(int m, int n, int det, double **matrix)
{
    double **scheMatrix = scheduleMatrix(matrix, m, n);
    int rank = rankMatrix(scheMatrix, m, n);

    if (rank == m && det != 0)
    {
        if (m == 3)
        {

            printf("O conjunto de vetores que pode ser usados como base!\n"
                   "\nBase: B = {(%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf), (%.2lf, %.2lf, %.2lf)}\n",
                   matrix[0][0], matrix[0][1], matrix[0][2],
                   matrix[1][0], matrix[1][1], matrix[1][2],
                   matrix[2][0], matrix[2][1], matrix[2][2]);
        }
        else if (m == 2)
        {
            printf("O conjunto de vetores que pode ser usados como base!\n"
                   "\nBase: B = {(%.2lf, %.2lf), (%.2lf, %.2lf)}\n",
                   matrix[0][0], matrix[0][1],
                   matrix[1][0], matrix[1][1]);
        }
    }
    else
    {
        printf("O conjunto de vetores que pode ser usado como base!\n");
    }
}

double *calcAutovalue(double **matrix, int m, int n){

   if(m == 2){
        double *autoValues = allocateVetor(2);
        double **matrixCop = copyMatrix(matrix, m, n);
        double termB = 0, termC = 0;

        termB = (-matrixCop[0][0]) - (matrixCop[1][1]);
        termC = calcDeterminant(matrix, m);

        autoValues[0] = (-termB + sqrt((termB * termB) - 4 * termC)) / 2;
        autoValues[1] = (-termB - sqrt((termB * termB) - 4 * termC)) / 2;

        return autoValues;
   } else if(m == 3){
        double *autoValues = allocateVetor(3);
        double **matrixCop = copyMatrix(matrix, m, n);
        double a = 1; // Coeficiente de λ^3 (é sempre 1 para matriz 3x3)
        double b, c, d;

        // Cálculo dos coeficientes b, c, d a partir da matriz
        b = - (matrixCop[0][0] + matrixCop[1][1] + matrixCop[2][2]);
        c = matrixCop[0][0] * matrixCop[1][1] + matrixCop[1][1] * matrixCop[2][2] + matrixCop[2][2] * matrixCop[0][0]
            - (matrixCop[0][1] * matrixCop[1][0] + matrixCop[1][2] * matrixCop[2][1] + matrixCop[2][0] * matrixCop[0][2]);
        d = - (matrixCop[0][0] * (matrixCop[1][1] * matrixCop[2][2] - matrixCop[1][2] * matrixCop[2][1]) 
            + matrixCop[1][1] * (matrixCop[0][0] * matrixCop[2][2] - matrixCop[0][2] * matrixCop[2][0]) 
            + matrixCop[2][2] * (matrixCop[0][0] * matrixCop[1][1] - matrixCop[0][1] * matrixCop[1][0]));

        // Usando a fórmula de Cardano para resolver a equação cúbica
        double q = (3 * c / a - (b * b) / (a * a)) / 9;
        double r = (-27 * d / a + b * (9 * c / a - 2 * (b * b) / (a * a))) / 54;

        double discriminante = q * q * q + r * r;

        if (discriminante > 0) {
            // Uma raiz real e duas complexas
            double s = cbrt(r + sqrt(discriminante));
            double t = cbrt(r - sqrt(discriminante));
            autoValues[0] = s + t - b / (3 * a);
            autoValues[1] = -(s + t) / 2 - b / (3 * a);
            autoValues[2] = -(s + t) / 2 - b / (3 * a);
        } else {
            // Três raízes reais
            double theta = acos(r / sqrt(-q * q * q));
            autoValues[0] = 2 * sqrt(-q) * cos(theta / 3) - b / (3 * a);
            autoValues[1] = 2 * sqrt(-q) * cos((theta + 2 * M_PI) / 3) - b / (3 * a);
            autoValues[2] = 2 * sqrt(-q) * cos((theta + 4 * M_PI) / 3) - b / (3 * a);
        }
        return autoValues;
    }
}