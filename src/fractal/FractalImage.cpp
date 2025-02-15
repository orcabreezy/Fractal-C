#include "fractal/FractalImage.h"

FractalImage::FractalImage(int imageWidth, int imageHeight, Fractal* fractal)
: imageWidth(imageWidth), imageHeight(imageHeight),
    width(imageWidth * SCALE), height(imageHeight * SCALE),
    center(-1.0, 0.0),
    base(center - (0.5 * width) - (height * std::complex(0.0, 0.5))),
    fractalPtr(fractal) {}


Fractal::complex_t FractalImage::relativeToAbsolute(int coord_x, int coord_y) {

    return this->base
        + Fractal::complex_t(coord_x * SCALE, 0.0)
        + Fractal::complex_t(0.0, coord_y * SCALE)
    ;
}

PureImage FractalImage::getBoolImage() {

    const Pixel black(0, 0, 0);
    const Pixel white(255, 255, 255);

    PureImage fractalImage(this->imageWidth, this->imageHeight);
    
    for (int i = 0; i < imageWidth; i++) {

        for (int j = 0; j < imageHeight; j++) {
            
            const Fractal::complex_t start = this->relativeToAbsolute(i, j);

            if (fractalPtr->iterationValue(start) < 100) {
                fractalImage.imageData[i][j] = black;
            } else {
                fractalImage.imageData[i][j] = white;
            }
        }
    }

    return fractalImage;
}
