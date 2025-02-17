#include "Pixel.h"

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
: r(r), g(g), b(b) {}

Pixel::Pixel() : r(0), g(0), b(0) {}

Pixel::Pixel(unsigned char w) : r(w), g(w), b(w) {}