//
// complexlib.c
//

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "complexlib.h"

/* double complex type ------------------------------ */
double arg(dcomplex z, int mode){
    /*
        mode = 0: radian
        mode = 1: degree
    */
    float angle;
    angle = atan(z.im / z.re);
    if(mode)
        return angle * 180 / PI;
    else
        return angle;
}

double magnitude(dcomplex z) {
    return sqrt(z.re * z.re + z.im * z.im);
}

double norm(dcomplex z) {
    return z.re * z.re + z.im * z.im;
}

dcomplex conjugate(dcomplex z) {
    dcomplex r = {z.re, -z.im};
    return r;
}

dcomplex complex_exp(dcomplex z) {
    return _Cmulrc(exp(z.re), cbuild(cos(z.im), sin(z.im)));
}

dcomplex _Ceulerr(double x) {
    return cbuild(cos(x), sin(x));
}

dcomplex _Ceulerc(dcomplex z) {
    return _Cmulcr(_Ceulerr(z.re), exp(-z.im));
}

void _Ceulererr(void) {
    fprintf(stderr, "TypeError: ceuler( <dcomplex, double> z ).\n");
    exit(EXIT_FAILURE);
}

dcomplex cbuild(double re, double im) {
    dcomplex z = { re, im };
    return z;
}

dcomplex _Caddcc(dcomplex a, dcomplex b) {
    return cbuild(a.re + b.re, a.im + b.im);
}

dcomplex _Caddcr(dcomplex a, double b) {
    return cbuild(a.re + b, a.im);
}

dcomplex _Caddrc(double a, dcomplex b) {
    return cbuild(a + b.re, b.im);
}

void _Cadderr(void) {
    fprintf(stderr, "TypeError: cadd( <dcomplex, double> a, <dcomplex, double> b).\n");
    exit(EXIT_FAILURE);
}

dcomplex _Csubcc(dcomplex a, dcomplex b) {
    return cbuild(a.re - b.re, a.im - b.im);
}

dcomplex _Csubcr(dcomplex a, double b) {
    return cbuild(a.re - b, a.im);
}

dcomplex _Csubrc(double a, dcomplex b) {
    return cbuild(a - b.re, -b.im);
}

void _Csuberr(void) {
    fprintf(stderr, "TypeError: csub( <dcomplex, double> a, <dcomplex, double> b).\n");
    exit(EXIT_FAILURE);
}

dcomplex _Cmulcc(dcomplex a, dcomplex b) {
    return cbuild(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

dcomplex _Cmulcr(dcomplex a, double b) {
    return cbuild(a.re * b, a.im * b);
}

dcomplex _Cmulrc(double a, dcomplex b) {
    return cbuild(a * b.re, a * b.im);
}

void _Cmulerr(void) {
    fprintf(stderr, "TypeError: cmul( <dcomplex, double> a, <dcomplex, double> b).\n");
    exit(EXIT_FAILURE);
}

dcomplex _Cdivcc(dcomplex a, dcomplex b) {
    double angle = arg(a, 0) - arg(b, 0);
    double abs = magnitude(a) / magnitude(b);
    return cbuild(abs * cos(angle), abs * sin(angle));
}

dcomplex _Cdivcr(dcomplex a, double b) {
    return cbuild(a.re / b, a.im / b);
}

dcomplex _Cdivrc(double a, dcomplex b) {
    return _Cmulcr(conjugate(b), a / norm(b));
}

void _Cdiverr(void) {
    fprintf(stderr, "TypeError: cdiv( <dcomplex, double> a, <dcomplex, double> b).\n");
    exit(EXIT_FAILURE);
}

