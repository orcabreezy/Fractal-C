#pragma once

#include <cstdint>

#include "PureImage.h"
#include "ImageFile.h"

#pragma pack(push, 1)

/**
 * @brief Basic BMP Header
 * 
 */
struct BmpHeader {
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t dataOffset;
};

/**
 * @brief Basic BMP info-header
 * 
 */
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

/**
 * @brief extended BMP info-header for BMP Version 5
 * 
 */
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

/**
 * @brief Bmp Representation of a file
 * 
 */
class BmpImage : ImageFile {

    const int width;
    const int height;

    std::string name = "";
    
    BmpHeader header;
    BmpInfoHeader infoHeader;
    BmpV5InfoHeader v5InfoHeader;

    bool v5;

    public:
    PureImage image;

    BmpImage(const int width, const int height);
    BmpImage(PureImage& image);
    BmpImage(PureImage& image, BmpHeader header, BmpInfoHeader infoHeader, const std::string& name);
    BmpImage(PureImage& image, BmpHeader header, BmpV5InfoHeader v5infoHeader, const std::string& name);

    ~BmpImage() = default;

    /**
     * @brief write the current image with <filename>
     * 
     * @param filename 
     */
    void writeImage(const std::string& filename) override;

    /**
     * @brief delete some color information according to the bayer-mosaic
     * 
     */
    void bayerize();

    /**
     * @brief read an image with name <filename> and return as BmpImage Object
     * 
     * @param filename 
     * @return BmpImage 
     */
    static BmpImage readImage(const std::string& filename);

    private:
    /**
     * @brief Helper: read only the Bmp Header
     * 
     * @param filename 
     * @return BmpHeader 
     */
    static BmpHeader readHeader(const std::string& filename);

    /**
     * @brief Helper: read only the (basic) info-header; automatically starts at correct offset
     * 
     * @param filename 
     * @return BmpInfoHeader 
     */
    static BmpInfoHeader readInfoHeader(const std::string& filename);

    /**
     * @brief Helper: read only the V5 Info-Header; automatically starts at correct offset
     * 
     * @param filename 
     * @return BmpV5InfoHeader 
     */
    static BmpV5InfoHeader readV5InfoHeader(const std::string& filename);

    /**
     * @brief Helper: read the uncompressed BitMap Pixel data as 24-Bit RGB and return as
     *          Pure Image Object
     * 
     * @param filename 
     * @param offset offset in the file (determined by header)
     * @param width  image width (determined by info-header)
     * @param height image height (determined by info-header)
     * @return PureImage 
     */
    static PureImage readPixelArray(const std::string& filename, const int offset, const int width, const int height);

};
