// Copyright 2023 Sharovatov Daniil
#ifndef MODULES_TASK_1_SHAROVATOV_D_INT_RADIX_MERGE_INT_RADIX_MERGE_H_
#define MODULES_TASK_1_SHAROVATOV_D_INT_RADIX_MERGE_INT_RADIX_MERGE_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

int getMax(std::vector<int>* vec);

void radixSortForExp(std::vector<int>* vec, int exp);

void radixSort(std::vector<int>* vec);

std::vector<int> radixSortMerge(std::vector<int>* vec);

std::vector<int> getRandomVector(int size);

#endif  // MODULES_TASK_1_SHAROVATOV_D_INT_RADIX_MERGE_INT_RADIX_MERGE_H_
