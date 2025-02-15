#include <complex>
#include <functional>

struct Fractal {

    typedef double complex_t;

    /**
     * @brief The Defining Fractal Function
     * 
     */
    const std::function<std::complex<complex_t>(
        std::complex<complex_t>, std::complex<complex_t>
    )> iteration;

    const int ITER_CNT;

    /**
     * @brief Function which computes a fractal iteration
     * 
     * @return 
     */
    double iterationValue(std::complex<complex_t>);
};