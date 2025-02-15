#pragma once

#include <complex>
#include <functional>

#include "Fractal.h"
#include "PureImage.h"

struct FractalImage {

    /**
     * @brief UNIT / PIXEL
     * 
     */
    const double SCALE = 4.0 / 1920.0;

    const int imageWidth;
    const int imageHeight;

    /**
     * @brief fractal image width
     * 
     */
    const field_t width;

    /**
     * @brief fractal
     * 
     */
    const field_t height;
    
    /**
     * @brief 
     * 
     */
    const complex_t center;

    /**
     * @brief top Left corner of the fractal image
     * 
     */
    const complex_t base;

    /**
     * @brief the Image defining Fractal function
     * 
     */
    Fractal* fractalPtr;

    /**
     * @brief Get the Image as a hard boolean set
     * 
     * @return PureImage 
     */
    PureImage getBoolImage();

    /**
     * @brief Image centered arround 0 + 0i
     * 
     * @param widht 
     * @param height 
     * @param fractal A pointer to the underlying fractal
     */
    FractalImage(int imageWidht, int imageHeight, Fractal* fractal);
    
    ~FractalImage() = default;

    private:
    complex_t relativeToAbsolute(int coord_x, int coord_y);
};