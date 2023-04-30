// Copyright 2023 Tolkachev
#ifndef MODULES_TASK_2_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_
#define MODULES_TASK_2_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_

#include <omp.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>

std::vector<int> Getvec(int n);
void HoarSort(std::vector<int>* arr, int first, int last);
std::vector<int> Merge(const std::vector<int>& arr,
                       const std::vector<int>& arr2);
std::vector<int> SortParallel(std::vector<int>* vec);
#endif  // MODULES_TASK_2_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_
