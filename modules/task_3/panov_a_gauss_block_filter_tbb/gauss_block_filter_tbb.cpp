// Copyright 2023 Panov Alexey
#include <tbb/tbb.h>
#include <algorithm>
#include "../../../modules/task_3/panov_a_gauss_block_filter_tbb/gauss_block_filter_tbb.h"


int my_min(int a, int b) {
    return (a <= b) ? a : b;
}

using Matrix = std::vector<std::vector<double>>;

Matrix getGaussKernel() {
    return {
        { 1.0 / 16, 1.0 / 8, 1.0 / 16 },
        { 1.0 / 8, 1.0 / 4, 1.0 / 8 },
        { 1.0 / 16, 1.0 / 8, 1.0 / 16 }
    };
}

Color getNeighborIfOutOfBounds(int x, int y, const Image& source) {
    int resultX = x < 0 ? 0 : x >= source.size() ? source.size() - 1 : x;
    int resultY = y < 0 ? 0 : y >= source[0].size() ? source[0].size() - 1 : y;
    return source[resultX][resultY];
}

Color processPixel(int x, int y, const Image& source, const Matrix& kernel) {
    double kernelSum[3] = { 0.0, 0.0, 0.0 };
    const int halfKernelSizeX = kernel.size() / 2;
    const int halfKernelSizeY = kernel[0].size() / 2;
    for (int xOffset = -halfKernelSizeX; xOffset <= halfKernelSizeX; xOffset++) {
        for (int yOffset = -halfKernelSizeY; yOffset <= halfKernelSizeY; yOffset++) {
            const int currentX = x + xOffset;
            const int currentY = y + yOffset;
            Color currentPixel = getNeighborIfOutOfBounds(currentX, currentY, source);

            const int kernelX = xOffset + halfKernelSizeX;
            const int kernelY = yOffset + halfKernelSizeY;
            kernelSum[0] += currentPixel.red * kernel[kernelX][kernelY];
            kernelSum[1] += currentPixel.green * kernel[kernelX][kernelY];
            kernelSum[2] += currentPixel.blue * kernel[kernelX][kernelY];
        }
    }
    return Color(kernelSum[0], kernelSum[1], kernelSum[2]);
}

void processBlock(int blockX, int blockY, const Image& source, Image* _result, const Matrix& kernel) {
    Image& result = *_result;
    const int xBound = my_min(blockX + kernel.size(), source.size());
    const int yBound = my_min(blockY + kernel[0].size(), source[0].size());
    for (int x = blockX; x < xBound; x++) {
        for (int y = blockY; y < yBound; y++) {
            result[x][y] = processPixel(x, y, source, kernel);
        }
    }
}

Image generateImage(int width, int height) {
    return Image(width, std::vector<Color>(height, Color(255, 255, 255)));
}

Image processImage(const Image& source) {
    Matrix kernel = getGaussKernel();
    Image result = Image(source);

    tbb::parallel_for(
        tbb::blocked_range2d<int>(
            0, source.size(),
            0, source[0].size()),
        [&](const tbb::blocked_range2d<int>& r) {
            for (int blockX = r.rows().begin(); blockX < r.rows().end(); blockX += kernel.size()) {
                for (int blockY = r.cols().begin(); blockY < r.cols().end(); blockY += kernel[0].size()) {
                    processBlock(blockX, blockY, source, &result, kernel);
                }
            }
        });
    return result;
}
