#ifndef MATRIX_H
#define MATRIX_H

double **allocateMatrixDouble(int m, int n);
char **allocateMatrixChar(int m, int n);
void printMatrixDouble(double **matrix, int m, int n);
void printMatrixChar(char **matrix, int m);
double **scheduleMatrix(double **matrix, int m, int n);
int rankMatrix(double **matrix, int m, int n);
double **systemToMatrix(char **system, int m);

#endif