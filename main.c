#include <stdio.h>
#include <string.h>
#include "headers/matrix.h"

#define MAX_LENGTH 1024

// Definições de cores ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

int main()
{

  char again = 'n';

  do
  {

    printf(GREEN "\n************************************************************************\n" RESET);
    printf(GREEN "\n                        Trabalho de Algebra\n" RESET);
    printf(GREEN "\n************************************************************************\n" RESET);

    int option = 0;
    do
    {

      printf("\nSelecione uma das funcoes do programa:\n");
      printf("\n1 - Calculadora de Sistemas Lineares");
      printf("\n2 - Verificacao de injetividade, sobrejetividade e sobrejetividade");
      printf("\n3 - Determinacao de bases");
      printf("\n4 - Calculo de Autovalores e autovetores");
      printf("\n5 - Diagonalizacao de matrizes\n");
      printf("\nDigite o numero da opcao: ");
      scanf("%d", &option);

      if (option < 1 || option > 5)
        printf(RED "\nOpcao inexistente!\n" RESET);

    } while (option < 1 || option > 5);

    printf(YELLOW "\nOpcao selecionada:\n" RESET);
    if (option == 1)
    {
      printf(YELLOW "1 - Calculadora de Sistemas Lineares\n" RESET);
      printf("\nInstrucoes:\n");
      printf("\n> Digite as equacoes do sistema e aperte Enter 2x para enviar.\nSe o valor da variavel for 1 ou 0, devera ser informado!\n");
      printf("\n> Exemplo:\n1x + 0y - 3z = 5\n3x - 4y + 0z = 8\n2x - 1y - 2z = 6\n\n");
    }
    else if (option == 2)
    {
    }
    else if (option == 3)
    {
    }
    else if (option == 4)
    {
    }
    else
    {
    }

    char input[MAX_LENGTH];

    /**
     * Guarda toda a entrada do sistema em um vetor já determinando a qnt de linhas
     * e comprimento da maior equação para criação da matriz que guardará o sistema
     */
    int rows = 0, rowLen = 0, biggerLen = 0;
    for (int i = 0; i < MAX_LENGTH; i++)
    {
      scanf("%c", &input[i]);

      // Condicional para evitar problemas ao apertar enter antes de informar a entrada
      if (i == 0 && input[0] == '\n')
      {
        input[0] = '\0';
        i = -1;
      }
      else
      {
        if (input[i] == '\n')
        {
          if (rowLen > biggerLen)
            biggerLen = rowLen;
          rowLen = 0;
          if (i > 0 && input[i - 1] == '\n')
          {
            input[i] = '\0';
            input[i - 1] = '\0';
            break;
          }
          rows++;
        }
        else
        {
          rowLen++;
        }
      }
    }

    char **system = allocateMatrixChar(rows, biggerLen);

    /**
     * Guarda entrada no sistema
     */

    int currentRow = 0;
    int inputLen = strlen(input);
    for (int i = 0; i < inputLen; i++)
    {
      rowLen = strlen(system[currentRow]);

      if (input[i] == '\n')
      {
        currentRow++;
      }
      else
      {
        system[currentRow][rowLen] = input[i];
      }
    }

    double **matrix = systemToMatrix(system, rows);
    printf("\n> Matriz gerada a partir do sistema: \n");
    printMatrixDouble(matrix, rows, rows + 1);

    double determinant = calcDeterminant(matrix, rows);
    printf("\n> Determinante: %.2lf\n", determinant);

    printf("\n> Transformacao representada pela matriz:\n");
    classifyTransformation(matrix, rows);

    baseVerification(rows, rows + 1, determinant, matrix);

    double **scheduledMatrix = scheduleMatrix(matrix, rows, rows + 1);
    printf("\n> Matriz escalonada:\n");
    printMatrixDouble(scheduledMatrix, rows, rows + 1);

    classifyScheduledMatrix(scheduledMatrix, rows, rows + 1);

    int rank = rankMatrix(scheduledMatrix, rows, rows + 1);
    printf("\n> Posto da matriz: %d\n", rank);

    // Comentado pois está retornando Segmentation fault
    // freeMatrixChar(system, rows);
    // freeMatrixDouble(matrix, rows);
    getchar();

    printf(GREEN "\nDeseja experimentar outra funcao do programa? (s/n)\n");
    scanf("%c", &again);
  } while (again == 's');

  return 0;
}