#include <stdio.h>
#include <morpho.h>

#include "specialfn.h"

double gamma(double x); // Gamma function
double lgam(double x);  // Logarithm of the gamma function
double beta(double a, double b); // Beta function
double lbeta(double a, double b); // Logarithm of beta
double rgamma(double x); // Reciprocal gamma function
double erf(double x); // Error function
double erfc(double x); // Complementary error function
double ndtr(double x); // Normal CDF
double ndtri(double x); // Inverse normal CDF
double incbet(double a, double b, double x); // Incomplete beta
double incbi(double a, double b, double y); // Inverse incomplete beta
double j0(double x); // Bessel J0
double j1(double x); // Bessel J1
double y0(double x); // Bessel Y0
double y1(double x); // Bessel Y1
double jn(int n, double x); // Bessel Jn
double yn(int n, double x); // Bessel Yn
double i0(double x); // Modified Bessel I0
double i1(double x); // Modified Bessel I1
double iv(double v, double x); // Modified Bessel Iv
double k0(double x); // Modified Bessel K0
double k1(double x); // Modified Bessel K1
double kn(int n, double x); // Modified Bessel Kn

double igam(double a, double x);  // Incomplete gamma integral 
double igamc(double a, double x); // Complemented incomplete gamma integral

/* -------------------------------------------------------
 * Raise Ceres errors as morpho errors
 * ------------------------------------------------------- */

typedef struct {
    int code;
    errorid tag;
} SpecialfnError;

static const SpecialfnError specialfn_errors[] = {
    { DOMAIN, SPECIALFN_DOMAINERROR },
    { SING, SPECIALFN_SINGULARITYERROR },
    { OVERFLOW, SPECIALFN_OVERFLOWERROR },
    { UNDERFLOW, SPECIALFN_UNDERFLOWERROR },
    { TLOSS, SPECIALFN_TLOSSERROR },
    { PLOSS, SPECIALFN_PLOSSERROR }
};

static bool specialfn_dispatcherror(vm *v) {
    int code = mtherr_geterror();
    if (code == 0) return false;
    
    const char *function = (merrorname) ? merrorname : "unknown";

    for (unsigned int i = 0; i < sizeof(specialfn_errors)/sizeof(specialfn_errors[0]); i++) {
        if (specialfn_errors[i].code == code) {
            morpho_runtimeerror(v, specialfn_errors[i].tag, function);
            return true;
        }
    }

    return false;
}

#define SPECIALFN_UNARY_WRAPPER(wrapper, label, function) \
value wrapper(vm *v, int nargs, value *args) { \
    value out=MORPHO_NIL; \
    double x; \
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) { \
        mtherr_reset(); \
        out=MORPHO_FLOAT(function(x)); \
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL; \
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 1, "float"); \
    return out; \
}

#define SPECIALFN_BINARY_WRAPPER(wrapper, label, function) \
value wrapper(vm *v, int nargs, value *args) { \
    value out=MORPHO_NIL; \
    double a, b; \
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) && \
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b)) { \
        mtherr_reset(); \
        out=MORPHO_FLOAT(function(a, b)); \
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL; \
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 2, "float"); \
    return out; \
}

/* -------------------------------------------------------
 * Ceres veneers
 * ------------------------------------------------------- */

SPECIALFN_UNARY_WRAPPER(Specialfn_gamma, SPECIALFN_GAMMA, gamma)
SPECIALFN_UNARY_WRAPPER(Specialfn_lgam, SPECIALFN_LOGGAMMA, lgam)
SPECIALFN_BINARY_WRAPPER(Specialfn_beta, SPECIALFN_BETA, beta)
SPECIALFN_BINARY_WRAPPER(Specialfn_lbeta, SPECIALFN_LOGBETA, lbeta)
SPECIALFN_BINARY_WRAPPER(Specialfn_igam, SPECIALFN_LOWERINCOMPLETEGAMMA, igam)
SPECIALFN_UNARY_WRAPPER(Specialfn_rgamma, SPECIALFN_RECIPROCALGAMMA, rgamma)
SPECIALFN_UNARY_WRAPPER(Specialfn_erf, SPECIALFN_ERF, erf)
SPECIALFN_UNARY_WRAPPER(Specialfn_erfc, SPECIALFN_ERFC, erfc)
SPECIALFN_UNARY_WRAPPER(Specialfn_ndtr, SPECIALFN_NORMALCDF, ndtr)
SPECIALFN_UNARY_WRAPPER(Specialfn_ndtri, SPECIALFN_INVERSENORMALCDF, ndtri)

value Specialfn_incbet(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 2), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(incbet(a,b,x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_INCOMPLETEBETA, 3, "float");

    return out;
}

value Specialfn_incbi(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b, y;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 2), &y)) {
        mtherr_reset();
        out=MORPHO_FLOAT(incbi(a,b,y));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_INVERSEINCOMPLETEBETA, 3, "float");

    return out;
}

SPECIALFN_UNARY_WRAPPER(Specialfn_j0, SPECIALFN_BESSELJ, j0)
SPECIALFN_UNARY_WRAPPER(Specialfn_j1, SPECIALFN_BESSELJ, j1)
SPECIALFN_UNARY_WRAPPER(Specialfn_y0, SPECIALFN_BESSELY, y0)
SPECIALFN_UNARY_WRAPPER(Specialfn_y1, SPECIALFN_BESSELY, y1)
SPECIALFN_UNARY_WRAPPER(Specialfn_i0, SPECIALFN_MODIFIEDBESSELI, i0)
SPECIALFN_UNARY_WRAPPER(Specialfn_k0, SPECIALFN_MODIFIEDBESSELK, k0)

value Specialfn_jn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x = MORPHO_GETFLOATVALUE(MORPHO_GETARG(args, 1));
    mtherr_reset();
    if (n == 0) out=MORPHO_FLOAT(j0(x));
    else if (n == 1) out=MORPHO_FLOAT(j1(x));
    else out=MORPHO_FLOAT(jn(n, x));
    if (specialfn_dispatcherror(v)) out=MORPHO_NIL;

    return out;
}

value Specialfn_yn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x = MORPHO_GETFLOATVALUE(MORPHO_GETARG(args, 1));
    mtherr_reset();
    if (n == 0) out=MORPHO_FLOAT(y0(x));
    else if (n == 1) out=MORPHO_FLOAT(y1(x));
    else out=MORPHO_FLOAT(yn(n, x));
    if (specialfn_dispatcherror(v)) out=MORPHO_NIL;

    return out;
}

value Specialfn_i1(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x = MORPHO_GETFLOATVALUE(MORPHO_GETARG(args, 1));
    mtherr_reset();
    if (n == 0) out=MORPHO_FLOAT(i0(x));
    else if (n == 1) out=MORPHO_FLOAT(i1(x));
    else out=MORPHO_FLOAT(iv((double) n, x));
    if (specialfn_dispatcherror(v)) out=MORPHO_NIL;

    return out;
}

value Specialfn_kn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x = MORPHO_GETFLOATVALUE(MORPHO_GETARG(args, 1));
    mtherr_reset();
    if (n == 0) out=MORPHO_FLOAT(k0(x));
    else if (n == 1) out=MORPHO_FLOAT(k1(x));
    else out=MORPHO_FLOAT(kn(n, x));
    if (specialfn_dispatcherror(v)) out=MORPHO_NIL;

    return out;
}

SPECIALFN_BINARY_WRAPPER(Specialfn_igamc, SPECIALFN_UPPERINCOMPLETEGAMMA, igamc)

/* -------------------------------------------------------
 * Initialization and finalization
 * ------------------------------------------------------- */

void specialfn_initialize(void) { 
    morpho_defineerror(SPECIALFN_DOMAINERROR, ERROR_HALT, SPECIALFN_DOMAINERROR_MSG);
    morpho_defineerror(SPECIALFN_SINGULARITYERROR, ERROR_HALT, SPECIALFN_SINGULARITYERROR_MSG);
    morpho_defineerror(SPECIALFN_OVERFLOWERROR, ERROR_HALT, SPECIALFN_OVERFLOWERROR_MSG);
    morpho_defineerror(SPECIALFN_UNDERFLOWERROR, ERROR_HALT, SPECIALFN_UNDERFLOWERROR_MSG);
    morpho_defineerror(SPECIALFN_TLOSSERROR, ERROR_HALT, SPECIALFN_TLOSSERROR_MSG);
    morpho_defineerror(SPECIALFN_PLOSSERROR, ERROR_HALT, SPECIALFN_PLOSSERROR_MSG);

    morpho_addfunction(SPECIALFN_GAMMA, "Float (_)", Specialfn_gamma, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_LOGGAMMA, "Float (_)", Specialfn_lgam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BETA, "Float (_,_)", Specialfn_beta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_LOGBETA, "Float (_,_)", Specialfn_lbeta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_LOWERINCOMPLETEGAMMA, "Float (_,_)", Specialfn_igam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_UPPERINCOMPLETEGAMMA, "Float (_,_)", Specialfn_igamc, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_RECIPROCALGAMMA, "Float (_)", Specialfn_rgamma, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_ERF, "Float (_)", Specialfn_erf, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_ERFC, "Float (_)", Specialfn_erfc, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_NORMALCDF, "Float (_)", Specialfn_ndtr, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_INVERSENORMALCDF, "Float (_)", Specialfn_ndtri, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_INCOMPLETEBETA, "Float (_,_,_)", Specialfn_incbet, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_INVERSEINCOMPLETEBETA, "Float (_,_,_)", Specialfn_incbi, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELJ, "Float (_)", Specialfn_j0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELJ, "Float (Int,_)", Specialfn_jn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELY, "Float (_)", Specialfn_y0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELY, "Float (Int,_)", Specialfn_yn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELI, "Float (_)", Specialfn_i0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELI, "Float (Int,_)", Specialfn_i1, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELK, "Float (_)", Specialfn_k0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELK, "Float (Int,_)", Specialfn_kn, BUILTIN_FLAGSEMPTY, NULL);
}
