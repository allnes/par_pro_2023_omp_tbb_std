// Copyright 2023 Busko Polina

#include <omp.h>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "../../../modules/task_2/busko_p_operator_sobelya/operator_sobelya.h"

Img::Img(int x, int y) {
    if ((x <= 0) || (y <= 0))
        throw "ERROR! Img size must be greater then zero";
    sizeX = x;
    sizeY = y;
    image.resize(x, std::vector<int>(y));

    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            image[i][j] = gen() % MAX_VALUE_PIX;
        }
    }
}

Img::Img(int x, int y, int value) {
    if ((x <= 0) || (y <= 0))
        throw "ERROR! Img size must be greater then zero";
    sizeX = x;
    sizeY = y;
    image.resize(x, std::vector<int>(y, value));
}

std::vector<std::vector<int>> Img::SeqSobel() {
    if ((sizeX <= 0) || (sizeY <= 0))
        throw "ERROR! Img size must be greater then zero";

    SobelFilter filter;
    std::vector<std::vector<int>> result = image;

    #pragma omp parallel
    {
    #pragma omp parallel for
    for (int i = 1; i < sizeX - 1; i++) {
        for (int j = 1; j < sizeY - 1; j++) {
            double x = 0.0;
            double y = 0.0;
            for (int fx = 0; fx < 3; fx++) {
                for (int fy = 0; fy < 3; fy++) {
                    x += image[i + fx - 1][j + fy - 1] * filter.xFilter[fx][fy];
                    y += image[i + fx - 1][j + fx - 1] * filter.yFilter[fx][fy];
                }
            }
            double tmp = sqrt(x * x + y * y);
            if (tmp > MAX_VALUE_PIX) {
                result[i][j] = MAX_VALUE_PIX;
            } else {
                if (tmp < MIN_VALUE_PIX) {
                    result[i][j] = MIN_VALUE_PIX;
                } else {
                    result[i][j] = static_cast <int>(tmp);
                }
            }
        }
    }
    }
    return result;
}

std::vector<std::vector<int>> Img::ParallelSobel() {
    if ((sizeX <= 0) || (sizeY <= 0))
        throw "ERROR! Img size must be greater then zero";

    SobelFilter filter;
    std::vector<std::vector<int>> result = image;

    for (int i = 1; i < sizeX - 1; i++) {
        for (int j = 1; j < sizeY - 1; j++) {
            double x = 0.0;
            double y = 0.0;
            for (int fx = 0; fx < 3; fx++) {
                for (int fy = 0; fy < 3; fy++) {
                    x += image[i + fx - 1][j + fy - 1] * filter.xFilter[fx][fy];
                    y += image[i + fx - 1][j + fx - 1] * filter.yFilter[fx][fy];
                }
            }
            double tmp = sqrt(x * x + y * y);
            if (tmp > MAX_VALUE_PIX) {
                result[i][j] = MAX_VALUE_PIX;
            } else {
                if (tmp < MIN_VALUE_PIX) {
                    result[i][j] = MIN_VALUE_PIX;
                } else {
                    result[i][j] = static_cast <int>(tmp);
                }
            }
        }
    }
    return result;
}
void Img::print() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            std::cout << image[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
