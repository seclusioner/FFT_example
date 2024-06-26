#pragma once

#include "complexlib.h"

#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

int** allocate2DArray(int rows, int cols);
float** allocate2DArray_f(int rows, int cols);
double** allocate2DArray_d(int rows, int cols);
dcomplex** allocate2D_dcomplex(int rows, int cols);

void free2DArray(int** arr, int rows);
void free2DArray_f(float** arr, int rows);
void free2DArray_d(double** arr, int rows);
void free2D_dcomplex(dcomplex** arr, int rows);


double* linspace(double start, double over, int N);


int** constant_2Darrayd(int height, int width, int val);

#ifdef __cplusplus
}
#endif

#endif // ARRAY_H
