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
double igami(double a, double p); // Inverse upper incomplete gamma
double ei(double x); // Exponential integral Ei
double expn(int n, double x); // Exponential integral En
double dawsn(double x); // Dawson's integral
double zetac(double x); // Riemann zeta minus one
double zeta(double x, double q); // Hurwitz zeta
double spence(double x); // Dilogarithm
double polylog(int n, double x); // Polylogarithm
double incbet(double a, double b, double x); // Incomplete beta
double incbi(double a, double b, double y); // Inverse incomplete beta
double hyperg(double a, double b, double x); // Confluent hypergeometric
double hyp2f1(double a, double b, double c, double x); // Gauss hypergeometric
int fresnl(double x, double *s, double *c); // Fresnel integrals
int sici(double x, double *si, double *ci); // Sine and cosine integrals
int shichi(double x, double *shi, double *chi); // Hyperbolic sine and cosine integrals
double struve(double v, double x); // Struve function H_v
double j0(double x); // Bessel J0
double j1(double x); // Bessel J1
double y0(double x); // Bessel Y0
double y1(double x); // Bessel Y1
double jn(int n, double x); // Bessel Jn
double jv(double v, double x); // Bessel Jv
double yn(int n, double x); // Bessel Yn
double ellie(double phi, double m); // Incomplete elliptic E
double ellik(double phi, double m); // Incomplete elliptic F
double ellpe(double m); // Complete elliptic E
double ellpk(double m); // Complete elliptic K
int ellpj(double u, double m, double *sn, double *cn, double *dn, double *ph); // Jacobian elliptic functions
int airy(double x, double *ai, double *aip, double *bi, double *bip); // Airy functions
double psi(double x); // Digamma
double i0(double x); // Modified Bessel I0
double i1(double x); // Modified Bessel I1
double i0e(double x); // Scaled modified Bessel I0
double i1e(double x); // Scaled modified Bessel I1
double iv(double v, double x); // Modified Bessel Iv
double k0(double x); // Modified Bessel K0
double k1(double x); // Modified Bessel K1
double k0e(double x); // Scaled modified Bessel K0
double k1e(double x); // Scaled modified Bessel K1
double kn(int n, double x); // Modified Bessel Kn

double igam(double a, double x);  // Incomplete gamma integral 
double igamc(double a, double x); // Complemented incomplete gamma integral

/* -------------------------------------------------------
 * Raise Cephes errors as Morpho errors
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

static bool specialfn_airy(vm *v, value *args, const char *label, double *ai, double *aip, double *bi, double *bip, int *status) {
    double x;

    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        mtherr_reset();
        *status = airy(x, ai, aip, bi, bip);
        return true;
    }

    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 1, "float");
    return false;
}

static bool specialfn_ellpj(vm *v, value *args, const char *label, double *sn, double *cn, double *dn, double *ph) {
    double u, m;

    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &u) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &m)) {
        mtherr_reset();
        ellpj(u, m, sn, cn, dn, ph);
        return true;
    }

    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 2, "float");
    return false;
}

static bool specialfn_fresnl(vm *v, value *args, const char *label, double *s, double *c) {
    double x;

    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        fresnl(x, s, c);
        return true;
    }

    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 1, "float");
    return false;
}

static bool specialfn_sici(vm *v, value *args, const char *label, double *si, double *ci) {
    double x;

    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        sici(x, si, ci);
        return true;
    }

    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 1, "float");
    return false;
}

static bool specialfn_shichi(vm *v, value *args, const char *label, double *shi, double *chi) {
    double x;

    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        shichi(x, shi, chi);
        return true;
    }

    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, label, 1, "float");
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
 * Cephes veneers
 * ------------------------------------------------------- */

SPECIALFN_UNARY_WRAPPER(Specialfn_gamma, SPECIALFN_GAMMA, gamma)
SPECIALFN_UNARY_WRAPPER(Specialfn_lgam, SPECIALFN_LOGGAMMA, lgam)
SPECIALFN_BINARY_WRAPPER(Specialfn_beta, SPECIALFN_BETA, beta)
SPECIALFN_BINARY_WRAPPER(Specialfn_lbeta, SPECIALFN_LOGBETA, lbeta)
SPECIALFN_BINARY_WRAPPER(Specialfn_igam, SPECIALFN_LOWERINCOMPLETEGAMMA, igam)
SPECIALFN_BINARY_WRAPPER(Specialfn_ellik, SPECIALFN_INCOMPLETEELLIPTICF, ellik)
SPECIALFN_BINARY_WRAPPER(Specialfn_ellie, SPECIALFN_INCOMPLETEELLIPTICE, ellie)
SPECIALFN_UNARY_WRAPPER(Specialfn_rgamma, SPECIALFN_RECIPROCALGAMMA, rgamma)
SPECIALFN_UNARY_WRAPPER(Specialfn_erf, SPECIALFN_ERF, erf)
SPECIALFN_UNARY_WRAPPER(Specialfn_erfc, SPECIALFN_ERFC, erfc)
SPECIALFN_UNARY_WRAPPER(Specialfn_ndtr, SPECIALFN_NORMALCDF, ndtr)
SPECIALFN_UNARY_WRAPPER(Specialfn_ndtri, SPECIALFN_INVERSENORMALCDF, ndtri)
SPECIALFN_UNARY_WRAPPER(Specialfn_ei, SPECIALFN_EXPINTEGRALEI, ei)
SPECIALFN_UNARY_WRAPPER(Specialfn_dawsn, SPECIALFN_DAWSON, dawsn)
SPECIALFN_UNARY_WRAPPER(Specialfn_zetac, SPECIALFN_RIEMANNZETAMINUSONE, zetac)
SPECIALFN_UNARY_WRAPPER(Specialfn_spence, SPECIALFN_DILOG, spence)

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

value Specialfn_ellpk(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double m;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &m)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ellpk(1.0 - m));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_COMPLETEELLIPTICK, 1, "float");

    return out;
}

value Specialfn_ellpe(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double m;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &m)) {
        mtherr_reset();
        out=MORPHO_FLOAT(ellpe(1.0 - m));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_COMPLETEELLIPTICE, 1, "float");

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

value Specialfn_igami(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, p;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &p)) {
        mtherr_reset();
        out=MORPHO_FLOAT(igami(a, p));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_INVERSEUPPERINCOMPLETEGAMMA, 2, "float");

    return out;
}

value Specialfn_hyperg(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 2), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(hyperg(a, b, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_CONFLUENTHYPERGEOMETRIC, 3, "float");

    return out;
}

value Specialfn_hyp2f1(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double a, b, c, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &a) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &b) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 2), &c) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 3), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(hyp2f1(a, b, c, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_GAUSSHYPERGEOMETRIC, 4, "float");

    return out;
}

value Specialfn_expn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(expn(n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_EXPINTEGRALE, 2, "integer, float");

    return out;
}

value Specialfn_riemannZeta(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        if (x == 1.0) {
            morpho_runtimeerror(v, SPECIALFN_SINGULARITYERROR, SPECIALFN_RIEMANNZETA);
            return MORPHO_NIL;
        }
        mtherr_reset();
        out=MORPHO_FLOAT(zetac(x) + 1.0);
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_RIEMANNZETA, 1, "float");

    return out;
}

value Specialfn_hurwitzZeta(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double x, q;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &q)) {
        mtherr_reset();
        out=MORPHO_FLOAT(zeta(x, q));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_HURWITZZETA, 2, "float");

    return out;
}

value Specialfn_polylog(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(polylog(n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_POLYLOG, 2, "integer, float");

    return out;
}

value Specialfn_struve(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double order, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &order) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(struve(order, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_STRUVEH, 2, "float");

    return out;
}

value Specialfn_fresnelS(vm *v, int nargs, value *args) {
    double s, c;
    if (specialfn_fresnl(v, args, SPECIALFN_FRESNELS, &s, &c)) return MORPHO_FLOAT(s);
    return MORPHO_NIL;
}

value Specialfn_fresnelC(vm *v, int nargs, value *args) {
    double s, c;
    if (specialfn_fresnl(v, args, SPECIALFN_FRESNELC, &s, &c)) return MORPHO_FLOAT(c);
    return MORPHO_NIL;
}

value Specialfn_sineIntegral(vm *v, int nargs, value *args) {
    double si, ci;
    if (specialfn_sici(v, args, SPECIALFN_SINEINTEGRAL, &si, &ci)) return MORPHO_FLOAT(si);
    return MORPHO_NIL;
}

value Specialfn_cosineIntegral(vm *v, int nargs, value *args) {
    double x, si, ci;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        if (x == 0.0) {
            morpho_runtimeerror(v, SPECIALFN_SINGULARITYERROR, SPECIALFN_COSINEINTEGRAL);
            return MORPHO_NIL;
        }
        sici(x, &si, &ci);
        return MORPHO_FLOAT(ci);
    }
    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_COSINEINTEGRAL, 1, "float");
    return MORPHO_NIL;
}

value Specialfn_sinhIntegral(vm *v, int nargs, value *args) {
    double shi, chi;
    if (specialfn_shichi(v, args, SPECIALFN_SINHINTEGRAL, &shi, &chi)) return MORPHO_FLOAT(shi);
    return MORPHO_NIL;
}

value Specialfn_coshIntegral(vm *v, int nargs, value *args) {
    double x, shi, chi;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &x)) {
        if (x == 0.0) {
            morpho_runtimeerror(v, SPECIALFN_SINGULARITYERROR, SPECIALFN_COSHINTEGRAL);
            return MORPHO_NIL;
        }
        shichi(x, &shi, &chi);
        return MORPHO_FLOAT(chi);
    }
    morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_COSHINTEGRAL, 1, "float");
    return MORPHO_NIL;
}

SPECIALFN_UNARY_WRAPPER(Specialfn_j0, SPECIALFN_BESSELJ, j0)
SPECIALFN_UNARY_WRAPPER(Specialfn_j1, SPECIALFN_BESSELJ, j1)
SPECIALFN_UNARY_WRAPPER(Specialfn_y0, SPECIALFN_BESSELY, y0)
SPECIALFN_UNARY_WRAPPER(Specialfn_y1, SPECIALFN_BESSELY, y1)
value Specialfn_airyAi(vm *v, int nargs, value *args) {
    double ai, aip, bi, bip;
    int status;
    if (specialfn_airy(v, args, SPECIALFN_AIRYAI, &ai, &aip, &bi, &bip, &status)) return MORPHO_FLOAT(ai);
    return MORPHO_NIL;
}

value Specialfn_airyAiPrime(vm *v, int nargs, value *args) {
    double ai, aip, bi, bip;
    int status;
    if (specialfn_airy(v, args, SPECIALFN_AIRYAIPRIME, &ai, &aip, &bi, &bip, &status)) return MORPHO_FLOAT(aip);
    return MORPHO_NIL;
}

value Specialfn_airyBi(vm *v, int nargs, value *args) {
    double ai, aip, bi, bip;
    int status;
    if (specialfn_airy(v, args, SPECIALFN_AIRYBI, &ai, &aip, &bi, &bip, &status)) {
        if (status < 0) {
            morpho_runtimeerror(v, SPECIALFN_OVERFLOWERROR, SPECIALFN_AIRYBI);
            return MORPHO_NIL;
        }
        return MORPHO_FLOAT(bi);
    }
    return MORPHO_NIL;
}

value Specialfn_airyBiPrime(vm *v, int nargs, value *args) {
    double ai, aip, bi, bip;
    int status;
    if (specialfn_airy(v, args, SPECIALFN_AIRYBIPRIME, &ai, &aip, &bi, &bip, &status)) {
        if (status < 0) {
            morpho_runtimeerror(v, SPECIALFN_OVERFLOWERROR, SPECIALFN_AIRYBIPRIME);
            return MORPHO_NIL;
        }
        return MORPHO_FLOAT(bip);
    }
    return MORPHO_NIL;
}

value Specialfn_jacobiSn(vm *v, int nargs, value *args) {
    double sn, cn, dn, ph;
    if (specialfn_ellpj(v, args, SPECIALFN_JACOBISN, &sn, &cn, &dn, &ph)) {
        if (specialfn_dispatcherror(v)) return MORPHO_NIL;
        return MORPHO_FLOAT(sn);
    }
    return MORPHO_NIL;
}

value Specialfn_jacobiCn(vm *v, int nargs, value *args) {
    double sn, cn, dn, ph;
    if (specialfn_ellpj(v, args, SPECIALFN_JACOBICN, &sn, &cn, &dn, &ph)) {
        if (specialfn_dispatcherror(v)) return MORPHO_NIL;
        return MORPHO_FLOAT(cn);
    }
    return MORPHO_NIL;
}

value Specialfn_jacobiDn(vm *v, int nargs, value *args) {
    double sn, cn, dn, ph;
    if (specialfn_ellpj(v, args, SPECIALFN_JACOBIDN, &sn, &cn, &dn, &ph)) {
        if (specialfn_dispatcherror(v)) return MORPHO_NIL;
        return MORPHO_FLOAT(dn);
    }
    return MORPHO_NIL;
}

value Specialfn_jacobiAmplitude(vm *v, int nargs, value *args) {
    double sn, cn, dn, ph;
    if (specialfn_ellpj(v, args, SPECIALFN_JACOBIAMPLITUDE, &sn, &cn, &dn, &ph)) {
        if (specialfn_dispatcherror(v)) return MORPHO_NIL;
        return MORPHO_FLOAT(ph);
    }
    return MORPHO_NIL;
}

SPECIALFN_UNARY_WRAPPER(Specialfn_psi, SPECIALFN_DIGAMMA, psi)
SPECIALFN_UNARY_WRAPPER(Specialfn_i0, SPECIALFN_MODIFIEDBESSELI, i0)
SPECIALFN_UNARY_WRAPPER(Specialfn_k0, SPECIALFN_MODIFIEDBESSELK, k0)
SPECIALFN_UNARY_WRAPPER(Specialfn_i0e, SPECIALFN_SCALEDMODIFIEDBESSELI0, i0e)
SPECIALFN_UNARY_WRAPPER(Specialfn_i1e, SPECIALFN_SCALEDMODIFIEDBESSELI1, i1e)
SPECIALFN_UNARY_WRAPPER(Specialfn_k0e, SPECIALFN_SCALEDMODIFIEDBESSELK0, k0e)
SPECIALFN_UNARY_WRAPPER(Specialfn_k1e, SPECIALFN_SCALEDMODIFIEDBESSELK1, k1e)

value Specialfn_jn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        if (n == 0) out=MORPHO_FLOAT(j0(x));
        else if (n == 1) out=MORPHO_FLOAT(j1(x));
        else out=MORPHO_FLOAT(jn(n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELJ, 2, "integer, float");

    return out;
}

value Specialfn_jv(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double order, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &order) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(jv(order, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELJ, 2, "float");

    return out;
}

value Specialfn_yn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        if (n == 0) out=MORPHO_FLOAT(y0(x));
        else if (n == 1) out=MORPHO_FLOAT(y1(x));
        else out=MORPHO_FLOAT(yn(n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_BESSELY, 2, "integer, float");

    return out;
}

value Specialfn_i1(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        if (n == 0) out=MORPHO_FLOAT(i0(x));
        else if (n == 1) out=MORPHO_FLOAT(i1(x));
        else out=MORPHO_FLOAT(iv((double) n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_MODIFIEDBESSELI, 2, "integer, float");

    return out;
}

value Specialfn_iv(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    double order, x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 0), &order) &&
        morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        out=MORPHO_FLOAT(iv(order, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_MODIFIEDBESSELI, 2, "float");

    return out;
}

value Specialfn_kn(vm *v, int nargs, value *args) {
    value out=MORPHO_NIL;

    int n = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0));
    double x;
    if (morpho_valuetofloat(MORPHO_GETARG(args, 1), &x)) {
        mtherr_reset();
        if (n == 0) out=MORPHO_FLOAT(k0(x));
        else if (n == 1) out=MORPHO_FLOAT(k1(x));
        else out=MORPHO_FLOAT(kn(n, x));
        if (specialfn_dispatcherror(v)) out=MORPHO_NIL;
    } else morpho_runtimeerror(v, VM_INVALIDARGSDETAIL, SPECIALFN_MODIFIEDBESSELK, 2, "integer, float");

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
    morpho_addfunction(SPECIALFN_INVERSEUPPERINCOMPLETEGAMMA, "Float (_,_)", Specialfn_igami, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_CONFLUENTHYPERGEOMETRIC, "Float (_,_,_)", Specialfn_hyperg, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_GAUSSHYPERGEOMETRIC, "Float (_,_,_,_)", Specialfn_hyp2f1, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_EXPINTEGRALEI, "Float (_)", Specialfn_ei, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_EXPINTEGRALE, "Float (Int,_)", Specialfn_expn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_DAWSON, "Float (_)", Specialfn_dawsn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_FRESNELS, "Float (_)", Specialfn_fresnelS, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_FRESNELC, "Float (_)", Specialfn_fresnelC, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SINEINTEGRAL, "Float (_)", Specialfn_sineIntegral, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_COSINEINTEGRAL, "Float (_)", Specialfn_cosineIntegral, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SINHINTEGRAL, "Float (_)", Specialfn_sinhIntegral, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_COSHINTEGRAL, "Float (_)", Specialfn_coshIntegral, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_RIEMANNZETA, "Float (_)", Specialfn_riemannZeta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_RIEMANNZETAMINUSONE, "Float (_)", Specialfn_zetac, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_HURWITZZETA, "Float (_,_)", Specialfn_hurwitzZeta, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_DILOG, "Float (_)", Specialfn_spence, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_POLYLOG, "Float (Int,_)", Specialfn_polylog, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_STRUVEH, "Float (_,_)", Specialfn_struve, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELJ, "Float (_)", Specialfn_j0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELJ, "Float (Int,_)", Specialfn_jn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELJ, "Float (Float,_)", Specialfn_jv, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELY, "Float (_)", Specialfn_y0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_BESSELY, "Float (Int,_)", Specialfn_yn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_INCOMPLETEELLIPTICF, "Float (_,_)", Specialfn_ellik, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_INCOMPLETEELLIPTICE, "Float (_,_)", Specialfn_ellie, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_COMPLETEELLIPTICK, "Float (_)", Specialfn_ellpk, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_COMPLETEELLIPTICE, "Float (_)", Specialfn_ellpe, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_JACOBISN, "Float (_,_)", Specialfn_jacobiSn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_JACOBICN, "Float (_,_)", Specialfn_jacobiCn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_JACOBIDN, "Float (_,_)", Specialfn_jacobiDn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_JACOBIAMPLITUDE, "Float (_,_)", Specialfn_jacobiAmplitude, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_AIRYAI, "Float (_)", Specialfn_airyAi, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_AIRYAIPRIME, "Float (_)", Specialfn_airyAiPrime, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_AIRYBI, "Float (_)", Specialfn_airyBi, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_AIRYBIPRIME, "Float (_)", Specialfn_airyBiPrime, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_DIGAMMA, "Float (_)", Specialfn_psi, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELI, "Float (_)", Specialfn_i0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELI, "Float (Int,_)", Specialfn_i1, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELI, "Float (Float,_)", Specialfn_iv, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELK, "Float (_)", Specialfn_k0, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_MODIFIEDBESSELK, "Float (Int,_)", Specialfn_kn, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SCALEDMODIFIEDBESSELI0, "Float (_)", Specialfn_i0e, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SCALEDMODIFIEDBESSELI1, "Float (_)", Specialfn_i1e, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SCALEDMODIFIEDBESSELK0, "Float (_)", Specialfn_k0e, BUILTIN_FLAGSEMPTY, NULL);
    morpho_addfunction(SPECIALFN_SCALEDMODIFIEDBESSELK1, "Float (_)", Specialfn_k1e, BUILTIN_FLAGSEMPTY, NULL);
}
