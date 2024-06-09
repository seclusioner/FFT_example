#pragma once

#include "fft.h"
#include "complexlib.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif // PI

#ifdef __cplusplus
extern "C" {
#endif

double* complex_to_double(dcomplex *a, int N);

dcomplex* double_to_complex(double *a, int N);
dcomplex** allocate2D_dcomplex(int rows, int cols);

dcomplex dcomplex_add(dcomplex a, dcomplex b);
dcomplex dcomplex_sub(dcomplex a, dcomplex b);
dcomplex dcomplex_mul(dcomplex a, dcomplex b);
dcomplex dcomplex_smul(dcomplex a, double scalar);

void free2D_dcomplex(dcomplex** arr, int rows);

double* convolve(double *x, double *h, int sz_x, int sz_h, int *len);
double* fftconvolve(double *x, double *h, int sz_x, int sz_h, int *len);

// fft 2d
dcomplex** dft2d(dcomplex** image, int width, int height);
dcomplex** idft2d(dcomplex** fft_result, int width, int height);
dcomplex** fft2d(dcomplex** image, int rows, int cols, norm_mode mode);
dcomplex** ifft2d(dcomplex** fft_result, int rows, int cols, norm_mode mode);

double* zeropadding(double *x, int size_x, int N);

void spectrum_shift(dcomplex **sp, int rows, int cols);
void spectrum(double *x, int N, double Fs);

#ifdef __cplusplus
}
#endif
