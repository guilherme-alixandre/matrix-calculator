#ifndef MATRIX_H
#define MATRIX_H

double **allocateMatrixDouble(int m, int n);
double **scheduleMatrix(double **matrix, int m, int n);
double **systemToMatrix(char **system, int m);
char **allocateMatrixChar(int m, int n);
void freeMatrixChar(char **matrix, int m);
void printMatrixDouble(double **matrix, int m, int n);
void printMatrixChar(char **matrix, int m);
int rankMatrix(double **matrix, int m, int n);

#endif