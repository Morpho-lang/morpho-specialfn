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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "gamma", 1, "float");

    return out;
}

value Specialfn_lgam(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(lgam(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "lgam", 1, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "beta", 2, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "lbeta", 2, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "igam", 2, "float");

    return out;
}

value Specialfn_rgamma(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(rgamma(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "rgamma", 1, "float");

    return out;
}

value Specialfn_erf(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(erf(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "erf", 1, "float");

    return out;
}

value Specialfn_erfc(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(erfc(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "erfc", 1, "float");

    return out;
}

value Specialfn_ndtr(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ndtr(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "ndtr", 1, "float");

    return out;
}

value Specialfn_ndtri(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ndtri(x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "ndtri", 1, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "incbet", 3, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "incbi", 3, "float");

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
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, "igamc", 2, "float");

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

    morpho_addfunction("gamma", "Float (_)", Specialfn_gamma, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("lgam", "Float (_)", Specialfn_lgam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("beta", "Float (_,_)", Specialfn_beta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("lbeta", "Float (_,_)", Specialfn_lbeta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("igam", "Float (_,_)", Specialfn_igam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("igamc", "Float (_,_)", Specialfn_igamc, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("rgamma", "Float (_)", Specialfn_rgamma, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("erf", "Float (_)", Specialfn_erf, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("erfc", "Float (_)", Specialfn_erfc, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("ndtr", "Float (_)", Specialfn_ndtr, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("ndtri", "Float (_)", Specialfn_ndtri, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("incbet", "Float (_,_,_)", Specialfn_incbet, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("incbi", "Float (_,_,_)", Specialfn_incbi, BUILTIN_FLAGSEMPTY, NULL);
}
