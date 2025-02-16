#pragma once

#include <complex>

#include "fractal/fractalUtils.h"

/**
 * @brief Fractal iteration interface
 * 
 */
struct Fractal {

    virtual int iterationValue(complex_t start, int depth) = 0;
    virtual field_t magnitude(complex_t z) = 0;
};

