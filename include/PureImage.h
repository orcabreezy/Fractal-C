#pragma once

#include <cstddef>
#include <memory>

#include "Pixel.h"

/**
 * @brief raw representation of an rgb image Bitmap
 * 
 */
struct PureImage {

    typedef std::unique_ptr<std::unique_ptr<Pixel[]>[]> bitmap_t;

    size_t width;
    size_t height;

    PureImage(size_t width, size_t height);
    PureImage(size_t width, size_t height, Pixel** imageArray);
    PureImage(const PureImage& cpy);
    ~PureImage() = default;

    bitmap_t imageData;
    
};