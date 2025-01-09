#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

#include "PureImage.h"
#include "Pixel.h"


PureImage::PureImage(size_t width, size_t height)
    : width(width), height(height) {
    
    this->imageData = std::make_unique<std::unique_ptr<Pixel[]>[]>(this->width);

    for (size_t i = 0; i < this->width; ++i) {
        this->imageData[i] = std::make_unique<Pixel[]>(this->height);
    }
}

PureImage::PureImage(size_t width, size_t height, Pixel** imageArray)
    : width(width), height(height) {
    
    this->imageData = std::make_unique<std::unique_ptr<Pixel[]>[]>(this->width);

    for (size_t i = 0; i < width; ++i) {
        this->imageData[i] = std::make_unique<Pixel[]>(height);
        
        for (size_t j = 0; j < width; ++j) {
            this->imageData[i][j] = imageArray[i][j];
        }
    }
}

PureImage::PureImage(const PureImage& cpy)
    : PureImage(cpy.width, cpy.height) {

    for (size_t i = 0; i < this->width; ++i) {
        std::memcpy(imageData[i].get(), cpy.imageData[i].get(), this->height * sizeof(Pixel));
    }
}
