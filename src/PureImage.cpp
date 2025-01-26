#include <cstring>

#include "PureImage.h"
#include "Pixel.h"


PureImage::PureImage(size_t width, size_t height)
    : width(width), height(height) {
    
    this->imageData = std::vector<std::vector<Pixel>>();
    this->imageData.reserve(width);

    for (size_t i = 0; i < this->width; ++i) {
        std::vector<Pixel> innerVector = std::vector<Pixel>(height);
        this->imageData.push_back(innerVector);
    }

}

PureImage::PureImage(size_t width, size_t height, Pixel** imageArray)
    : width(width), height(height) {
    
    this->imageData = std::vector<std::vector<Pixel>>();
    this->imageData.reserve(width);

    for (size_t i = 0; i < width; ++i) {
        std::vector<Pixel> innerVector = std::vector<Pixel>();
        innerVector.reserve(height);
        for (size_t j = 0; j < height; ++j) {
            innerVector.emplace_back(imageArray[i][j]);
        }
        this->imageData.push_back(innerVector);
    }
}

PureImage::PureImage(const PureImage& cpy)
    : PureImage(cpy.width, cpy.height) {

    this->imageData = cpy.imageData;
}

PureImage PureImage::operator=(const PureImage& cpy) {
    return PureImage(cpy);
}

int determineColor(int i, int j) {

    int r = 0;
    int g = 1;
    int b = 2;

    if (i % 2 == 0) {
        // g-b row

        if (j % 2 == 0) {
            return g;
        }

        return b;
    }
    
    // r-g row
    if (j % 2 == 0) {

        return r;
    }
    return g;
}

void PureImage::standard_bayerize() {

    PureImage& newImage = *this;

    int r = 0;
    int g = 1;
    int b = 2;   

    for (size_t i = 0; i < newImage.width; i++) {

        for (size_t j = 0; j < newImage.height; j++) {
            
            int color = determineColor(i, j);             

            if (color == r) {

                newImage.imageData[i][j].b = 0;
                newImage.imageData[i][j].g = 0;
            }

            else if (color == g) {

                newImage.imageData[i][j].r = 0;
                newImage.imageData[i][j].b = 0;
            }

            else {

                newImage.imageData[i][j].r = 0;
                newImage.imageData[i][j].g = 0;
            }
        }
    }
}