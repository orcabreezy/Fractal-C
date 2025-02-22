#include "fractal/FractalImage.h"
#include "fractal/fractalUtils.h"
#include "gradient/SimpleGradient.h"
#include "gradient/LookupGradient.h"

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

    const Pixel black;
    const Pixel white(255);

    PureImage fractalImage(this->imageWidth, this->imageHeight); 

    for (int i = 0; i < imageWidth; i++) {

        for (int j = 0; j < imageHeight; j++) {
            
            const complex_t start = this->relativeToAbsolute(i, j);

            if (fractalPtr->iterationValue(start, depth) < depth) fractalImage.getPixel(i, j) = black;
            else fractalImage.getPixel(i, j) = white;
            
        }
    }

    return fractalImage;
}

PureImage FractalImage::getGradualImage(int depth, Gradient* grad) {
    
    PureImage fractalImage(this->imageWidth, this->imageHeight); 

    for (int i = 0; i < imageWidth; i++) {

        for (int j = 0; j < imageHeight; j++) {
            
            const complex_t start = this->relativeToAbsolute(i, j);
            int escapeValue = fractalPtr->iterationValue(start, depth);   
            double res = 255.0 / depth;
            Pixel color(grad->getColor(int(res * escapeValue)));
            fractalImage.getPixel(i, j) = 
                res * escapeValue == 255 ? Pixel() : grad->getColor(int(res * escapeValue));
;
        }
    }

    return fractalImage;
}

PureImage FractalImage::getGradualImage(int depth) {
    SimpleGradient sg(Pixel(0), Pixel(255));
    LookupGradient freshGradient(&sg);
    return getGradualImage(depth, &freshGradient);
}

PureImage FractalImage::getGradualImage() {
    SimpleGradient sg(Pixel(0), Pixel(255));
    LookupGradient freshGradient(&sg);
    return getGradualImage(DEFAULT_DEPTH, &freshGradient);
}
