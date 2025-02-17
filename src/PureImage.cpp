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
    int g2 = 3; // green in a gb-col

    if (i % 2 == 0) {

        if (j % 2 == 0) {
            return g2;
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
    int g2 = 3;

    for (size_t i = 0; i < newImage.width; i++) {

        for (size_t j = 0; j < newImage.height; j++) {
            
            int color = determineColor(i, j);             

            if (color == r) {

                newImage.imageData[i][j].b = 0;
                newImage.imageData[i][j].g = 0;
            }

            else if (color == g || color == g2) {

                newImage.imageData[i][j].r = 0;
                newImage.imageData[i][j].b = 0;
            }

            else if (color == b) { 

                newImage.imageData[i][j].r = 0;
                newImage.imageData[i][j].g = 0;
            }
        }
    }
}


void PureImage::standard_debayerize() {

    const int red = 0;
    const int green = 1;
    const int blue = 2;
    const int green2 = 3;

    bitmap_t newImage;

    newImage.reserve(this->width);

    for (int i = 0; i < this->width - 1; i++) {

        newImage.emplace_back();
        newImage.at(i).reserve(this->height);

        for (int j = 0; j < this->height - 1; j++) {
            Pixel newPixel; 

            int color = determineColor(i, j);
            switch (color) {
                
                case red:
                    newPixel.r = this->imageData.at(i).at(j).r;
                    newPixel.g = this->imageData.at(i + 1).at(j).g;
                    newPixel.b = this->imageData.at(i + 1).at(j + 1).b;
                    break;
                
                case green2:
                    newPixel.r = this->imageData.at(i + 1).at(j).r;
                    newPixel.g = this->imageData.at(i).at(j).g;
                    newPixel.b = this->imageData.at(i).at(j + 1).b;
                    break;

                case blue:
                    newPixel.r = this->imageData.at(i + 1).at(j + 1).r;
                    newPixel.g = this->imageData.at(i + 1).at(j).g;
                    newPixel.b = this->imageData.at(i).at(j).b;
                    break;

                case green:
                    newPixel.r = this->imageData.at(i).at(j + 1).r;
                    newPixel.g = this->imageData.at(i).at(j).g;
                    newPixel.b = this->imageData.at(i + 1).at(j).b;
                    break;
                
                default:
                    newPixel.r = 0; newPixel.g = 0; newPixel.b = 0;
                    break;

            }

            newImage.at(i).push_back(newPixel);
        }
    }

    newImage.emplace_back();
    newImage.at(width - 1).reserve(this->height);

    // for (int j = 0; j < height; j++) {
    //     Pixel newPixel = {0, 0, 0};k

    //     newImage.at(width - 1).push_back(newPixel);
    // }

    // for (int i = 0; i < width; i++) {
    //     Pixel newPixel = {0, 0, 0};

    //     newImage.at(i).push_back(newPixel);
    // }


    this->imageData = newImage;
}

Pixel& PureImage::getPixel(int i, int j) {
    return this->imageData.at(i).at(j);
}