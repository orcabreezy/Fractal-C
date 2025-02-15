#include "fractal/Mandelbrot.h"


int Mandelbrot::iterationValue(complex_t start) {

    complex_t accumulator(0.0, 0.0);

    int i = 0;
    while (this->magnitude(accumulator) <= CUTOFF && i < MAX_ITER) {

        accumulator = accumulator * accumulator + start;

        ++i;
    }

    return i;
}

Fractal::field_t Mandelbrot::magnitude(complex_t z) {
    
    return (z.imag() * z.imag()) + (z.real() * z.real());
}