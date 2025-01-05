#include "bmp.h"
#include <fstream>
#include <iostream>


BmpImage::BmpImage(PureImage& image)
    : width(image.width), height(image.height), image(image) {
        
    uint32_t file_size = 54 + width * height * 3;
    uint32_t bitmap_size = file_size - 54;
    this->header = {
        0x4d42,
        file_size,
        0,
        54
    };

    this->infoHeader = {
        40,
        static_cast<int32_t>(width), 
        static_cast<int32_t>(height),
        1, 
        24,
        0,
        bitmap_size,
        0, 
        0, 
        0,
        0
    };
}

BmpImage::BmpImage(PureImage& image, BmpHeader header, BmpInfoHeader infoHeader)
: header(header), infoHeader(infoHeader), image(image), width(infoHeader.bmpWidth), height(infoHeader.bmpHeight) {}

void BmpImage::writeImage(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "could not open file for writing" << std::endl;
        return;
    }

    file.write(reinterpret_cast<char*>(&this->header), sizeof(BmpHeader));
    file.write(reinterpret_cast<char*>(&this->infoHeader), sizeof(BmpInfoHeader));

    // bmp pixel data    
    for (int y = this->height - 1; y >= 0; y--) {
        for (int x = 0; x < this->width; x++) {

            Pixel& p = this->image[x][y];
            
            file.write(reinterpret_cast<char*>(&p.b), 1);
            file.write(reinterpret_cast<char*>(&p.g), 1);
            file.write(reinterpret_cast<char*>(&p.r), 1);
        }
    }
    
    file.close();
}

BmpHeader BmpImage::readHeader(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("could not open file for reading");
    }

    BmpHeader header;

    file.read(reinterpret_cast<char*>(&header), sizeof(BmpHeader));
    file.close();

    return header;
}


BmpImage BmpImage::readImage(const std::string& filename) {

    BmpHeader header = BmpImage::readHeader(filename);

    if (header.signature != 0x4d42) {
        throw std::runtime_error("could not open file for reading");
    }

    BmpInfoHeader infoHeader;

    if (header.dataOffset == 54) {
        infoHeader = BmpImage::readInfoHeader(filename);
    } else {
        infoHeader = BmpImage::readV5InfoHeader(filename);
    }

    std::cout << "offset: " << header.dataOffset << std::endl;
    if (infoHeader.bitsPerPixel != 24) {
        throw std::runtime_error("Only 24-bit BMP files are supported");
    }

    PureImage pi = BmpImage::readPixelArray(filename, header.dataOffset, infoHeader.bmpWidth, infoHeader.bmpHeight);
    return BmpImage(pi, header, infoHeader);
}

BmpInfoHeader BmpImage::readInfoHeader(const std::string& filename) {
    
    std::ifstream file(filename, std::ios::binary);
    file.seekg(14, std::ios::beg);

    BmpInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BmpInfoHeader));
    file.close();
    
    return infoHeader;
}

BmpV5InfoHeader BmpImage::readV5InfoHeader(const std::string& filename) {

    std::ifstream file(filename, std::ios::binary);
    file.seekg(14, std::ios::beg);

    BmpV5InfoHeader v5InfoHeader;

    file.read(reinterpret_cast<char*>(&v5InfoHeader), sizeof(BmpV5InfoHeader));
    file.close();

    return v5InfoHeader;
}

PureImage BmpImage::readPixelArray(const std::string& filename, const int offset, const int width, const int height) {

    std::ifstream file(filename, std::ios::binary);

    Pixel** imageData = new Pixel*[width];
    for (int y = 0; y < width; ++y) {
        imageData[y] = new Pixel[height];
    }

    file.seekg(offset, std::ios::beg);
    for (int y = height - 1; y >= 0; --y) { // BMP files are bottom to top
        for (int x = 0; x < width; ++x) {
            Pixel& p = imageData[x][y];
            file.read(reinterpret_cast<char*>(&p.b), 1);
            file.read(reinterpret_cast<char*>(&p.g), 1);
            file.read(reinterpret_cast<char*>(&p.r), 1);
        }
    }

    file.close();
    return PureImage(width, height, imageData);
}
