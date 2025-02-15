#include "fractal/Mandelbrot.h"


int Mandelbrot::iterationValue(complex_t start, int detail) {

    complex_t accumulator(0.0, 0.0);

    int i = 0;
    while (this->magnitude(accumulator) <= CUTOFF_VALUE && i < detail) {

        accumulator = accumulator * accumulator + start;

        ++i;
    }

    return i;
}

field_t Mandelbrot::magnitude(complex_t z) {
    return euclidean_norm(z);
}