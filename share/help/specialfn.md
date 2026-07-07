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

    print incompleteBeta(2, 3, 0.5)

## inverseIncompleteBeta
[inverseIncompleteBeta]: # (inverseIncompleteBeta)

Computes the inverse of the regularized incomplete beta function.

    print inverseIncompleteBeta(2, 3, 0.5)

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
