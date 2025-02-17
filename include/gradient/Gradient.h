#pragma once

#include <vector>

#include "Pixel.h"

/**
 * @brief interface of a gradient
 * 
 */
struct Gradient {
    
    /**
     * @brief maps a natural number to a color
     * 
     * @param input 
     * @return Pixel output color
     */
    virtual Pixel getColor(int input) = 0;
};