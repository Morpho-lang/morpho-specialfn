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

/* -------------------------------------------------------
 * Ceres veneers
 * ------------------------------------------------------- */

value Specialfn_gamma(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(gamma(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_GAMMA, 1, "float");

    return out;
}

value Specialfn_lgam(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(lgam(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_LOGGAMMA, 1, "float");

    return out;
}

value Specialfn_beta(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b)) {
        mtherr_reset();
        out=MORPHO_FLOAT(beta(a,b));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BETA, 2, "float");

    return out;
}

value Specialfn_lbeta(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b)) {
        mtherr_reset();
        out=MORPHO_FLOAT(lbeta(a,b));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_LOGBETA, 2, "float");

    return out;
}

value Specialfn_igam(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double a, x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(igam(a,x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_LOWERINCOMPLETEGAMMA, 2, "float");

    return out;
}

value Specialfn_rgamma(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(rgamma(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_RECIPROCALGAMMA, 1, "float");

    return out;
}

value Specialfn_erf(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(erf(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_ERF, 1, "float");

    return out;
}

value Specialfn_erfc(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(erfc(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_ERFC, 1, "float");

    return out;
}

value Specialfn_ndtr(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ndtr(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_NORMALCDF, 1, "float");

    return out;
}

value Specialfn_ndtri(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ndtri(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_INVERSENORMALCDF, 1, "float");

    return out;
}

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

value Specialfn_j0(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(j0(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELJ, 1, "float");

    return out;
}

value Specialfn_j1(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(j1(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELJ, 1, "float");

    return out;
}

value Specialfn_y0(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(y0(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELY, 1, "float");

    return out;
}

value Specialfn_y1(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(y1(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELY, 1, "float");

    return out;
}

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

value Specialfn_igamc(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double a, x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(igamc(a,x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_UPPERINCOMPLETEGAMMA, 2, "float");

    return out;
}

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
}
