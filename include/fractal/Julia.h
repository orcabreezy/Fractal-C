#include "Fractal.h"

struct Julia : Fractal {

    const complex_t juliaConstant;

    int iterationValue(complex_t start, int depth) override;
    field_t magnitude(complex_t z) override;


    Julia() = delete;
    Julia(complex_t juliaConst);
    ~Julia() = default;
};