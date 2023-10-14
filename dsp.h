/*
    DSP
    - convolve (time domain、frequency domain)
    - zeropadding
    - type exchange (complex <-> float)
*/

#pragma once

#include "fft.h"
#include "numeric.h"
#include "complexlib.h"

dcomplex* float_to_complex(float *a, int N);
float* complex_to_float(dcomplex *a, int N);

float* convolve(float *x, float *h, int sz_x, int sz_h, int *len);
float* fftconvolve(float *x, float *h, int sz_x, int sz_h, int *len);
float* zeropadding(float *x, int size_x, int N);
