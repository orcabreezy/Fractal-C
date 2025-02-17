#pragma once

#include <complex>
#include <functional>

#include "Fractal.h"
#include "PureImage.h"
#include "gradient/Gradient.h"

struct FractalImage {

    /**
     * @brief UNIT / PIXEL
     * 
     */
    const double SCALE = 3.0 / 1920.0;

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
    PureImage getBoolImage(int depth);

    /**
     * @brief Get the gradual image with a variable gradient
     * 
     * @param depth 
     * @param grad 
     * @return PureImage
     */
    PureImage getGradualImage(int depth, Gradient* grad);

    /**
     * @brief Get the Image as a one-dimensional color gradient
     * 
     * @param depth the maximum depth resolution (max-iter)
     * @return PureImage 
     */
    PureImage getGradualImage(int depth);

    /**
     * @brief Get the Gradual Image object with base depth of 255
     * 
     * @return PureImage 
     */
    PureImage getGradualImage();

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