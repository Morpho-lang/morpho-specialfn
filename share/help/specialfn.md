[comment]: # (Specialfn help)

# specialfn
[specialfn]: # (specialfn)

The `specialfn` extension provides special functions for scientific computing in morpho.

Import it with:

    import specialfn

[showsubtopics]: # (subtopics)

## gamma
[gamma]: # (gamma)

Computes the Gamma function.

    print gamma(5) // expect: 24

## logGamma
[logGamma]: # (logGamma)

Computes the natural logarithm of the Gamma function.

    print logGamma(5)

## reciprocalGamma
[reciprocalGamma]: # (reciprocalGamma)

Computes the reciprocal Gamma function `1 / Gamma(x)`.

    print reciprocalGamma(5)

## lowerIncompleteGamma
[lowerIncompleteGamma]: # (lowerIncompleteGamma)

Computes the lower regularized incomplete Gamma function `P(a, x)`.

This is the normalized lower incomplete Gamma ratio.

    print lowerIncompleteGamma(2, 0.5)

## upperIncompleteGamma
[upperIncompleteGamma]: # (upperIncompleteGamma)

Computes the upper regularized incomplete Gamma function `Q(a, x)`.

    print upperIncompleteGamma(2, 0.5)

The regularized incomplete Gamma functions satisfy:

    lowerIncompleteGamma(a, x) + upperIncompleteGamma(a, x) = 1

## digamma
[digamma]: # (digamma)

Computes the digamma function, the logarithmic derivative of the Gamma function.

    print digamma(1)

## beta
[beta]: # (beta)

Computes the beta function.

    print beta(2, 3)

## logBeta
[logBeta]: # (logBeta)

Computes the natural logarithm of the beta function.

    print logBeta(2, 3)

## incompleteBeta
[incompleteBeta]: # (incompleteBeta)

Computes the regularized incomplete beta function.

This is the normalized incomplete beta ratio.

    print incompleteBeta(2, 3, 0.5)

## inverseIncompleteBeta
[inverseIncompleteBeta]: # (inverseIncompleteBeta)

Computes the inverse of the regularized incomplete beta function.

    print inverseIncompleteBeta(2, 3, 0.5)

## inverseUpperIncompleteGamma
[inverseUpperIncompleteGamma]: # (inverseUpperIncompleteGamma)

Computes the inverse of the upper regularized incomplete Gamma function.

Given `a` and `p`, it returns `x` such that `upperIncompleteGamma(a, x) = p`.

    print inverseUpperIncompleteGamma(1, 0.36787944117144233)

## confluentHypergeometric
[confluentHypergeometric]: # (confluentHypergeometric)

Computes the confluent hypergeometric function.

    print confluentHypergeometric(1, 1, 1)

## hypergeometric2F1
[hypergeometric2F1]: # (hypergeometric2F1)

Computes the Gauss hypergeometric function.

    print hypergeometric2F1(1, 1, 2, 0.5)

## expIntegralEi
[expIntegralEi]: # (expIntegralEi)

Computes the exponential integral `Ei(x)`.

    print expIntegralEi(1)

## expIntegralE
[expIntegralE]: # (expIntegralE)

Computes the exponential integral `E_n(x)`.

The first argument is an integer order `n`.

    print expIntegralE(1, 1)

## dawson
[dawson]: # (dawson)

Computes Dawson's integral.

    print dawson(1)

## fresnelS
[fresnelS]: # (fresnelS)

Computes the Fresnel integral `S(x)`.

    print fresnelS(1)

## fresnelC
[fresnelC]: # (fresnelC)

Computes the Fresnel integral `C(x)`.

    print fresnelC(1)

## sineIntegral
[sineIntegral]: # (sineIntegral)

Computes the sine integral.

    print sineIntegral(1)

## cosineIntegral
[cosineIntegral]: # (cosineIntegral)

Computes the cosine integral.

    print cosineIntegral(1)

## sinhIntegral
[sinhIntegral]: # (sinhIntegral)

Computes the hyperbolic sine integral.

    print sinhIntegral(1)

## coshIntegral
[coshIntegral]: # (coshIntegral)

Computes the hyperbolic cosine integral.

    print coshIntegral(1)

## riemannZeta
[riemannZeta]: # (riemannZeta)

Computes the Riemann zeta function.

    print riemannZeta(2)

## riemannZetaMinusOne
[riemannZetaMinusOne]: # (riemannZetaMinusOne)

Computes `riemannZeta(x) - 1`.

    print riemannZetaMinusOne(2)

## hurwitzZeta
[hurwitzZeta]: # (hurwitzZeta)

Computes the Hurwitz zeta function.

This is the two-parameter zeta function `zeta(x, q)`.

    print hurwitzZeta(2, 2)

## dilog
[dilog]: # (dilog)

Computes the dilogarithm.

    print dilog(1)

## polylog
[polylog]: # (polylog)

Computes the polylogarithm of integer order.

The first argument is an integer order `n`.

    print polylog(2, 1)

## struveH
[struveH]: # (struveH)

Computes the Struve function `H_v(x)` of order `v`.

    print struveH(0, 1)

## erf
[erf]: # (erf)

Computes the error function.

    print erf(0) // expect: 0

## erfc
[erfc]: # (erfc)

Computes the complementary error function.

    print erfc(0) // expect: 1

## normalCDF
[normalCDF]: # (normalCDF)

Computes the cumulative distribution function of the standard normal distribution.

    print normalCDF(0) // expect: 0.5

## inverseNormalCDF
[inverseNormalCDF]: # (inverseNormalCDF)

Computes the inverse cumulative distribution function of the standard normal distribution.

    print inverseNormalCDF(0.5) // expect: 0

## besselJ
[besselJ]: # (besselJ)

Computes the Bessel function of the first kind.

Supported call patterns:

    besselJ(x)      // order 0
    besselJ(n, x)   // integer order
    besselJ(v, x)   // real order

Examples:

    print besselJ(1.0)
    print besselJ(2, 1.0)
    print besselJ(0.5, 1.0)

## besselY
[besselY]: # (besselY)

Computes the Bessel function of the second kind.

Supported call patterns:

    besselY(x)      // order 0
    besselY(n, x)   // integer order

Examples:

    print besselY(1.0)
    print besselY(2, 1.0)

## modifiedBesselI
[modifiedBesselI]: # (modifiedBesselI)

Computes the modified Bessel function of the first kind.

Supported call patterns:

    modifiedBesselI(x)      // order 0
    modifiedBesselI(n, x)   // integer order
    modifiedBesselI(v, x)   // real order

Examples:

    print modifiedBesselI(1.0)
    print modifiedBesselI(2, 1.0)
    print modifiedBesselI(0.5, 1.0)

## modifiedBesselK
[modifiedBesselK]: # (modifiedBesselK)

Computes the modified Bessel function of the second kind.

Supported call patterns:

    modifiedBesselK(x)      // order 0
    modifiedBesselK(n, x)   // integer order

Examples:

    print modifiedBesselK(1.0)
    print modifiedBesselK(2, 1.0)

## scaledModifiedBesselI0
[scaledModifiedBesselI0]: # (scaledModifiedBesselI0)

Computes the exponentially scaled modified Bessel function `I0`.

This rescales `I0(x)` to improve numerical behavior for large `x`.

    print scaledModifiedBesselI0(1)

## scaledModifiedBesselI1
[scaledModifiedBesselI1]: # (scaledModifiedBesselI1)

Computes the exponentially scaled modified Bessel function `I1`.

This rescales `I1(x)` to improve numerical behavior for large `x`.

    print scaledModifiedBesselI1(1)

## scaledModifiedBesselK0
[scaledModifiedBesselK0]: # (scaledModifiedBesselK0)

Computes the exponentially scaled modified Bessel function `K0`.

This rescales `K0(x)` to improve numerical behavior for large `x`.

    print scaledModifiedBesselK0(1)

## scaledModifiedBesselK1
[scaledModifiedBesselK1]: # (scaledModifiedBesselK1)

Computes the exponentially scaled modified Bessel function `K1`.

This rescales `K1(x)` to improve numerical behavior for large `x`.

    print scaledModifiedBesselK1(1)

## airyAi
[airyAi]: # (airyAi)

Computes the Airy function `Ai(x)`.

    print airyAi(0)

## airyAiPrime
[airyAiPrime]: # (airyAiPrime)

Computes the derivative of the Airy function `Ai(x)`.

    print airyAiPrime(0)

## airyBi
[airyBi]: # (airyBi)

Computes the Airy function `Bi(x)`.

    print airyBi(0)

## airyBiPrime
[airyBiPrime]: # (airyBiPrime)

Computes the derivative of the Airy function `Bi(x)`.

    print airyBiPrime(0)

## incompleteEllipticF
[incompleteEllipticF]: # (incompleteEllipticF)

Computes the incomplete elliptic integral of the first kind using parameter `m`.

    print incompleteEllipticF(0.5, 0.2)

## incompleteEllipticE
[incompleteEllipticE]: # (incompleteEllipticE)

Computes the incomplete elliptic integral of the second kind using parameter `m`.

    print incompleteEllipticE(0.5, 0.2)

## completeEllipticK
[completeEllipticK]: # (completeEllipticK)

Computes the complete elliptic integral of the first kind using parameter `m`.

    print completeEllipticK(0.0) // expect: pi/2

## completeEllipticE
[completeEllipticE]: # (completeEllipticE)

Computes the complete elliptic integral of the second kind using parameter `m`.

    print completeEllipticE(0.0) // expect: pi/2

## jacobiSn
[jacobiSn]: # (jacobiSn)

Computes the Jacobi elliptic function `sn(u, m)`.

    print jacobiSn(0.5, 0.2)

## jacobiCn
[jacobiCn]: # (jacobiCn)

Computes the Jacobi elliptic function `cn(u, m)`.

    print jacobiCn(0.5, 0.2)

## jacobiDn
[jacobiDn]: # (jacobiDn)

Computes the Jacobi elliptic function `dn(u, m)`.

    print jacobiDn(0.5, 0.2)

## jacobiAmplitude
[jacobiAmplitude]: # (jacobiAmplitude)

Computes the Jacobi amplitude.

    print jacobiAmplitude(0.5, 0.2)
