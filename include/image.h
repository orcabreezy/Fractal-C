#pragma once

#include "pixel.h"
#include <string>


Pixel** readPPM(const std::string& filename, int& width, int& height);

void writeTIFF(const std::string& filename, Pixel** image, int widht, int height);

void writeBMP(const std::string& filename, Pixel** image, int widht, int height);


class ImageFile {

    virtual void writeImage(const std::string& filename) = 0;
};

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