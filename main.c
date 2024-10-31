#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "headers/matrix.h"

#define MAX_LENGTH 1024

// Definições de cores ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
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

    char option = '0';
    do
    {

      printf("\nSelecione uma das funcoes do programa:\n");
      printf("\n1 - Calculadora de Sistemas Lineares (Completo)");
      printf("\n2 - Verificacao de injetividade, sobrejetividade e bijetividade");
      printf("\n3 - Determinacao de bases");
      printf("\n4 - Calculo de Autovalores e autovetores");
      printf("\n5 - Diagonalizacao de matrizes\n");
      printf("\nDigite o numero da opcao: ");
      scanf("%c", &option);
      getchar();

      if (option < '1' || option > '5')
      {
        printf(RED "\nOpcao inexistente!\n" RESET);
      }

    } while (option < '1' || option > '5');

    printf(GREEN "\nOpcao selecionada:\n" RESET);
    if (option == '1')
    {
      printf(GREEN "1 - Calculadora de Sistemas Lineares\n" RESET);
      printf("\nInstrucoes:\n");
      printf("\n> Digite cada equacao do sistema em uma linha e ao final aperte Enter mais 1x para enviar.\n");
      printf(YELLOW "ATENÇÃO: Se o valor da variavel for 1 ou 0, devera ser informado!\nAs variaveis devem seguir a mesma ordem em todas as equações do sistema!\nUse '.' para números decimais, ex.: 1.5!\n" RESET);
      printf("\n> Exemplo:\n1x + 0y - 3z = 5\n3x - 4y + 0z = 8\n2x - 1y - 2z = 6\n\nSeu sistema:\n");
    }
    else if (option == '2')
    {
      printf(GREEN "2 - Verificacao de injetividade, sobrejetividade e bijetividade\n" RESET);
      printf("\nInstruções:\n");
      printf("\n> Digite cada linha da matriz separando os termos por virgula e ao final aperte Enter mais 1x para enviar.");
      printf("\n> Exemplo:\n1, 2, 3\n4, 5, 6\n7, 8, 9\n\nSua matriz:\n");
    }
    else if (option == '3')
    {
      printf(GREEN "3 - Determinacao de bases\n" RESET);
      printf("\nInstruções:\n");
      printf("\n> Digite cada vetor em uma linha separando os termos por virgula e ao final aperte Enter mais 1x para enviar.");
      printf("\nNão é necessário colocar entre parenteses.");
      printf("\n> Exemplo:\n1, 2, 3\n4, 5, 6\n7, 8, 9\n\nSeus vetores:\n");
    }
    else if (option == '4')
    {
      printf(GREEN "4 - Calculo de Autovalores e autovetores\n" RESET);
      printf("\nInstruções:\n");
      printf("\n> Digite cada linha da matriz separando os termos por virgula e ao final aperte Enter mais 1x para enviar.");
      printf("\n> Exemplo:\n4, 1\n2, 3\n\nSua matriz:\n");
    }
    else
    {
      printf(GREEN "5 - Diagonalizacao de matrizes\n" RESET);
      printf("\nInstruções:\n");
      printf("\n> Digite cada linha da matriz separando os termos por virgula e ao final aperte Enter mais 1x para enviar.");
      printf("\n> Exemplo:\n4, 1\n2, 3\n\nSua matriz:\n");
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

    char filename[] = "entradas.txt";

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
      printf("Erro ao abrir o arquivo!\n");
      return 1;
    }

    fprintf(file, "%s", input);
    fclose(file);

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
    double determinant = calcDeterminant(matrix, rows);

    if (option == '1')
    {
      printf(GREEN "\n> Matriz gerada a partir do sistema: \n" RESET);
      printMatrixDouble(matrix, rows, rows + 1);
      double **scheduledMatrix = scheduleMatrix(matrix, rows, rows + 1);
      printf(GREEN "\n> Matriz escalonada:\n" RESET);
      printMatrixDouble(scheduledMatrix, rows, rows + 1);

      classifyScheduledMatrix(scheduledMatrix, rows, rows + 1);

      int rank = rankMatrix(scheduledMatrix, rows, rows + 1);
      printf(GREEN "\n> Posto da matriz: " RESET);
      printf("%d\n", rank);
    }

    if (option == '1' || option == '2')
    {
      printf(GREEN "\n> Determinante: " RESET);
      printf("%.2lf\n", determinant);
      printf(GREEN "\n> Transformacao representada pela matriz: " RESET);
      classifyTransformation(matrix, rows);
    }

    if (option == '1' || option == '3')
    {
      printf(GREEN "\n> Determinacao de bases: " RESET);
      baseVerification(rows, rows + 1, determinant, matrix);
    }

    if (option == '1' || option == '4')
    {
      double *autoValues = calcAutovalues(matrix, rows, rows);
      printf(GREEN "\n> Autovalores:\n\n" RESET);
      if (rows == 2)
      {
        if (isnan(autoValues[0]) && isnan(autoValues[1]))
        {
          printf(RED "A matriz nao possui autovalores! (São números complexos)\n" RESET);
        }
        else
        {

          for (int i = 0; i < rows; i++)
          {
            if (!isnan(autoValues[i]))
            {
              printf("A%d = %.2lf\n", i + 1, autoValues[i]);
            }
          }
          calcAutovetors(matrix, rows, rows);
        }
      }
      else if (rows == 3)
      {
        if (isnan(autoValues[0]) && isnan(autoValues[1]) && isnan(autoValues[2]))
        {
          printf(RED "A matriz nao possui autovalores! (São números complexos)\n" RESET);
        }
        else
        {

          for (int i = 0; i < rows; i++)
          {
            if (!isnan(autoValues[i]))
            {
              printf("A%d = %.2lf\n", i + 1, autoValues[i]);
            }
          }
          calcAutovetors(matrix, rows, rows);
        }
      }
    }

    if (option == '1' || option == '5')
    {
      diagonalization(matrix, rows, rows);
    }

    // Comentado pois está retornando Segmentation fault
    // freeMatrixChar(system, rows);
    // freeMatrixDouble(matrix, rows);

    do
    {
      printf(CYAN "\nDeseja experimentar outra funcao do programa ou fazer outro teste nessa? (s/n)\n" RESET);
      scanf("%c", &again);

      if (again != 's' && again != 'S' && again != 'n' && again != 'N')
      {
        printf(RED "\nOpção inválida. Digite 's' ou 'n'!\n" RESET);
        getchar();
      }

    } while (again != 's' && again != 'S' && again != 'n' && again != 'N');
    getchar();
  } while (again == 's' || again == 'S');

  printf(CYAN "\nPrograma finalizado. Obrigado por usar!\n" RESET);

  getchar();
  return 0;
}