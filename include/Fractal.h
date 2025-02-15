#include <complex>
#include <functional>

struct Fractal {

    typedef double complex_t;

    /**
     * @brief The Defining Fractal Function
     * 
     */
    const std::function<std::complex<complex_t>(std::complex<complex_t>)> iteration;

    /**
     * @brief defines the magintued on the given Vector Space
     * 
     */
    const std::function<complex_t(std::complex<complex_t>)> magnitude;
    
    /**
    * @brief Function which computes a fractal iteration
    * 
    * @param start initial value
    * @return The value after ITER_CNT iterations
    */
    std::complex<complex_t> iterationValue(std::complex<complex_t> start);
    
    /**
     * @brief Function which computes the Magnitued
     * 
     * @param start initial value
     * @return The Magnitued after ITER_CNT iteration
     */
    complex_t iterationMagnitude(std::complex<complex_t> start);


    Fractal();
    ~Fractal() = default;


    private:

    /**
     * @brief iteration cutoff value for iterationValue
     * 
     */
    const int ITER_CNT;
};