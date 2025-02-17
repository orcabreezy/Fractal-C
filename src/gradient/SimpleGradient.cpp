#include "gradient/SimpleGradient.h"

SimpleGradient::SimpleGradient(Pixel start, Pixel end)
: start(start), end(end) {}

Pixel SimpleGradient::getColor(int input) {
    
    input = input % DOMAIN;

    double factor = double(input) / double(DOMAIN);

    int diff_r = end.r - start.r;
    int diff_g = end.g - start.g;
    int diff_b = end.b - start.b;

    int r = start.r + factor * diff_r;
    int g = start.g + factor * diff_g;
    int b = start.b + factor * diff_b;

    return Pixel(r, g, b);
}