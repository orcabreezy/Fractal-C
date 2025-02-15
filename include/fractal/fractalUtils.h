#pragma once

#include <complex>

typedef double field_t;
typedef std::complex<field_t> complex_t;

const field_t CUTOFF_VALUE = 2.0;

field_t euclidean_norm(complex_t z);