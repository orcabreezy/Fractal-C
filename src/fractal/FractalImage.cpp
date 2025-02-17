#include "fractal/FractalImage.h"

FractalImage::FractalImage(int imageWidth, int imageHeight, Fractal* fractal)
: imageWidth(imageWidth), imageHeight(imageHeight),
    width(imageWidth * SCALE), height(imageHeight * SCALE),
    center(0.0, 0.0),
    base(center - (0.5 * width) - (height * std::complex(0.0, 0.5))),
    fractalPtr(fractal) {}


complex_t FractalImage::relativeToAbsolute(int coord_x, int coord_y) {

    return this->base
        + complex_t(coord_x * SCALE, 0.0)
        + complex_t(0.0, coord_y * SCALE)
    ;
}

PureImage FractalImage::getBoolImage(int depth) {

    const Pixel black(0, 0, 0);
    const Pixel white(255, 255, 255);

    PureImage fractalImage(this->imageWidth, this->imageHeight); 

    for (int i = 0; i < imageWidth; i++) {

        for (int j = 0; j < imageHeight; j++) {
            
            const complex_t start = this->relativeToAbsolute(i, j);

            if (fractalPtr->iterationValue(start, depth) < depth) {
                fractalImage.imageData[i][j] = black;
            } else {
                fractalImage.imageData[i][j] = white;
            }
        }
    }

    return fractalImage;
}

PureImage FractalImage::getGradualImage(int depth) {
    
    PureImage fractalImage(this->imageWidth, this->imageHeight); 

    for (int i = 0; i < imageWidth; i++) {

        for (int j = 0; j < imageHeight; j++) {
            
            const complex_t start = this->relativeToAbsolute(i, j);
            int escapeValue = fractalPtr->iterationValue(start, depth);   
            int res = 255 / depth;
            int greyscaleValue = escapeValue * res;
            fractalImage.imageData[i][j] = Pixel(greyscaleValue, greyscaleValue, greyscaleValue);
        }
    }

    return fractalImage;
}

PureImage FractalImage::getGradualImage() {
    return getGradualImage(DEFAULT_DEPTH);
}
