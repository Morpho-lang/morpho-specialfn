# morpho-specialfn

This repository contains the `specialfn` package for Morpho, which provides a collection of special functions.

## Installation

The `specialfn` package can be installed with `morphopm`. Type the following into a terminal:

    morphopm install specialfn

## Use

The package can then be loaded into morpho using the `import` keyword.

    import specialfn

Special functions can be used just like any other function, e.g. 

    print gamma(0.5)

For a list of supported functions, start morpho and type

    ? specialfn 

## Manual installation

Clone this repository onto your computer in any convenient place:

    git clone https://github.com/morpho-lang/morpho-specialfn.git

then add the location of this repository to your .morphopackages file.

    echo PACKAGEPATH >> ~/.morphopackages 
    where PACKAGEPATH is the location of the git repository.

You need to compile the extension, which you can do by cd'ing to the repository's base folder and typing

    cmake -S . -B build
    cmake --build build --config Release
    cmake --install build --config Release

## License

See [LICENSE.md](LICENSE.md) for copyright and licensing information.

