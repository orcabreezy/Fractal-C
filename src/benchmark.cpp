#pragma once

#include <chrono>

double benchmark(void (*f)(const size_t), const size_t size) {

    auto start = std::chrono::high_resolution_clock::now();
    f(size);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count();
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

