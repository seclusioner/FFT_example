#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "fft.h"
#include "dsp.h"

#define UNICODE

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

	printf("\nPress any key to continue . . . ");
	if (_getch()) printf("\n");
	return 0;
}
