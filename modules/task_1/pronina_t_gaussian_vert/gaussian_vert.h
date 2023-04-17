// Copyright 2023 Pronina Tatiana
#ifndef MODULES_TASK_1_PRONINA_T_GAUSSIAN_VERT_GAUSSIAN_VERT_H_
#define MODULES_TASK_1_PRONINA_T_GAUSSIAN_VERT_GAUSSIAN_VERT_H_

#include <vector>
#include <random>
#include <iostream>

struct rgb_coub {
    unsigned char red, green, blue;
};
bool operator==(const rgb_coub& a, const rgb_coub& b);
std::vector<rgb_coub> getRandomImage(int rows, int columns);
std::vector<rgb_coub> Gaussian_Filter_Seq(const std::vector<rgb_coub>& img,
    int rows, int columns, const double sigma);

#endif  // MODULES_TASK_1_PRONINA_T_GAUSSIAN_VERT_GAUSSIAN_VERT_H_
