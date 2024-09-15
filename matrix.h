#ifndef MATRIX_H
#define MATRIX_H

double **allocateMatrixDouble(int m, int n);
char **allocateMatrixChar(int m, int n);
void printMatrix(double **matrix, int m, int n);
double **scheduleMatrix(double **matrix, int m, int n);
int rankMatrix(double **matrix, int m, int n);
double **systemToMatrix(char **system, int m);

#endif