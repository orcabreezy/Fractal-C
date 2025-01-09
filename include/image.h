#pragma once

#include <string>

#include "pixel.h"


Pixel** readPPM(const std::string& filename, int& width, int& height);

void writeTIFF(const std::string& filename, Pixel** image, int widht, int height);

void writeBMP(const std::string& filename, Pixel** image, int widht, int height);



struct PureImage {
    
    size_t width;
    size_t height;

    PureImage(size_t width, size_t height, Pixel** imageArray);
    PureImage(const PureImage& cpy);
    ~PureImage();

    Pixel** getData();
    Pixel* operator[](int i);
    Pixel** imageData;
};