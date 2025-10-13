[comment]: # (Specialfn help)

# Specialfn
[specialfn]: # (specialfn)

The `specialfn` extension provides a number of special functions for use in morpho. To use the `specialfn` extension import it,

    import specialfn

[showsubtopics]: # (subtopics)

## gamma
[gamma]: # (gamma)

Computes the Gamma function, defined by:

    Γ(a) = ∫ dt from 0 to ∞ of t^(a-1)*exp(-t) 

To use, import the `specialfn` package: 

    import specialfn

The `gamma` function then takes a single numerical argument:

    print gamma(3.3)

## lgam
[lgam]: # (lgam)

Computes the log of the gamma function (see the entry for `gamma`).

To use, import the `specialfn` package: 

    import specialfn

The `lgam` function then takes a single numerical argument:

    print lgam(4.5)

## igam
[igam]: # (igam)

Computes the lower regularized incomplete Gamma function, defined by:

    P(a, x) = 1/Γ(a) ∫ dt from 0 to x of t^(a-1)*exp(-t) 

It may sometimes be referred to as the "normalized" lower incomplete gamma function.

To use, import the `specialfn` package:

    import specialfn

The `igam` function then takes two numerical arguments:

    print igam(2, 0.5)

## igamc
[igamc]: # (igamc)

Computes the upper regularized incomplete Gamma function, defined by:

    Q(a, x) = 1/Γ(a) ∫ dt from x to ∞ of t^(a-1)*exp(-t) 

Note that there are many related gamma functions; this is sometimes called the "complemented" incomplete gamma function. It may also be referred to as the "normalized" upper incomplete gamma function.

To use, import the `specialfn` package:

    import specialfn

The `igamc` function then takes two numerical arguments:

    print igamc(2, 0.5)

Note that the lower and upper regularized incomplete gamma functions obey the identity:

    P(a,x) + Q(a,x) = 1

and so

    print igam(2, 0.5) + igamc(2, 0.5) // expect: 1
