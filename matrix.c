#include<stdio.h>
#include<string.h>
#include "matrix.h"

double **allocateMatrixDouble(int m, int n) {

}

char **allocateMatrixChar(int m, int n) {

}

void printMatrixDouble(double **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf/t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixChar(char **matrix, int m) {
    for (int i = 0; i < m; i++) {
        int rowLen = strlen(matrix[i]);
        for (int j = 0; j < rowLen; j++) {
            printf("%c/t", matrix[i][j]);
        }
        printf("\n");
    }
}

double **scheduleMatrix(double **matrix, int m, int n) {

}

int rankMatrix(double **matrix, int m, int n) {

}

double **systemToMatrix(char **system, int m) {
    
}