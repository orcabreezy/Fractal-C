#include "gradient/Gradient.h"

struct SimpleGradient : Gradient {

    /**
     * @brief start colour of the gradient
     * 
     */
    const Pixel start;

    /**
     * @brief end colouf of the gradient
     * 
     */
    const Pixel end;

    static const int DOMAIN = 255;

    Pixel getColor(int input) override;

    SimpleGradient() = delete;

    SimpleGradient(Pixel start, Pixel end);
    ~SimpleGradient() = default;
};