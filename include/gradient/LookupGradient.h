#pragma once

#include <array>

#include "gradient/Gradient.h"

struct LookupGradient : Gradient {

    std::array<Pixel, DOMAIN> lut;

    Pixel getColor(int input) override;

    LookupGradient(Gradient* tmplate);
    LookupGradient() = delete; 
    ~LookupGradient() = default;
};
