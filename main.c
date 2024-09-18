#include <stdio.h>
#include <string.h>
#include "headers/matrix.h"

#define MAX_LENGTH 1024

int main()
{

  char input[MAX_LENGTH];

  printf("\n> Digite as equacoes do sistema e aperte Enter 2x para enviar.\n");

  printf("\n> Exemplo:\n2x + 3y - 3z = 5\n3x - 4y + 3z = 8\n2x - 4y - 2z = 6\n\n");

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

  double **scheduledMatrix = scheduleMatrix(matrix, rows, rows + 1);
  printf("\n> Matriz escalonada:\n");
  printMatrixDouble(scheduledMatrix, rows, rows + 1);

  printf("\n> Classificacao do sistema: ");
  classifyScheduledMatrix(scheduledMatrix, rows, rows + 1);

  // Comentado pois está retornando Segmentation fault
  // freeMatrixChar(system, rows);
  // freeMatrixDouble(matrix, rows);
  getchar();
  return 0;
}