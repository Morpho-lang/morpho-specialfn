# morpho-specialfn license

Please note that this morpho package is comprised of code from an external package and is provided with a hybrid license as described below.

## Cephes copyright statement

The `specialfn` package is based in part on the [Cephes mathematical library](http://www.netlib.org/cephes/). Cephes files are in `/src/cephes`. These have been modified from their original version to use ANSI function definitions, and in one case (`mtherr.c`) to provide `morpho` error reporting.
 
The Cephes library is accompanied by the following statement: 

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

## MIT License

Any code other than that in `/src/cephes` is provided under an MIT license:

    Copyright 2026 T J Atherton

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.