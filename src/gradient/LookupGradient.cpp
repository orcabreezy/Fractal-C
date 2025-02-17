#include "gradient/LookupGradient.h"


LookupGradient::LookupGradient(Gradient* tmplate) {
    
    for (int i = 0; i < DOMAIN; i++) {
        this->lut[i] = tmplate->getColor(i);
    }
}

Pixel LookupGradient::getColor(int input) {
    return this->lut[input];
}