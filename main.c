#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "fft.h"
#include "dsp.h"
#include "complexlib.h"

#define EPILSON 1e-10
#define UNICODE

#define ABS(n) n > 0 ? n : -n

void print_arr(double *x, int N){
    for(int i=0;i<N;i++){
        printf("%.2f ", x[i]);
    }
    printf("\n");
}

void print_complex(dcomplex x, int mode){
    if(mode)
        printf("(%10f, %10f)", x.re, x.im);
    else
        printf("%10f%10fi", x.re, x.im);
}

void print_complexArray(dcomplex **x, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            print_complex(x[i][j], 1);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

/////////// testing ///////////
double** Random2dArray(int rows, int cols) {
    srand(time(NULL));
    int min = 0;
    int max = 255;

    double** matrix = allocate2D_double(rows, cols); // H, W
    if(matrix == NULL){
        printf("Allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }

    return matrix;
}


int main(void) {

    int flag = 0;
    int ROWS, COLS;

    ROWS = 2;
    COLS = 3;

    double** image = Random2dArray(ROWS, COLS); // H x W
    dcomplex ** input = allocate2D_dcomplex(ROWS, COLS);
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            //printf("%8.3f ", image[i][j]);
            input[i][j].re = image[i][j];
            printf("%8.3f ", input[i][j].re);
        }
        printf("\n");
    }

    //printf("\n----------fft2d---------------\n");
    dcomplex **X = fft2d(input, ROWS, COLS, backward);
    free2D_dcomplex(input, ROWS);

    //printf("\n-----------shift----------\n");
    spectrum_shift(X, ROWS, COLS);

    //printf("\n-----------shift----------\n");
    spectrum_shift(X, ROWS, COLS);

    //printf("\n-----------ifft2d-------------\n");
    dcomplex **result = ifft2d(X, ROWS, COLS, backward);

    printf("\n");
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            double error = result[i][j].re - image[i][j];
            printf("%8.3f ", result[i][j].re);
            if (error > EPILSON){
                flag = 1;
            }
        }

        printf("\n");

        if(flag)
            break;
    }

    ///////////////// Over /////////////////
    free2D_double(image, ROWS);
    free2D_dcomplex(X, ROWS);
    free2D_dcomplex(result, ROWS);

    printf("\n");
    if(flag)
        printf("???!\n");
    else
        printf("OK!\n");

    printf("\nFinish\n");
	system("pause");
	return 0;
}
