# Binomial Distribution Calculator

> For very large sample sample sizes (around 10000 or more as long as your architecture properly implements long double)

Some may ask, "why not use the normal approximation?"

Yes that would be far more accurate when `double` does not have enough precision.




## Table of Contents

- [Purpose](#purpose)

- [Installation](#installation)

- [Features, Tips, and Examples](#features)

## Purpose
Calculates values of the binomial probability and cumulative distribution
functions accurately for very large sample sizes. Multiplications and divisions
are alternated to keep numbers close to $1$. Further, intermediate values are
saved in the recursion's stack frames. This allows more precision than would be
achieved by saving intermediate values as a floating-point type with the
highest available precision. Indeed, this approach would not work as well if
implemented with a `for` loop or tail recursion.

## Installation
Type `make` in the directory you cloned. 

## Features
Get started just by typing `./bin` to start using the program interactively. 
Enter any non numerical character or `^D` to exit.
  
Use the program without entering interactive mode by typing in
```
./bin -a <sample size> <probability> -k <value within the domain>
```

### Warning
Currently uses `long double` internally. Many architectures today (such as
Apple ARM) typedef `long double` as `double`, making the calculator fail for
$N>1000$. The solution is likely to use gcc's \_float128 internally and drop
support for clang.


### Tips
- Strip off unnecessary output with the `-b` flag
- Skip calculating the CDF or PDF with the `-p` and `-c` flags respectively
- Enter distribution parameters on the command line but still use interactive 
mode by using the -i flag

### Example Usage
```
Shawn@SadMachine binomial_dist % ./bin -iak 0.5 30 15
p(15) = 0.1444644480943680
P(X<=15) = 0.5722322240471840
k = 20
p(20) = 0.0279816007241607
P(X<=20) = 0.9786130273714662
k = ^D
Shawn@SadMachine binomial_dist % ./bin -cak 10000 0.15 1400
P(X<=1400) = 0.0024817556128307
```
