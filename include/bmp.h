#pragma once
#include "image.h"

#pragma pack(push, 1)

struct BmpHeader {
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t dataOffset;
};


struct BmpInfoHeader {
    uint32_t infoHeaderSize;
    int32_t bmpWidth;
    int32_t bmpHeight;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};

struct BmpV5InfoHeader : BmpInfoHeader {
    uint32_t bV5RedMask;
    uint32_t bV5GreenMask;
    uint32_t bV5BlueMask;
    uint32_t bV5AlphaMask;
    uint32_t bV5CSType;
    uint32_t bV5Endpoints[9];
    uint32_t bV5GammaRed;
    uint32_t bV5GammaGreen;
    uint32_t bV5GammaBlue;
    uint32_t bV5Intent;
    uint32_t bV5ProfileData;
    uint32_t bV5ProfileSize;
    uint32_t bV5Reserved;
};

#pragma pack(pop)

class BmpImage : ImageFile {

    const int width;
    const int height;
    
    BmpHeader header;
    BmpInfoHeader infoHeader;
    BmpV5InfoHeader v5InfoHeader;

    bool v5;

    public:
    PureImage image;

    BmpImage(PureImage& image);
    BmpImage(PureImage& image, BmpHeader header, BmpInfoHeader infoHeader);
    BmpImage(PureImage& image, BmpHeader header, BmpV5InfoHeader v5infoHeader);
    // BmpImage(PureImage& image, BmpHeader header, BmpV5InfoHeader infoHeader);

    void writeImage(const std::string& filename);

    static BmpImage readImage(const std::string& filename);

    private:
    static BmpHeader readHeader(const std::string& filename);
    static BmpInfoHeader readInfoHeader(const std::string& filename);
    static BmpV5InfoHeader readV5InfoHeader(const std::string& filename);

    static PureImage readPixelArray(const std::string& filename, const int offset, const int width, const int height);
};
