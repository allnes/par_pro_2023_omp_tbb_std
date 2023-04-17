// Copyright 2023 Bushmakin Maksim
#ifndef MODULES_TASK_2_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
#define MODULES_TASK_2_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

#define STUB_ELEMENT (999)

std::vector<int> getRandomIntVec(int length);
std::vector<int> getReversedVec(int length);
void printIntVec(std::vector<int> vec);
void printIntVec(int* vec, int n);

bool isPowerOf2(int number);
bool getPowerOf2(int number);

void shellsortSequential(int* vec, std::size_t n);

void batcherMergeParallel(int* vec, int partSize, int partsCount);
void shellsortOpenMP(std::vector<int>* vecPtr);

#endif  // MODULES_TASK_2_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
