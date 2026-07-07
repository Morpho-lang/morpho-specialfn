#include <stdio.h>
#include <morpho/morpho.h>
#include <morpho/builtin.h>

#define SPECIALFN_DOMAINERROR "SpecialfnDomain"
#define SPECIALFN_DOMAINERROR_MSG "Special function %s encountered a domain error."

#define SPECIALFN_SINGULARITYERROR "SpecialfnSingularity"
#define SPECIALFN_SINGULARITYERROR_MSG "Special function %s encountered a singularity."

#define SPECIALFN_OVERFLOWERROR "SpecialfnOverflow"
#define SPECIALFN_OVERFLOWERROR_MSG "Special function %s overflowed."

#define SPECIALFN_UNDERFLOWERROR "SpecialfnUnderflow"
#define SPECIALFN_UNDERFLOWERROR_MSG "Special function %s underflowed."

#define SPECIALFN_TLOSSERROR "SpecialfnTLoss"
#define SPECIALFN_TLOSSERROR_MSG "Special function %s encountered total loss of precision."

#define SPECIALFN_PLOSSERROR "SpecialfnPLoss"
#define SPECIALFN_PLOSSERROR_MSG "Special function %s encountered partial loss of precision."

#define SPECIALFN_GAMMA "gamma"
#define SPECIALFN_LOGGAMMA "logGamma"
#define SPECIALFN_BETA "beta"
#define SPECIALFN_LOGBETA "logBeta"
#define SPECIALFN_LOWERINCOMPLETEGAMMA "lowerIncompleteGamma"
#define SPECIALFN_UPPERINCOMPLETEGAMMA "upperIncompleteGamma"
#define SPECIALFN_RECIPROCALGAMMA "reciprocalGamma"
#define SPECIALFN_ERF "erf"
#define SPECIALFN_ERFC "erfc"
#define SPECIALFN_NORMALCDF "normalCDF"
#define SPECIALFN_INVERSENORMALCDF "inverseNormalCDF"
#define SPECIALFN_INCOMPLETEBETA "incompleteBeta"
#define SPECIALFN_INVERSEINCOMPLETEBETA "inverseIncompleteBeta"
#define SPECIALFN_BESSELJ "besselJ"
#define SPECIALFN_BESSELY "besselY"
#define SPECIALFN_DIGAMMA "digamma"
#define SPECIALFN_MODIFIEDBESSELI "modifiedBesselI"
#define SPECIALFN_MODIFIEDBESSELK "modifiedBesselK"

void mtherr_reset(void);
int mtherr_geterror(void);
int mtherr(char *name, int code);

extern const char *merrorname;

void specialfn_initialize(void);
