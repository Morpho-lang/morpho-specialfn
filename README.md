# morpho-specialfn

This repository contains the `specialfn` package for Morpho, which provides a collection of special functions.

## Installation

Clone this repository onto your computer in any convenient place:

    git clone https://github.com/morpho-lang/morpho-specialfn.git

then add the location of this repository to your .morphopackages file.

    echo PACKAGEPATH >> ~/.morphopackages 
    where PACKAGEPATH is the location of the git repository.

You need to compile the extension, which you can do by cd'ing to the repository's base folder and typing

    mkdir build
    cd build
    cmake .. 
    make install

## Use

The package can then be loaded into morpho using the `import` keyword.

    import specialfn

Special functions can be used just like any other function, e.g. 

    print gamma(0.5)

For a list of supported functions, start morpho and type

    ? specialfn 

## Cephes copyright statement

The `specialfn` package is based in part on the [Cephes mathematical library](http://www.netlib.org/cephes/) which is provided with the following statement:

    Copyright 1984, 1995, 2000 by Stephen L. Moshier

    Some software in this archive may be from the book _Methods and
    Programs for Mathematical Functions_ (Prentice-Hall or Simon & Schuster
    International, 1989) or from the Cephes Mathematical Library, a
    commercial product. In either event, it is copyrighted by the author.
    What you see here may be used freely but it comes with no support or
    guarantee.

    The two known misprints in the book are repaired here in the
    source listings for the gamma function and the incomplete beta
    integral.

    Stephen L. Moshier
    moshier@na-net.ornl.gov