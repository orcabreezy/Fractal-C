#include "gradient/Gradient.h"

#include <functional>

/**
 * @brief Map onto an existing gradient with a certain relationship
 */
struct FunctionalGradient : Gradient {

    /**
     * @brief the mapping function f
     * 
     */
    const std::function<int(int)> f;

    /**
     * @brief the basis gradient, onto which is mapped to
     * 
     */
    Gradient& basisGradient;

    Pixel getColor(int input) override;

    /**
     * @brief Construct a Function Gradient
     * 
     * @param basisGradient the underlying gradient, onto which is mapped by
     * @param gradientFunction the function which is used for the mapping
     */
    FunctionalGradient(Gradient& basisGradient, std::function<int(int)> gradientFunction);
    FunctionalGradient() = delete;
    ~FunctionalGradient() = default;
};