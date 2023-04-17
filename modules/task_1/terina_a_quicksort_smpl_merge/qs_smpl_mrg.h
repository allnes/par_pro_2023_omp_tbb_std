// Copyright 2023 Terina Alina
#ifndef MODULES_TASK_1_TERINA_A_QUICKSORT_SMPL_MERGE_QS_SMPL_MRG_H_
#define MODULES_TASK_1_TERINA_A_QUICKSORT_SMPL_MERGE_QS_SMPL_MRG_H_

#include <omp.h>
#include <algorithm>
#include <vector>
#include <random>
#include <utility>
#include <iostream>

std::vector <int> getRandomVector(int n);
std::vector<int> GetSortedVec(int n);
std::vector<int> GetReversedVec(int n);
void quickSort(int l, int r, std::vector <int>* list);

#endif  // MODULES_TASK_1_TERINA_A_QUICKSORT_SMPL_MERGE_QS_SMPL_MRG_H_
