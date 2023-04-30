// Copyright 2023 Terina Alina
#ifndef MODULES_TASK_2_TERINA_A_QUICKSORT_SMPL_MERGE_OMP_QS_SMPL_MERGE_H_
#define MODULES_TASK_2_TERINA_A_QUICKSORT_SMPL_MERGE_OMP_QS_SMPL_MERGE_H_
#include <time.h>
#include <random>
#include <vector>

void quickSort(int l, int r, std::vector <double>* list);
void genrndArr(double* arr, int n);
std::vector <double> getRandomVector(int n);
void SimpleMerge(double* arr, int n, double* arr1, int m);
void quicksort(double* arr, int first, int last);
void quickSortPar_OMP(double* arr, int n);
#endif  // MODULES_TASK_2_TERINA_A_QUICKSORT_SMPL_MERGE_OMP_QS_SMPL_MERGE_H_
