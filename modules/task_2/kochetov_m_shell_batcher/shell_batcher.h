// Copyright 2023 Kochetov Maksim
#ifndef MODULES_TASK_2_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
#define MODULES_TASK_2_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

const int FILLER = 1000000;

std::vector<int> GetRandomVec(int length);
void PrintVec(std::vector<int> vec);
void PrintVec(int* vec, int n);
bool Is2Power(int number);
bool What2Power(int number);
void ShellsortSeq(int* vec, std::size_t n);
void BatcherOddOrEvenMerge(int *partStartPtr, int partSize, bool isOdd);
void BatcherParallelMerge(int* vec, int partSize, int partsCount);
void ShellsortParallel(std::vector<int>* vecPtr);

#endif  // MODULES_TASK_2_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
