#pragma once

#include <complex>

/**
 * @brief Fractal iteration interface
 * 
 */
struct Fractal {

    typedef double field_t;
    typedef std::complex<field_t> complex_t;


    virtual int iterationValue(complex_t start) = 0;
    virtual field_t magnitude(complex_t z) = 0;
};