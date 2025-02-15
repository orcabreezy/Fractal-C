#include "Fractal.h"


Fractal::Fractal()
    : ITER_CNT(100) {}


std::complex<Fractal::complex_t> Fractal::iterationValue(std::complex<complex_t> start) {

    int init = 0;
    std::complex<complex_t> accumulator = this->iteration(start);

    while (init < this->ITER_CNT) {
        accumulator = this->iteration(accumulator);
    }

    return accumulator;
}

double Fractal::iterationMagnitude(std::complex<complex_t> start) {

    std::complex<complex_t> value(this->iterationValue(start));

    return this->magnitude(value);    
}