#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "fft.h"
#include "dsp.h"

#define UNICODE

float input[]={1.36849, 1.00912, 0.77214, -0.2554, -0.35185, -0.78784, -0.34128, -0.2047, 0.43879, 0.91979, 1.35083, 1.18693, 0.77584, 0.01244, -0.41674, -0.77935, -0.52584, 0.0619, 0.65222, 1.26387};

// -------------------------------
#define SAMPLING_FREQ 10
#define SAMPLES 5

void print_arr(float *x, int N){
    for(int i=0;i<N;i++){
        printf("%.2f ", x[i]);
    }
    printf("\n");
}

void print_complex(dcomplex x, int mode){
    if(mode)
        printf("(%f, %f)\n", x.re, x.im);
    else
        printf("%f%+fi\n", x.re, x.im);
}

int main(void) {
    // Complex Test
    dcomplex a, b, c;
    a.re = 1;
    a.im = -1;
    b.re = b.im = 2;

    printf("a = ");print_complex(a, 0);
    printf("b = ");print_complex(b, 0);

    c = cadd(a, b);
    printf("a + b = ");print_complex(c, 0);

    c = csub(a, b);
    printf("a - b = ");print_complex(c, 0);

    c = cmul(a, b);
    printf("a * b = ");print_complex(c, 0);

    c = cdiv(a, b);
    printf("a / b = ");print_complex(c, 0);

    c = conjugate(a);
    printf("a* = ");print_complex(c, 0);

    printf("|a| = %f\n", magnitude(a));
    printf("rad(a) = %f, deg(a) = %f\n", arg(a, 0), arg(a, 1));

    printf("---------------\n");
    // -----------------------------------------------
    float x[SAMPLES]={0};
    float h[SAMPLES]={0};
    int N = SAMPLES;

    for(int i=0;i<N;i++){
        x[i] = h[i] = 1;
    }
    printf("Input Vector1: ");
    print_arr(x, N);
    printf("Input Vector2: ");
    print_arr(h, N);
    printf("---------------\n");
    
    float *yn;

    yn = fftconvolve(x, h, SAMPLES, SAMPLES, &N);
    printf("After FFT convolve:\n");
    print_arr(yn, N);
    printf("---------------\n");
    
    yn = convolve(x, h, SAMPLES, SAMPLES, &N);
    printf("After convolve:\n");
    print_arr(yn, N);
    free(yn);

    printf("---------------\n");
    spectrum(input, sizeof(input)/sizeof(input[0]), SAMPLING_FREQ);

	printf("\nPress any key to continue . . . ");
	if (_getch()) printf("\n");
	return 0;
}
