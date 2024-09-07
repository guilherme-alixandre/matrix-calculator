#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int n = 0;

//enum e struct
enum Dimensao {
	DOIS = 2,
	TRES = 3
};

enum Operadores {
	ADICAO = '+',
	SUBTRACAO = '-',
	IGUAL = '='
};

// funções
void inputDimension () {
	do{
	printf("Informe a dimensao da matriz (2 ou 3):");
	scanf("%d", &n);
	if(n != DOIS && n != TRES) {
		printf("Entrada Invalida!!\n");
	}
	getchar();
	}while(n != DOIS && n != TRES);
}

bool isNumeric(char c) {
	return c > 47 && c < 58;
}

bool isOperator(char c) {
	return c == ADICAO || c == SUBTRACAO || c ==  IGUAL;
}

 void printMatrizFinal(int x, double **matriz) {
 	for (int i = 0; i < x; i++) {
		for(int j = 0; j < x + 1; j++) {
			printf("%.2lf ", matriz[i][j]); 		
		}
		printf("\n");
	}
 }

double strtoDouble(char *y){
	char *endptr;
	return strtod(y, &endptr);
}

void scheduling(double **matriz, int col) {
	for(int j = 0; j < n + 1; j++){
		for(int i = 0; i < n; i++){
			
		}	
	}
}

int main () {

	inputDimension();

	char matriz[n][51];
	double matrizFinal[n][n+1];

	printf("Informe o sistema:\n");
	printf("\nEx.:\nax+by+3c=d\nex+fy+gc=h\nix+jy+kz=l\n\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 50; j++) {
			char c = ' ';
			scanf("%c", &c);

			if (c == '\n') {
				matriz[i][j] = '\0';
			    break;
			}

			matriz[i][j] = c;
		}

		// Valida se sistema informado na linha é válido
		int coefsAdd = 0;
		int tam = strlen(matriz[i]);
		for (int j = 0; j < tam; j++) {

			// Reserva coef. atual da linha
			char number[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
			int charsInNumber = 0;

			// Coleta coef. negativo
			if (matriz[i][j] == SUBTRACAO) {
				number[0] = SUBTRACAO;
				charsInNumber++;

				for(int x = j + 1; x < tam; x++) {
					if (isNumeric(matriz[i][x])) {
						number[charsInNumber] = matriz[i][x];
						charsInNumber++;
					} else if (matriz[i][x] == ' ') {
						// Pula espaço
					}else {
						j += x - j;
						break;
					}
				}

				matrizFinal[i][coefsAdd] = strtoDouble(number);
				coefsAdd++;
			} else if (isNumeric(matriz[i][j])) {
				number[0] = matriz[i][j];
				for(int x = j + 1; x < tam; x++) {
					if (isNumeric(matriz[i][x])) {
						number[x - j] = matriz[i][x];
					} else {
						j += x - j;
						break;
					}
				}
				matrizFinal[i][coefsAdd] = strtoDouble(number);
				coefsAdd++;
			}


		}
	}

	// printMatrizFinal(n, matrizFinal);	

	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n + 1; j++) {
			printf("%.2lf ", matrizFinal[i][j]); 		
		}
		printf("\n");
	}

	

	return 0;
}

/*
1. Criar um validador de coluna zerada.

*/