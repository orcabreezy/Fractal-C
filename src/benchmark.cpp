#include <chrono>
#include <numeric>

#include "fractal/Mandelbrot.h"
#include "fractal/FractalImage.h"
#include "BmpImage.h"

double benchmark(void (*f)(const size_t), const size_t problem_size) {

    auto start = std::chrono::high_resolution_clock::now();
    f(problem_size);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

std::vector<double> benchmarks(void (*f)(const size_t), const size_t problem_size, const size_t n) {

    std::vector<double> durations;
    durations.reserve(n);

    for (int i = 0; i < n; i++) {
        durations.push_back(benchmark(f, problem_size));
    }

    return durations;
}

double arithmeticMean(std::vector<double> values) {

    return std::accumulate(
        std::begin(values),
        std::end(values),
        0.0,
        [](double a, double b){return a + b;}
    ) / values.size();
}

std::string statisticalBenchmark(void (*f)(const size_t), const size_t problem_size, const size_t n) {

    std::vector<double> durations(benchmarks(f, problem_size, n));

    double mean = arithmeticMean(durations);

    std::stringstream summary;
    for (double duration : durations) {
        summary << duration << "\n";
    }

    summary << "\n-------\n" << "mean: " << mean << std::endl;

    return summary.str();
}


void true_matrix(const size_t size) {

    // create matrix
    int **matrix = new int*[size];

    for (size_t i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            
            matrix[i][j] = 0;
        }
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {

            matrix[i][j] = static_cast<int>(i + j);
        }
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {

            matrix[i][j] = (matrix[i][j] * matrix[i][j]);
        }
    }

    for (size_t i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


void flat_matrix(const size_t size) {

    int *matrix = new int[size * size];

    for (size_t i = 0; i < size * size; i++) {
        matrix[i] = 0;
    }

    for (size_t i = 0; i < size * size; i++) {
        matrix[i] = static_cast<int>(i + 4);
    }

    for (size_t i = 0; i < size * size; i++) {
        matrix[i] = matrix[i] * matrix[i];
    }
    delete[] matrix;
}

void mandelbrot_rendering(const size_t size) {

  Mandelbrot fr;
  FractalImage fi(1920, 1080, &fr);
  PureImage pi(fi.getGradualImage());
  BmpImage imageFile(pi);
}

