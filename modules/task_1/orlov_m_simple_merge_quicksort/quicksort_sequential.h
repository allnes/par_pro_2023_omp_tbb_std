// Copyright 2023 Maksim Orlov

#pragma once
#include <utility>

int quicksortPartition(double* arr, int start, int finish);
void quicksortSequentialRecursive(double* arr, int start, int finish);
void quicksortSequential(double* arr, int n);
bool compareArrays(double* a1, int n1, double* a2, int n2, double eps = 0.00001);
