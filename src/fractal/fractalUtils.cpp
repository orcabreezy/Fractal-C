#include "fractal/fractalUtils.h"

field_t euclidean_norm(complex_t z) {
     
    return (z.imag() * z.imag()) + (z.real() * z.real());
}