#pragma once

/**
 * @brief very basic representation of a single 8-bit rgb Pixel
 * 
 */
struct Pixel {

    unsigned char r, g, b;

    Pixel();
    Pixel(unsigned char w);
    Pixel(unsigned char r, unsigned char g, unsigned char b);
    ~Pixel() = default;
};