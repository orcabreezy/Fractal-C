#pragma once

#include "fractal/Fractal.h"

struct Mandelbrot : Fractal {

    /**
     * @brief defines the End for the iteration
     */
    const field_t CUTOFF = 2.0;

    /**
     * @brief maximum iteration
     * 
     */
    const int MAX_ITER = 100;

    /**
     * @brief Defining the Mandelbrot iteration z_(n+1) = z_(n)^2 + c
     * 
     * @param start 
     * @return int 
     */
    int iterationValue(complex_t start) override; 

    /**
     * @brief standard 2-Norm for complex numbers
     * 
     * @param z complex number
     * @return real-valued magnitude
     */
    field_t magnitude(complex_t z) override;

    Mandelbrot() = default;
    ~Mandelbrot() = default;
};