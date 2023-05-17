// Copyright 2023 Maksim Orlov

#pragma once
#include <omp.h>
#include <iostream>

void sw(double* a, double* b);
int quicksortPartition(double* arr, int& start, int& finish);
void push(int* stack, int* size, int elem);
int pop(int* stack, int* size);
void quicksortSequentialRecursive(double* arr, int start, int finish);
void quicksortSequential(double* arr, int n);
void quicksortParallelRecursive(double* arr, int start, int finish);
void quicksortParallel(double* arr, int n);
bool compareArrays(double* a1, int n1, double* a2, int n2, double eps = 0.00001);
