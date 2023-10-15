#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "dsp.h"

float* complex_to_float(dcomplex *a, int N){
    float *output;
    output = (float*)calloc(N, sizeof(float));
    for(int i=0;i<N;i++){
        output[i] = a[i].re;
    }

    return output;
}

dcomplex* float_to_complex(float *a, int N){
    dcomplex *output;
    output = (dcomplex*)calloc(N, sizeof(dcomplex));
    for(int i=0;i<N;i++){
        output[i].re = a[i];
        output[i].im = 0;
    }

    return output;
}

float* convolve(float *x, float *h, int sz_x, int sz_h, int *len){
    int sz = sz_x + sz_h - 1;
    float *output = NULL;
    output = (float*) calloc(sz, sizeof(float));
    for(int i=0;i<sz_x;i++){
        for(int j=0;j<sz_h;j++){
            output[i+j] += x[i] * h[j];
        }
    }

    *len = sz;
    return output;
}

float* fftconvolve(float *x, float *h, int sz_x, int sz_h, int *len){
    int N = sz_x + sz_h - 1;
    x = zeropadding(x, sz_x, N);
    h = zeropadding(h, sz_h, N);

    dcomplex *X, *H;
    dcomplex *xn, *hn;
    xn = float_to_complex(x, N);
    hn = float_to_complex(h, N);
    X = fft(xn, N, backward);
    H = fft(hn, N, backward);

    free(xn);
    free(hn);

    dcomplex *Y;
    Y = (dcomplex*)calloc(N, sizeof(dcomplex));
    for(int k=0;k<N;k++){
        Y[k] = _Cmulcc(X[k], H[k]);
    }

    free(X);
    free(H);

    dcomplex *y;
    y = ifft(Y, N, backward);

    float *yn;
    yn = complex_to_float(y, N);

    *len = N;
    return yn;
}

float* zeropadding(float *x, int size_x, int N){
    // x: input, size_x: input's length, N: size of convolution.
    float *array = NULL;
    array = (float*)calloc(N, sizeof(float));
    
    int i;
    for(i=0;i<N;i++){
        if(i<size_x){
            array[i] = x[i];
        }else{
            array[i] = 0;
        }
    }

    return array;
}

void spectrum(float *x, int N, float Fs){
    dcomplex *X;
    dcomplex *xn;
    xn = float_to_complex(x, N);
    X = fft(xn, N, backward);
    for(int i=0;2*i<N;i++){
        printf("%.3f Hz\t%.3f\n", (i*Fs/N), cabs(X[i]));
    }
    printf("-------------------------------\n");
}
