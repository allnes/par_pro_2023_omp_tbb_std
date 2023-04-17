// Copyright 2023 Mikerin Ilya
#ifndef MODULES_TASK_1_MIKERIN_I_SHELL_SORT_SEQ_SHELLSORT_H_
#define MODULES_TASK_1_MIKERIN_I_SHELL_SORT_SEQ_SHELLSORT_H_

#include <vector>
#include <string>
#include <random>
#include <iostream>

std::vector<double> getRandomVector(int  sz);

void MergeSort(std::vector<double> &vec, std::size_t first, std::size_t second); //NOLINT

void ShellSort(std::vector<double> &vec);  //NOLINT

#endif  // MODULES_TASK_1_MIKERIN_I_SHELL_SORT_SEQ_SHELLSORT_H_
