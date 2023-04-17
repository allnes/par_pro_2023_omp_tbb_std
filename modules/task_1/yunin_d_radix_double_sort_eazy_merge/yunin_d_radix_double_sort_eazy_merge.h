// Copyright 2023 Yunin Daniil
#ifndef MODULES_TASK_1_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_H_
#define MODULES_TASK_1_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_H_

#include <vector>

void printVector(const std::vector<double>& vec);
std::vector<double> merge(const std::vector<double>& arr1,
    const std::vector<double>& arr2);
std::vector<double> radixSort(const std::vector<double>& data1,
    const std::vector<double>& data2);
bool countSortFinalStep(double* in, double* out, int len);
void countSort(double* in, double* out, int len, int exp);
std::vector<double> randomVec(int size, int leftBound, int rightBound);

#endif  // MODULES_TASK_1_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_YUNIN_D_RADIX_DOUBLE_SORT_EAZY_MERGE_H_
