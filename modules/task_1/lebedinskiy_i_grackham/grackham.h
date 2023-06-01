// Copyright 2023 Lebedinskiy Ilya
#ifndef MODULES_TASK_1_LEBEDINSKIY_I_GRACKHAM_GRACKHAM_H_
#define MODULES_TASK_1_LEBEDINSKIY_I_GRACKHAM_GRACKHAM_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <utility>

int distance(const std::pair<int, int>& dot1, const std::pair<int, int>& dot2);
int rotation(const std::pair<int, int>& dot1,
const std::pair<int, int>& dot2, const std::pair<int, int>& dot3);
std::vector<std::pair<int, int>> greckham_seq(std::vector<std::pair<int, int>> vec);
std::vector<std::pair<int, int>> gen_dots(int vectorSize);

#endif  // MODULES_TASK_1_LEBEDINSKIY_I_GRACKHAM_GRACKHAM_H_
