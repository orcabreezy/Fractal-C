#pragma once

#include <cstddef>
#include <vector>

#include "Pixel.h"

/**
 * @brief raw representation of a 24-bit rgb bitmap.
 *      
 *  the underlying datastructure is a vector^2, in `imageData` which holds the image in the following struture:
 *     
 *             [, [ Pixel, Pixel, Pixel, ...(height) Pixel], [], [], ...(width) [] ] 
 * 
 *        imageData[width][height]
 */
struct PureImage {

    typedef std::vector<std::vector<Pixel>> bitmap_t;

    size_t width;
    size_t height;
    bitmap_t imageData;

    PureImage(size_t width, size_t height);
    PureImage(size_t width, size_t height, Pixel** imageArray);
    PureImage(const PureImage& cpy);

    PureImage operator=(const PureImage& cpy);
    ~PureImage() = default;

    /**
     * @brief unresolve the standard bayer-mosaic
     * 
     */
    void standard_bayerize();
    
};