/*
    DSP
    - convolve (time domain、frequency domain)
    - zeropadding
    - type exchange (complex <-> double)
*/

#pragma once

#include "fft.h"
#include "numeric.h"
#include "complexlib.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif // PI

double* complex_to_double(dcomplex *a, int N);
double** allocate2D_double(int rows, int cols);

int** allocate2D(int rows, int cols);

dcomplex* double_to_complex(double *a, int N);
dcomplex** allocate2D_dcomplex(int rows, int cols);

dcomplex dcomplex_add(dcomplex a, dcomplex b);
dcomplex dcomplex_sub(dcomplex a, dcomplex b);
dcomplex dcomplex_mul(dcomplex a, dcomplex b);
dcomplex dcomplex_smul(dcomplex a, double scalar);

double* convolve(double *x, double *h, int sz_x, int sz_h, int *len);
double* fftconvolve(double *x, double *h, int sz_x, int sz_h, int *len);

dcomplex** dft2d(dcomplex** image, int width, int height);
dcomplex** idft2d(dcomplex** fft_result, int width, int height);
dcomplex** fft2d(dcomplex** image, int rows, int cols);
dcomplex** ifft2d(dcomplex** fft_result, int rows, int cols);

double* zeropadding(double *x, int size_x, int N);

void spectrum(double *x, int N, double Fs);
