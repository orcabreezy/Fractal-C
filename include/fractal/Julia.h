#include "Fractal.h"

struct Julia : Fractal {

    const complex_t juliaConstant;

    int iterationValue(complex_t start, int detail) override;
    field_t magnitude(complex_t z) override;


    Julia() = delete;
    Julia(complex_t juliaConst = complex_t(0.0, 0.0));
    ~Julia() = default;
};