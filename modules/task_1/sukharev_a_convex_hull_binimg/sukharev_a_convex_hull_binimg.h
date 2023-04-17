// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TASK_1_SUKHAREV_A_CONVEX_HULL_BINIMG_SUKHAREV_A_CONVEX_HULL_BINIMG_H_
#define MODULES_TASK_1_SUKHAREV_A_CONVEX_HULL_BINIMG_SUKHAREV_A_CONVEX_HULL_BINIMG_H_

#include <vector>
#include <utility>

void printImg(const std::vector<std::vector<int>>& g);

std::vector<std::vector<int>> build_convhull_img(
        const std::vector<std::vector<int>>& img);
std::vector<std::vector<std::pair<int, int>>> build_components(
        const std::vector<std::vector<int>>& img, const int n, const int m);
std::vector<std::pair<int, int>> graham(
                const std::vector<std::pair<int, int>>& _v);
#endif  // MODULES_TASK_1_SUKHAREV_A_CONVEX_HULL_BINIMG_SUKHAREV_A_CONVEX_HULL_BINIMG_H_
