#include <iostream>
#include <fstream>
#include <cstdint>

#include "image.h"
#include "pixel.h"


PureImage::PureImage(size_t width, size_t height, Pixel** imageArray) {
    this->width = width; 
    this->height = height;

    this->imageData = imageArray;
};

PureImage::PureImage(const PureImage& cpy) {
    this->width = cpy.width;
    this->height = cpy.height;
    
    Pixel** copyData = cpy.imageData;
    this->imageData = new Pixel*[this->width];
    for (size_t i = 0; i < this->width; i++) {
        this->imageData[i] = new Pixel[height];
    }

    for (size_t i = 0; i < this->width; i++) {
        for (size_t j = 0; j < this->height; j++) {
            this->imageData[i][j] = copyData[i][j];
        }
    }
}

PureImage::~PureImage() {

    for (size_t i = 0; i < this->height; i++) {
        delete[] this->imageData[i];
    }
    delete[] this->imageData;
}

Pixel** PureImage::getData() {
    return this->imageData;
}

Pixel* PureImage::operator[](int i) {
    return this->imageData[i];
}


Pixel** readPPM(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open the file!" << std::endl;
        return nullptr;
    }

    std::string header;
    file >> header;
    if (header != "P6") {
        std::cerr << "Invalid PPM file!" << std::endl;
        return nullptr;
    }

    file >> width >> height;
    int max_val;
    file >> max_val;
    file.ignore(256, '\n'); // Skip to the binary data

    Pixel** image = new Pixel*[static_cast<unsigned long>(height)];
    for (int i = 0; i < height; ++i) {
        image[i] = new Pixel[static_cast<unsigned long>(width)];
        file.read(reinterpret_cast<char*>(image[i]), width * sizeof(Pixel));
    }

    file.close();
    return image;
}

void writeTIFF(const std::string& filename, Pixel** image, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open the file for writing!" << std::endl;
        return;
    }

    // TIFF header
    uint16_t byteOrder = 0x4949; // Little-endian
    uint16_t version = 42;
    uint32_t ifdOffset = 8;

    file.write(reinterpret_cast<char*>(&byteOrder), sizeof(byteOrder));
    file.write(reinterpret_cast<char*>(&version), sizeof(version));
    file.write(reinterpret_cast<char*>(&ifdOffset), sizeof(ifdOffset));

    // Image File Directory (IFD)
    uint16_t numEntries = 8;
    file.write(reinterpret_cast<char*>(&numEntries), sizeof(numEntries));

    // IFD entries
    struct IFDEntry {
        uint16_t tag;
        uint16_t type;
        uint32_t count;
        uint32_t valueOffset;
    };

    IFDEntry widthEntry = {256, 4, 1, static_cast<uint32_t>(width)};
    IFDEntry heightEntry = {257, 4, 1, static_cast<uint32_t>(height)};
    IFDEntry bitsPerSampleEntry = {258, 3, 3, 8};
    IFDEntry compressionEntry = {259, 3, 1, 1};
    IFDEntry photometricEntry = {262, 3, 1, 2};
    IFDEntry stripOffsetsEntry = {273, 4, 1, static_cast<uint32_t>(8 + 2 + numEntries * 12 + 4 + 6)};
    IFDEntry samplesPerPixelEntry = {277, 3, 1, 3};
    IFDEntry rowsPerStripEntry = {278, 4, 1, static_cast<uint32_t>(height)};
    IFDEntry stripByteCountsEntry = {279, 4, 1, static_cast<uint32_t>(width * height * 3)};

    file.write(reinterpret_cast<char*>(&widthEntry), sizeof(widthEntry));
    file.write(reinterpret_cast<char*>(&heightEntry), sizeof(heightEntry));
    file.write(reinterpret_cast<char*>(&bitsPerSampleEntry), sizeof(bitsPerSampleEntry));
    file.write(reinterpret_cast<char*>(&compressionEntry), sizeof(compressionEntry));
    file.write(reinterpret_cast<char*>(&photometricEntry), sizeof(photometricEntry));
    file.write(reinterpret_cast<char*>(&stripOffsetsEntry), sizeof(stripOffsetsEntry));
    file.write(reinterpret_cast<char*>(&samplesPerPixelEntry), sizeof(samplesPerPixelEntry));
    file.write(reinterpret_cast<char*>(&rowsPerStripEntry), sizeof(rowsPerStripEntry));
    file.write(reinterpret_cast<char*>(&stripByteCountsEntry), sizeof(stripByteCountsEntry));

    // Next IFD offset (0 means no more IFDs)
    uint32_t nextIFDOffset = 0;
    file.write(reinterpret_cast<char*>(&nextIFDOffset), sizeof(nextIFDOffset));

    // Bits per sample values
    uint16_t bitsPerSample[3] = {8, 8, 8};
    file.write(reinterpret_cast<char*>(bitsPerSample), sizeof(bitsPerSample));

    // Image data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel& p = image[y][x];
            file.write(reinterpret_cast<char*>(&p.r), 1);
            file.write(reinterpret_cast<char*>(&p.g), 1);
            file.write(reinterpret_cast<char*>(&p.b), 1);
        }
    }

    file.close();
}