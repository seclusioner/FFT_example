#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fft.h"
#include "complexlib.h"
#include "dsp.h"
#include "Array.h"

// Fundamental Operations
double* complex_to_double(dcomplex *a, int N){
    double *output;
    output = (double*)calloc(N, sizeof(double));
    for(int i=0;i<N;i++){
        output[i] = a[i].re;
    }

    return output;
}

dcomplex* double_to_complex(double *a, int N){
    dcomplex *output;
    output = (dcomplex*)calloc(N, sizeof(dcomplex));
    for(int i=0;i<N;i++){
        output[i].re = a[i];
        output[i].im = 0;
    }

    return output;
}

// Complex Operations
dcomplex dcomplex_add(dcomplex a, dcomplex b){ // a+b
    dcomplex c;
    c.re = a.re + b.re;
    c.im = a.im + b.im;
    return c;
}

dcomplex dcomplex_sub(dcomplex a, dcomplex b){ // a-b
    dcomplex c;
    c.re = a.re - b.re;
    c.im = a.im - b.im;
    return c;
}

dcomplex dcomplex_mul(dcomplex a, dcomplex b){ // a*b
    dcomplex c;

    c.re = a.re * b.re - a.im * b.im;
    c.im = a.re * b.im + a.im * b.re;

    return c;
}

dcomplex dcomplex_smul(dcomplex a, double scalar){
    dcomplex c;

    c.re = a.re * scalar;
    c.im = a.im * scalar;

    return c;
}

static dcomplex** transposeMatrix_dcomplex(dcomplex** matrix, int rows, int cols) {
    dcomplex** transposedMatrix = allocate2D_dcomplex(cols, rows);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    return transposedMatrix;
}

//////////////////////////////// Algorithm ////////////////////////////////
// Convolution
double* convolve(double *x, double *h, int sz_x, int sz_h, int *len){
    int sz = sz_x + sz_h - 1;
    double *output = NULL;
    output = (double*) calloc(sz, sizeof(double));
    for(int i=0;i<sz_x;i++){
        for(int j=0;j<sz_h;j++){
            output[i+j] += x[i] * h[j];
        }
    }

    *len = sz;
    return output;
}

double* fftconvolve(double *x, double *h, int sz_x, int sz_h, int *len){
    int N = sz_x + sz_h - 1;
    x = zeropadding(x, sz_x, N);
    h = zeropadding(h, sz_h, N);

    dcomplex *X, *H;
    dcomplex *xn, *hn;
    xn = double_to_complex(x, N);
    hn = double_to_complex(h, N);
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

    double *yn;
    yn = complex_to_double(y, N);

    *len = N;
    return yn;
}

// DFT 2D & IDFT 2D
dcomplex** dft2d(dcomplex** image, int width, int height){
    //M, N = signal.shape
    double M, N;

    M = height;
    N = width;

    dcomplex** dft_result = allocate2D_dcomplex(M, N);

    double theta;
    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){
            for(int u=0;u<M;u++){
                for(int v=0;v<N;v++){
                    theta = -2 * PI * ((u * x) / M + (v * y) / N);
                    dcomplex phasor;
                    phasor.re = cos(theta); phasor.im = sin(theta);
                    dft_result[x][y] = dcomplex_add(dft_result[x][y], dcomplex_mul(image[u][v], phasor));
                }
            }
        }
    }

    return dft_result;
}

dcomplex** idft2d(dcomplex** fft_result, int width, int height){
    double M, N;

    M = height;
    N = width;
    dcomplex** idft_result = allocate2D_dcomplex(M, N);
    if (idft_result == NULL){
        printf("Allocation failed!\n");
        exit(1);
    }

    double theta;
    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){
            for(int u=0;u<M;u++){
                for(int v=0;v<N;v++){
                    theta = 2 * PI * ((u * x) / M + (v * y) / N);
                    dcomplex phasor;
                    phasor.re = cos(theta); phasor.im = sin(theta);
                    idft_result[x][y] = dcomplex_add(idft_result[x][y], dcomplex_mul(fft_result[u][v], phasor));
                }
            }

            idft_result[x][y].re /= (double)(M * N);
            idft_result[x][y].im /= (double)(M * N);
        }
    }

    return idft_result;
}

// 2D fft
dcomplex** fft2d(dcomplex** image, int rows, int cols, norm_mode mode){
    ////////////////////// fft2D //////////////////////
    dcomplex* tmp;
    dcomplex* tmp_fft;

    // for rows [i][j]
    dcomplex** fft_rows = allocate2D_dcomplex(rows, cols);
    tmp = (dcomplex *) calloc(cols, sizeof(dcomplex));
    tmp_fft = (dcomplex *) calloc(cols, sizeof(dcomplex));
    if (fft_rows == NULL || tmp == NULL || tmp_fft == NULL) {
        printf("Allocated failed!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) { // rows
        for (int j = 0; j < cols; j++) { // cols
            tmp[j] = image[i][j];
        }
        tmp_fft = fft(tmp, cols, mode); // 0 for forward FFT
        for (int k = 0; k < cols; k++) {
            fft_rows[i][k] = tmp_fft[k];
        }
    }

    free(tmp);
    free(tmp_fft);

    // for cols [j][i]
    tmp = (dcomplex *) calloc(rows, sizeof(dcomplex));
    tmp_fft = (dcomplex *) calloc(rows, sizeof(dcomplex));
    dcomplex** X = allocate2D_dcomplex(rows, cols);
    if (X == NULL || tmp == NULL || tmp_fft == NULL) {
        printf("Allocated failed!\n");
        exit(1);
    }

    // transpose
    dcomplex** transposed_fft_rows = transposeMatrix_dcomplex(fft_rows, rows, cols);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            tmp[j] = transposed_fft_rows[i][j];
        }
        tmp_fft = fft(tmp, rows, mode); // 0 for forward FFT
        for (int k = 0; k < rows; k++) {
            X[k][i] = tmp_fft[k];
        }
    }

    free(tmp);
    free(tmp_fft);
    free2D_dcomplex(transposed_fft_rows, cols);
    free2D_dcomplex(fft_rows, rows);

    return X;
}

// 2D ifft
static dcomplex* ifft_self(dcomplex* fft_result, int N, norm_mode mode){
    // conjugate -> fft -> 1/N
    dcomplex* X;

    for(int i=0;i<N;i++){
        fft_result[i] = conjugate(fft_result[i]);
    }

    X = fft(fft_result, N, mode);

    double coefficient;
    if(mode == backward){
        coefficient = 1.0/(double)N;
    }
    else if(mode == ortho){
        coefficient = 1.0 / sqrt(N);
    }
    else if(mode == forward){
        coefficient = 1.0;
    }


    for(int i=0;i<N;i++){
        X[i] = dcomplex_smul(X[i], coefficient);
    }

    return X;
}

dcomplex** ifft2d(dcomplex** fft_result, int rows, int cols, norm_mode mode){
    /////////////////// ifft2d ///////////////////
    dcomplex* tmp;
    dcomplex* tmp_ifft;
    dcomplex** ifft_rows = allocate2D_dcomplex(rows, cols);
    tmp = (dcomplex *) calloc(cols, sizeof(dcomplex));
    tmp_ifft = (dcomplex *) calloc(cols, sizeof(dcomplex));
    if (ifft_rows == NULL || tmp == NULL || tmp_ifft == NULL) {
        printf("Allocated failed!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) { // rows
        for (int j = 0; j < cols; j++) { // cols
            tmp[j] = fft_result[i][j];
        }
        tmp_ifft = ifft_self(tmp, cols, mode); // 0 for forward FFT
        for (int k = 0; k < cols; k++) {
            ifft_rows[i][k] = tmp_ifft[k];
        }
    }

    free(tmp);
    free(tmp_ifft);

    tmp = (dcomplex *) calloc(rows, sizeof(dcomplex));
    tmp_ifft = (dcomplex *) calloc(rows, sizeof(dcomplex));
    dcomplex** x = allocate2D_dcomplex(rows, cols);
    if (x == NULL || tmp == NULL || tmp_ifft == NULL) {
        printf("Allocated failed!\n");
        exit(1);
    }

    // transpose
    dcomplex** transposed_ifft_rows = transposeMatrix_dcomplex(ifft_rows, rows, cols);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            tmp[j] = transposed_ifft_rows[i][j];
        }
        tmp_ifft = ifft_self(tmp, rows, mode); // 0 for forward FFT
        for (int k = 0; k < rows; k++) {
            x[k][i] = tmp_ifft[k];
        }
    }

    for (int i = 1; i <= rows / 2; i++) {
        for (int j = 0; j < cols; j++) {
            dcomplex temp = x[i][j];
            x[i][j] = x[rows - i][j];
            x[rows - i][j] = temp;
        }
    }

    free(tmp);
    free(tmp_ifft);
    free2D_dcomplex(transposed_ifft_rows, cols);
    free2D_dcomplex(ifft_rows, rows);

    return x;
}

void spectrum_shift(dcomplex **sp, int rows, int cols) {
    int mid_row = rows / 2;
    int mid_col = cols / 2;

    dcomplex tmp;

    for (int i = 0; i < mid_row; i++) {
        for (int j = 0; j < mid_col; j++) {
            // upper-left <-> lower-right
            tmp = sp[i][j];
            sp[i][j] = sp[mid_row + i][mid_col + j];
            sp[mid_row + i][mid_col + j] = tmp;

            // upper-right <-> lower-left
            tmp = sp[i][mid_col + j];
            sp[i][mid_col + j] = sp[mid_row + i][j];
            sp[mid_row + i][j] = tmp;
        }
    }
}


double* zeropadding(double *x, int size_x, int N){
    // x: input, size_x: input's length, N: size of convolution.
    double *array = NULL;
    array = (double*)calloc(N, sizeof(double));

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

void spectrum(double *x, int N, double Fs){
    dcomplex *X;
    dcomplex *xn;
    xn = double_to_complex(x, N);
    X = fft(xn, N, backward);
    for(int i=0;2*i<N;i++){
        printf("%.3f Hz\t%.3f\n", (i*Fs/N), magnitude(X[i]));
    }
    printf("-------------------------------\n");
    free(xn);
    free(X);
}
