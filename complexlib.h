//
// conmplexlib.h
//

#pragma once

#ifndef _COMPLEXLIB_H_
#define _COMPLEXLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct double_complex_t {
    double re;
    double im;
} dcomplex;

#ifndef PI
#define PI (3.1415926535897932384626433832795028841971693993751058209749445923)
#endif

/* double complex type ------------------------------ */
double arg(dcomplex z, int mode);
double magnitude(dcomplex z);
double norm(dcomplex z);

dcomplex conjugate(dcomplex z);
dcomplex complex_exp(dcomplex z);
dcomplex _Ceulerr(double x);
dcomplex _Ceulerc(dcomplex z);
void _Ceulererr(void);

#define ceuler(z) _Generic((a),     \
    dcomplex:_Ceulerc,              \
    double: _Ceulerr,               \
    default: _Ceulererr             \
)(z)

dcomplex cbuild(double real, double imag);
dcomplex _Caddcc(dcomplex a, dcomplex b);
dcomplex _Caddcr(dcomplex a, double b);
dcomplex _Caddrc(double a, dcomplex b);

void _Cadderr(void);

#define cadd(a, b) _Generic((a),    \
    dcomplex: _Generic((b),         \
        dcomplex: _Caddcc,          \
        double: _Caddcr,            \
        default: _Cadderr           \
    ),                              \
    double: _Generic((b),           \
        dcomplex: _Caddrc,          \
        default: _Cadderr           \
    ),                              \
    default: _Cadderr               \
)(a, b)

dcomplex _Csubcc(dcomplex a, dcomplex b);
dcomplex _Csubcr(dcomplex a, double b);
dcomplex _Csubrc(double a, dcomplex b);
void _Csuberr(void);

#define csub(a, b) _Generic((a),    \
    dcomplex: _Generic((b),         \
        dcomplex: _Csubcc,          \
        double: _Csubcr,            \
        default: _Csuberr           \
    ),                              \
    double: _Generic((b),           \
        dcomplex: _Csubcr,          \
        default: _Csuberr           \
    ),                              \
    default: _Csuberr               \
)(a, b)

dcomplex _Cmulcc(dcomplex a, dcomplex b);
dcomplex _Cmulcr(dcomplex a, double b);
dcomplex _Cmulrc(double a, dcomplex b);
void _Cmulerr(void);

#define cmul(a, b) _Generic((a),    \
    dcomplex: _Generic((b),         \
        dcomplex: _Cmulcc,          \
        double  : _Cmulcr,          \
        default : _Cmulerr          \
    ),                              \
    double: _Generic((b),           \
        dcomplex: _Cmulrc,          \
        default : _Cmulerr          \
    ),                              \
    default: _Cmulerr               \
)(a, b)

dcomplex _Cdivcc(dcomplex a, dcomplex b);
dcomplex _Cdivcr(dcomplex a, double b);
dcomplex _Cdivrc(double a, dcomplex b);
void _Cdiverr(void);

#define cdiv(a, b) _Generic((a),    \
    dcomplex: _Generic((b),         \
        dcomplex: _Cdivcc,          \
        double: _Cdivcr,            \
        default: _Cdiverr           \
    ),                              \
    double: _Generic((b),           \
        dcomplex: _Cdivcr,          \
        default: _Cdiverr           \
    ),                              \
    default: _Cdiverr               \
)(a, b)

#ifdef __cplusplus
}
#endif

#endif
