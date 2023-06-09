// Copyright 2023 Maksim Orlov

#include <cstdlib>
#include "../../../modules/task_2/orlov_m_simple_merge_quicksort/quicksort_parallel.h"

int quicksortPartition(double* arr, int start, int finish) {
    int pivot = finish - 1;
    int largeElem = start;
    for (int i = start; i < finish; i++) {
        if (arr[i] < arr[pivot]) {
            std::swap(arr[i], arr[largeElem]);
            largeElem++;
        }
    }
    std::swap(arr[pivot], arr[largeElem]);
    return largeElem;
}

void push(int* stack, int* size, int elem) {
    stack[(*size)++] = elem;
}

int pop(int* stack, int* size) {
    return stack[--(*size)];
}

void quicksortSequentialRecursive(double* arr, int start, int finish) {
    if (finish <= start + 1) return;
    int pivotPos = quicksortPartition(arr, start, finish);
    quicksortSequentialRecursive(arr, start, pivotPos);
    quicksortSequentialRecursive(arr, pivotPos + 1, finish);
}

void quicksortSequential(double* arr, int n) {
    if (n < 1) throw "Too few elements";
    quicksortSequentialRecursive(arr, 0, n);
}

void quicksortParallelRecursive(double* arr, int start, int finish) {
    if (finish <= start + 1) return;
    int pivotPos = quicksortPartition(arr, start, finish);
#pragma omp parallel sections
    {
#pragma omp section
        {
            if (pivotPos > start + 1) quicksortParallelRecursive(arr, start, pivotPos);
        }
#pragma omp section
        {
            if (finish > pivotPos + 2) quicksortParallelRecursive(arr, pivotPos + 1, finish);
        }
    }
}

void quicksortParallel(double* arr, int n) {
    if (n < 1) throw "Too few elements";
    quicksortParallelRecursive(arr, 0, n);
}

bool compareArrays(double* a1, int n1, double* a2, int n2, double eps) {
    if (n1 != n2) return false;
    for (int i = 0; i < n1; i++) {
        if (std::abs(a1[i] - a2[i]) > eps) {
            return false;
        }
    }
    return true;
}
