  // Copyright 2023 Kudryashov Nikita
#include "../../../modules/task_2/kudryashov_n_gauss_vertical/kudryashov_n_gauss_vertical.h"

int clamp(int value, int min, int max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

std::vector<std::vector<double>> createKernel() {
    int size = 3;
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double norm = 0;
    double sigma = 0.6;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            kernel[i + 1][j + 1] = exp(-(i * i + j * j) /
            (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            norm += kernel[i + 1][j + 1];
        }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i][j] /= norm;
    return kernel;
}

int calcNewPixelColor(std::vector<std::vector<int>> image, int height,
int width, int y, int x, std::vector<std::vector<double>> kernel) {
    double resultColor = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int xn = clamp(x + i, 0, width - 1);
            int yn = clamp(y + j, 0, height - 1);
            resultColor += image[yn][xn] * kernel[i + 1][j + 1];
        }
    }
    return clamp(static_cast<int>(resultColor), 0, 255);
}

std::vector<std::vector<int>> gauss_filter_sequence(
const std::vector<std::vector<int>>& image, int height, int width) {
    std::vector<std::vector<int>> resultImage(height, std::vector<int>(width));
    std::vector<std::vector<double>> kernel = createKernel();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            resultImage[j][i] = calcNewPixelColor(image, height, width,
            j, i, kernel);
        }
    }

    return resultImage;
}

std::vector<std::vector<int>> gauss_filter_parallel(
    const std::vector<std::vector<int>>& image, int height, int width) {
    std::vector<std::vector<int>> resultImage(height, std::vector<int>(width));
    std::vector<std::vector<double>> kernel = createKernel();
#pragma omp parallel for shared(image, resultImage, height, width)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            resultImage[j][i] = calcNewPixelColor(image, height, width,
                j, i, kernel);
        }
    }

    return resultImage;
}
