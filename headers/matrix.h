#ifndef MATRIX_H
#define MATRIX_H

double **allocateMatrixDouble(int m, int n);
double **scheduleMatrix(double **matrix, int m, int n);
double **systemToMatrix(char **system, int m);
char **allocateMatrixChar(int m, int n);
void freeMatrixDouble(double **matrix, int m);
void freeMatrixChar(char **matrix, int m);
void printMatrixDouble(double **matrix, int m, int n);
void printMatrixChar(char **matrix, int m);
void classifyScheduledMatrix(double **matrix, int m, int n);
void classifyTransformation(double **matrix, int m);
int rankMatrix(double **matrix, int m, int n);
double calcDeterminant(double **matrix, int m);

#endif