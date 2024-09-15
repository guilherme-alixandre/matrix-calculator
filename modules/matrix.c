#include<stdio.h>
#include<string.h>
#include "headers/matrix.h"
#include "headers/array.h"

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
        printString(matrix[i]);
        printf("\n");
    }
}

double **scheduleMatrix(double **matrix, int m, int n) {

}

int rankMatrix(double **matrix, int m, int n) {

}

double **systemToMatrix(char **system, int m) {
    
}