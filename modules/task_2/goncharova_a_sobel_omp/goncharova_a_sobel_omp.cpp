// Copyright 2023 Goncharova Anna

#include <random>
#include <ctime>
#include <vector>
#include "../../../modules/task_2/goncharova_a_sobel_omp/goncharova_a_sobel_omp.h"

const image<char> KERNEL_X({1, 0, -1, 2, 0, -2, 1, 0, -1}, 3, 3);
const image<char> KERNEL_Y({1, 2, 1, 0, 0, 0, -1, -2, -1}, 3, 3);

image<uint8_t> randImage(size_t columns, size_t rows) {
    if (rows == 0 || columns == 0) {
        throw -1;
    }
    std::vector<uint8_t> matrix(columns * rows);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            matrix[i * rows + j] = static_cast<uint8_t>(gen() % 256);
    return image<uint8_t>(matrix, columns, rows);
}

image<uint8_t> sobelSequence(image<uint8_t> inImage) {
    if (inImage._rows == 0 || inImage._columns == 0 || inImage._matrix.empty()) {
        throw -1;
    }
    image<uint8_t> result(inImage._columns, inImage._rows);
    for (size_t i = 1; i < inImage._rows - 1; ++i)
        for (size_t j = 1; j < inImage._columns - 1; ++j) {
            int index = i * inImage._columns + j;
            int resX = 0, resY = 0;
            int indexKernel = 0;
            for (int ki = -1; ki <= 1; ki++)
                for (int kj = -1; kj <= 1; kj++) {
                    resX += KERNEL_X._matrix[indexKernel] * inImage._matrix[(i + ki) * inImage._columns + j + kj];
                    resY += KERNEL_Y._matrix[indexKernel] * inImage._matrix[(i + ki) * inImage._columns + j + kj];
                    indexKernel++;
                }
            result._matrix[index] = sqrt(resX * resX + resY * resY) > 255 ? 255 : sqrt(resX * resX + resY * resY);
        }
    return result;
}

image<uint8_t> sobelOmp(image<uint8_t> inImage) {
    if (inImage._rows == 0 || inImage._columns == 0 || inImage._matrix.empty()) {
        throw -1;
    }
    image<uint8_t> result(inImage._columns, inImage._rows);
    #pragma omp parallel for
    for (int i = 1; i < static_cast<int>(inImage._rows) - 1; ++i)
        for (int j = 1; j < static_cast<int>(inImage._columns) - 1; ++j) {
            int index = i * inImage._columns + j;
            int resX = 0, resY = 0;
            int indexKernel = 0;
            for (int ki = -1; ki <= 1; ki++)
                for (int kj = -1; kj <= 1; kj++) {
                    resX += KERNEL_X._matrix[indexKernel] * inImage._matrix[(i + ki) * inImage._columns + j + kj];
                    resY += KERNEL_Y._matrix[indexKernel] * inImage._matrix[(i + ki) * inImage._columns + j + kj];
                    indexKernel++;
                }
            result._matrix[index] = sqrt(resX * resX + resY * resY) > 255 ? 255 : sqrt(resX * resX + resY * resY);
        }
    return result;
}

