#include "fractal/ModularMandelbrot.h"
#include "fractal/fractalUtils.h"


int ModularMandelbrot::iterationValue(complex_t start, int depth) {
    int i = 0;
    double a_0 = start.real();
    double b_0 = start.imag();

    double a = 0.0;
    double b = 0.0;
    double a2 = 0.0;
    double b2 = 0.0;

    while (a2 + b2 < 4 && i < depth) {
        
        b = 2 * a * b + b_0;
        a = a2 - b2 + a_0;

        a2 = a * a;
        b2 = b * b;

        ++i;
    }

    return i;
}


field_t ModularMandelbrot::magnitude(complex_t z) {
    return euclidean_norm(z);
}