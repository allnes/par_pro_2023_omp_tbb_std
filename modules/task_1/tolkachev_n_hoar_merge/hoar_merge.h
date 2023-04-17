// Copyright 2023 Tolkachev
#ifndef MODULES_TASK_1_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_
#define MODULES_TASK_1_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_
#include <algorithm>
#include <vector>
std::vector<int> Getvec(int n);
void HoarSort(std::vector<int>* arr, int first, int last);
void Merge(std::vector<int>* arr, std::vector<int>* arr2, int left, int mid,
           int right);
void MergeSort(std::vector<int>* arr, std::vector<int>* arr2, int left,
               int right);
#endif  // MODULES_TASK_1_TOLKACHEV_N_HOAR_MERGE_HOAR_MERGE_H_
