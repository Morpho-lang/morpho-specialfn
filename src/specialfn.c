#include <stdio.h>
#include <morpho.h>

#include "specialfn.h"

double gamma(double x); // Gamma function
double lgam(double x);  // Logarithm of the gamma function

double igam(double a, double x);  // Incomplete gamma integral 
double igamc(double a, double x); // Complemented incomplete gamma integral

value Specialfn_gamma(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        out=MORPHO_FLOAT(gamma(x));
    }

    return out;
}

value Specialfn_lgam(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        out=MORPHO_FLOAT(lgam(x));
    }

    return out;
}

value Specialfn_igam(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double a, x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        out=MORPHO_FLOAT(igam(a,x));
    }

    return out;
}

value Specialfn_igamc(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL; 

    double a, x; 
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        out=MORPHO_FLOAT(igamc(a,x));
    }

    return out;
}

/* -------------------------------------------------------
 * Initialization and finalization
 * ------------------------------------------------------- */

void specialfn_initialize(void) { 
    morpho_addfunction("gamma", "Float (_)", Specialfn_gamma, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("lgam", "Float (_)", Specialfn_lgam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("igam", "Float (_,_)", Specialfn_igam, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction("igamc", "Float (_,_)", Specialfn_igamc, BUILTIN_FLAGSEMPTY, NULL);
}
