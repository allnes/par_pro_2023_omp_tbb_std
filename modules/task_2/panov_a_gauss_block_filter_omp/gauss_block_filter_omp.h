// Copyright 2023 Panov Alexey
#ifndef MODULES_TASK_2_PANOV_A_GAUSS_BLOCK_FILTER_OMP_GAUSS_BLOCK_FILTER_OMP_H_
#define MODULES_TASK_2_PANOV_A_GAUSS_BLOCK_FILTER_OMP_GAUSS_BLOCK_FILTER_OMP_H_

#include <vector>

using Channel = unsigned char;

struct Color {
    Channel red;
    Channel green;
    Channel blue;

    Color(Channel red, Channel green, Channel blue) :
        red(red), green(green), blue(blue) {}

    Color& operator=(const Color&) = default;

    bool operator==(const Color& o) const {
        return red == o.red && green == o.green && blue == o.blue;
    }
};

using Image = std::vector<std::vector<Color>>;

Image generateImage(int width, int height);

Image processImage(const Image& source);

#endif  // MODULES_TASK_2_PANOV_A_GAUSS_BLOCK_FILTER_OMP_GAUSS_BLOCK_FILTER_OMP_H_
