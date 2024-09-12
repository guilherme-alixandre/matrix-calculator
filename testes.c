#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

bool isLetter(char c)
{
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool isNumber(char c)
{
  return c >= 48 && c <= 57;
}

// Retorna o indice onde o elemento está, e -1 se não encontrar
int arrayFind(char *arr, char c)
{
  int len = strlen(arr);

  for (int i = 0; i < len; i++)
  {
    if (arr[i] == c)
      return i;
  }

  return -1;
}

void printArray(char *arr)
{
  int len = strlen(arr);

  for (int i = 0; i < len; i++)
  {
    printf("%c", arr[i]);
  }

  printf("\n");
}

int main()
{

  char input[MAX_LEN];
  int rows = 0;

  printf("\nInforme o sistema (Pressione Enter 2x para enviar):\n");

  for (int i = 0; i < MAX_LEN; i++)
  {
    scanf("%c", &input[i]);

    if (i > 0 && input[i] == '\n')
    {

      rows++;

      if (input[i - 1] == '\n')
      {

        rows--;

        input[i] = '\0';
        input[i - 1] = '\0';
        break;
      }
    }
    else if (i == MAX_LEN - 1)
    {
      printf("\nTamanho máximo de entrada alcançado! (1024 caracteres)\n");
    }
  }

  // Cria matriz com dimensões personalizadas
  int matriz[rows][rows + 1];
  char variables[MAX_LEN];

  // Guarda cada equação do sistema em uma linha de matriz
  int len = strlen(input);
  int biggerRowLen = 0, rowLen = 0;
  for (int i = 0; i < len; i++)
  {

    if (input[i] != '\n')
    {
      rowLen++;
    }
    else
    {
      if (rowLen > biggerRowLen)
        biggerRowLen = rowLen;
      rowLen = 0;
    }
  }

  char sistema[rows][biggerRowLen];

  int currentRow = 0, currentCol = 0;
  for (int i = 0; i < len; i++)
  {
    if (input[i] == '\n')
    {
      currentRow++;
      currentCol = 0;
    } else {
      sistema[currentRow][currentCol];
      currentCol++;
    }
  }

  for (int i = 0; i < rows; i++)
  {
    printArray(sistema[i]);
  }

  int lenVariables = strlen(variables);
  printf("\nVariáveis (%d): ", lenVariables);
  printArray(variables);

  // Percorre cada linha buscando os valores das variaveis

  return 0;
}