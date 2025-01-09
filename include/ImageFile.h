#pragma once

#include <string>

/**
 * @brief base class for all imageFile objects
 * 
 */
class ImageFile {

    /**
     * @brief write the current image to <filename>
     * 
     * @param filename 
     */
    virtual void writeImage(const std::string& filename) = 0;
};
