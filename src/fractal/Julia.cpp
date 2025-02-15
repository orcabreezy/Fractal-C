#include "fractal/Julia.h"

#include "fractal/fractalUtils.h"

Julia::Julia(complex_t juliaConst)
: juliaConstant(juliaConst) {}

int Julia::iterationValue(complex_t start, int detail) {

    complex_t accumulator(start);

    int i = 0;
    while(this->magnitude(accumulator) < CUTOFF_VALUE && i < detail) {

        accumulator = accumulator * this->juliaConstant;
        ++i;
    }

    return i;
}

field_t Julia::magnitude(complex_t z) {
    return euclidean_norm(z);
}