// Copyright 2023 Terina Alina
#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include "../../../modules/task_2/terina_a_quicksort_smpl_merge_omp/qs_smpl_merge.h"

TEST(OpenMP_version_QS, can_sort_mas_10000) {
    int n = 10000;
    double* arr = new double[n];
    std::vector<double> vec;
    genrndArr(arr, n);

    for (int i = 0; i < n; i++)
        vec.push_back(arr[i]);
    quickSort(0, n - 1, &vec);
    quickSortPar_OMP(arr, n);

    bool res = std::equal(&arr[0], &arr[n], &vec[0]);
    ASSERT_EQ(res, 1);
}

TEST(OpenMP_version_QS, can_sort_already_sorted_mas) {
    int n = 10000;
    double* arr = new double[n];
    std::vector<double> vec;
    genrndArr(arr, n);
    for (int i = 0; i < n; i++)
        vec.push_back(arr[i]);
    quickSort(0, n - 1, &vec);
    quickSortPar_OMP(arr, n);

    bool res = std::equal(&arr[0], &arr[n], &vec[0]);
    ASSERT_EQ(res, 1);
}

TEST(OpenMP_version_QS, can_sort_mas_with_inversion) {
    int n = 100000;
    double* arr = new double[n];
    std::vector<double> vec;
    genrndArr(arr, n);

    quicksort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        vec.push_back(arr[i]);
    for (int i = 0; i < n / 2; i++) {
        std::swap(arr[i], arr[n - i - 1]);
    }

    quickSortPar_OMP(arr, n);

    bool res = std::equal(&arr[0], &arr[n], &vec[0]);
    ASSERT_EQ(res, 1);
}

TEST(OpenMP_version_QS, can_sort_mas_with_only_zero_elems) {
    int n = 100000;
    double* arr = new double[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    quickSortPar_OMP(arr, n);
    ASSERT_EQ(arr[n-3], 0);
}
TEST(OpenMP_version_QS, can_sort_mas_with_one_elem) {
    int n = 100000;
    double* arr = new double[n];
    arr[n/2] = 4;
    quickSortPar_OMP(arr, n);
    ASSERT_EQ(arr[n - 1], 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
