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

            if (m == 2)
            {
                char signal = matrix[0][1] < 0 ? '+' : '-';
                printf("\nx1 = %.2lf %c %.2lfx2", matrix[0][2], signal, matrix[0][1]);
            }
            printf("\n");

            printf(GREEN "\n> Classificacao do sistema: " RESET);
            printf("(SPI) Sistema possivel e indeterminado!\n");
            return;
        }
    }

    for (int i = 0; i < m; i++)
    {
        printf("\nx%d = %.2lf", i + 1, matrix[i][m]);
    }

    printf("\n");

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
        printf("O conjunto de vetores não pode ser usado como base!\n");
    }
}

double *calcAutovalues(double **matrix, int m, int n)
{

    if (m == 2)
    {
        double *autoValues = allocateVetor(2);
        double **matrixCop = copyMatrix(matrix, m, n);
        double termB = 0, termC = 0;

        termB = (-matrixCop[0][0]) - (matrixCop[1][1]);
        termC = calcDeterminant(matrix, m);

        autoValues[0] = (-termB + sqrt((termB * termB) - 4 * termC)) / 2;
        autoValues[1] = (-termB - sqrt((termB * termB) - 4 * termC)) / 2;

        return autoValues;
    }
    // Essa função custou bastante tempo, mas ainda sim, não conseguimos faze-la funcionar de forma correta.
    else if (m == 3)
    {
        double *autoValues = allocateVetor(3);
        double **matrixCop = copyMatrix(matrix, m, n);
        // Passo 1: Calcule os coeficientes do polinômio característico
        double termB = -(matrixCop[0][0] + matrixCop[1][1] + matrixCop[2][2]);
        double termC = matrixCop[0][0] * matrixCop[1][1] + matrixCop[0][0] * matrixCop[2][2] + matrixCop[1][1] * matrixCop[2][2] - 
                    (matrixCop[0][1] * matrixCop[1][0] + matrixCop[0][2] * matrixCop[2][0] + matrixCop[1][2] * matrixCop[2][1]);
        double termD = -(matrixCop[0][0] * (matrixCop[1][1] * matrixCop[2][2] - matrixCop[1][2] * matrixCop[2][1]) -
                        matrixCop[0][1] * (matrixCop[1][0] * matrixCop[2][2] - matrixCop[1][2] * matrixCop[2][0]) +
                        matrixCop[0][2] * (matrixCop[1][0] * matrixCop[2][1] - matrixCop[1][1] * matrixCop[2][0]));

        // Passo 2: Eliminar o termo quadrático e calcular os valores P e Q
        double p = termB / -1; // Normalizado em relação a -1
        double q = termC / -1; // Normalizado em relação a -1
        double r = termD / -1; // Normalizado em relação a -1

        double P = q - (p * p) / 3;
        double Q = 2 * pow(p / 3, 3) - (p * q) / 3 + r;

        // Passo 3: Calcule o discriminante
        double discriminante = pow(Q / 2, 2) + pow(P / 3, 3);

        // Passo 4: Resolva a equação cúbica com base no valor do discriminante
        if (discriminante > 0) {
            // Uma raiz real e duas raízes complexas
            double S1 = cbrt(-Q / 2 + sqrt(discriminante));
            double S2 = cbrt(-Q / 2 - sqrt(discriminante));
            autoValues[0] = S1 + S2 - p / 3;
            autoValues[1] = NAN; // Raízes complexas
            autoValues[2] = NAN;
        } else if (discriminante == 0) {
            // Todas as raízes são reais e pelo menos duas são iguais
            double S = cbrt(-Q / 2);
            autoValues[0] = 2 * S - p / 3;
            autoValues[1] = -S - p / 3;
            autoValues[2] = -S - p / 3;
        } else {
            // Todas as raízes são reais e distintas
            double r1 = 2 * sqrt(-P / 3);
            double theta = acos(-Q / (2 * sqrt(-pow(P / 3, 3))));
            autoValues[0] = r1 * cos(theta / 3) - p / 3;
            autoValues[1] = r1 * cos((theta + 2 * M_PI) / 3) - p / 3;
            autoValues[2] = r1 * cos((theta + 4 * M_PI) / 3) - p / 3;
        }
        printf("\nFuncao de calculo de autovalores de matrizes 3x3 nao concluida!\n");
        return autoValues;
    }
}

void calcAutovetors(double **matrix, int m, int n)
{
    double *autoValues = calcAutovalues(matrix, m, n);

    if (m == 2)
    {
        printf(GREEN "\n> Autovetores:\n" RESET);
        for (int a = 0; a < 2; a++)
        {
            double **matrixCop = copyMatrix(matrix, m, n);
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                    {
                        matrixCop[i][j] -= autoValues[a];
                    }
                }
            }

            double **scheduledMatriz = scheduleMatrix(matrixCop, m, m + 1);

            printf("\nv1 = (1.00, %.2lf)", -scheduledMatriz[0][0] / scheduledMatriz[0][1]);
        }

        printf("\n");
    }
    else
    {
        printf("\nFuncao de calculo de autovetores de matrizes 3x3 nao concluida!\n");
    }
}

void diagonalization(double **matrix, int m, int n)
{

    double *autoValues = calcAutovalues(matrix, m, n);
    double **matrixCop = copyMatrix(matrix, m, n);

    if (m == 2)
    {
        printf(GREEN "\n\n> Matriz diagonalizada:\n" RESET);
        printf("\n%.2lf 0.00", autoValues[0]);
        printf("\n0.00 %.2lf\n", autoValues[1]);
    }
    else
    {
        printf("\nFuno de diagonalizacao de matrizes 3x3 não concluada!\n");
    }
}
