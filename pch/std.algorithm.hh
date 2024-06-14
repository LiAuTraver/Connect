// Precompiled header for algorithms in std.
#pragma once

#include <algorithm>
#include <numeric>
#include <iterator>
#include <complex>
#include <valarray> // old style numeric array
#include <random>
#include <ratio>
#include <limits>

#if __cplusplus >= 201703L
#include <execution>
#endif // __cplusplus >= 201703L


#if __cplusplus >= 202002L
#include <bit>
#include <ranges>
#include <numbers>
#endif // __cplusplus >= 202002L

#if __cplusplus >= 202203L
//#include <generator>
#include <stdfloat>
#endif // __cplusplus >= 202203L

#if __cplusplus >= 202603L
#include <linalg>
#endif // __cplusplus >= 202603L
