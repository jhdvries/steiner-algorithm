steiner-algorithm
=================

Implementations 2 approximation algorithm for the generalized steiner netwerk problem

## Requirements

* [gcc](http://gcc.gnu.org)
* [glpk](http://ftp.gnu.org/gnu/glpk/): for lp solver
* [lemon](http://lemon.cs.elte.hu/trac/lemon/wiki/Downloads): lemon graph library

Tested with versions 

* gcc 4.2.1    This is the standard compiler on most computers
* glpk 4.35,   NB: make sure to use this version, for lemon's compatibility
* lemon 1.2.4  A c++ library to 

## Instalation
I will give the whole range of commands that are necessary. This approach has been tested for mac, linux and ubuntu. It is not guaranteed that it works for microsoft. It assumed that the reader has previously compiled and executed code from the command prompt.


First install glpk by typing the parenthesized (.gz) might be required. For mac it is not required.

cd ~

mv Downloads/glpk-4.35.tar(.gz) .

tar xvf(z) glpk-4.35.tar(.gz)

cd glpk-4.35

./configure

make

sudo make install 

Then install glpk by typing the parenthesized (.gz) might be required. For mac it is not required.

cd ~

mv Downloads/lemon-1.2.4.tar(.gz) .

tar xvf(z) lemon-1.2.4.tar(.gz)

cd lemon-1.2.4

./configure

make

sudo make install 

When this is done, the code is obtained cloning the following reporistory

"git clone https://github.com/jhdvries/steiner-algorithm.git"
