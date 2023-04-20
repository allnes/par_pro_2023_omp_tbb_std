// Copyright 2023 Yunin Daniil
#ifndef MODULES_TASK_2_YUNIN_D_RADIX_SORT_YUNIN_D_RADIX_SORT_H_
#define MODULES_TASK_2_YUNIN_D_RADIX_SORT_YUNIN_D_RADIX_SORT_H_

#include <vector>
#include <string>

void printVector(const std::vector<double>& vec);
std::vector<double> merge(const std::vector<double>& arr1,
    const std::vector<double>& arr2);
std::vector<double> radixSortSeq(const std::vector<double>& data);
bool countSortFinalStep(double* in, double* out, int len);
void countSort(double* in, double* out, int len, int exp);
std::vector<double> getRandomVector(int size, int leftBound, int rightBound);
std::vector<std::vector<double>> splitVector(const std::vector<double>& data, int numParts);
std::vector<double> radixSortParallOmp(const std::vector<double>& data, int numParts);

#endif  // MODULES_TASK_2_YUNIN_D_RADIX_SORT_YUNIN_D_RADIX_SORT_H_
