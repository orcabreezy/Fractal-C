#include <complex>
#include <functional>

#include "Fractal.h"
#include "PureImage.h"

struct FractalImage {

    typedef double complex_t;

    /**
     * @brief top Left corner of the fractal image
     * 
     */
    const std::complex<double> BASE;

    /**
     * @brief fractal image width
     * 
     */
    const double WIDTH;

    /**
     * @brief fractal
     * 
     */
    const double HEIGHT;

    /**
     * @brief Cutoff vaue for boolean iteration
     * 
     */
    const double CUTOFF;
    
    /**
     * @brief the Image defining Fractal function
     * 
     */
    const Fractal fractal;

    /**
     * @brief Get the image with rate of escape colouring
     * 
     * @return PureImage 
     */
    PureImage getGradualImage();

    /**
     * @brief Get the Image as a hard boolean set
     * 
     * @return PureImage 
     */
    PureImage getBoolImage();

    FractalImage();

    private:

    std::complex<double> relativeToAbsolute(int coord_x, int coord_y);
};