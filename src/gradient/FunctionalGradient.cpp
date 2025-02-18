#include "gradient/FunctionalGradient.h"

Pixel FunctionalGradient::getColor(int input) {

    return this->basisGradient.getColor(f(input));
}

FunctionalGradient::FunctionalGradient(Gradient& basisGradient, std::function<int(int)> gradientFunction)
: f(gradientFunction), basisGradient(basisGradient) {};