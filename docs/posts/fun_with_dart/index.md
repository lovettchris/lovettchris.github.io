# Fun with Dart

![logo](logo.svg)

Dart is a new up and coming language and so I thought it would be fun to do some
simple performance comparisons.

See https://github.com/clovett/primes

This is a simple performance benchmarks comparing C#, Dart and Rust for an entirely CPU bound
problem (no I/O).  The problem is to find all primes under 1,000,000 and test that the [Goldbach
Conjecture](https://en.wikipedia.org/wiki/Goldbach%27s_conjecture) holds for all those numbers.

Times in milliseconds.

| Platform                 | C#     | Dart | Rust |
|--------------------------|--------|------|------|
| Windows 11 AMD Ryzen 9   | 40     | 76   | 17*  |
| Ubuntu 22.04 AMD Ryzen 9 | 43     | 75   | 17*  |

*Rust at 17ms is using a fast non-cryptographic hash on the HashSet.  Using the normal HashSet you
get 62ms.

Clearly Rust is very fast (when you turn off the expensive cryptographic hash algorithm).

C# builds a compiled executable that is almost twice as fast as Dart though and that is really
interesting.  In case you are wondering this is comparing the Dart native compile that you get using `dart compile exe ...`.
