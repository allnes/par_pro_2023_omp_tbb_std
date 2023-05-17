// Copyright 2023 Maksim Orlov

#include <gtest.h>
#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "../../../modules/task_2/orlov_m_simple_merge_quicksort/quicksort_parallel.h"

TEST(orlov_quicksort_Parallel, incorrect_number_of_elements) {
    double* pd = new double;
    EXPECT_ANY_THROW(quicksortParallel(pd, 0));
}

TEST(orlov_quicksort_Parallel, can_sort_array1) {
    double arr[7] = { 3, 5, 2, 10, -3, 0, 4 };
    double sorted[7] = { -3, 0, 2, 3, 4, 5, 10 };
    quicksortParallel(arr, 7);
    ASSERT_TRUE(compareArrays(arr, 7, sorted, 7));
}

TEST(orlov_quicksort_Parallel, can_sort_array2) {
    double arr[6] = { 0.3, 0, -0.4, 1.2, 0.3, -0.2};
    double sorted[6] = { -0.4, -0.2, 0, 0.3, 0.3, 1.2 };
    quicksortParallel(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

TEST(orlov_quicksort_Parallel, can_sort_array3) {
    int n = 50000;
    double* arr1 = new double[n];
    double* arr2 = new double[n];
    double* arr3 = new double[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = 1.0 * rand() / RAND_MAX;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    double begin_time = omp_get_wtime();
    quicksortSequential(arr3, n);
    double sequential_time = omp_get_wtime() - begin_time;
    begin_time = omp_get_wtime();
    quicksortParallel(arr1, n);
    double parallel_time = omp_get_wtime() - begin_time;
    
    
    std::cout << "Sequential time: " << sequential_time << std::endl << \
        "Parallel time: " << parallel_time << std::endl << \
        "Ratio: " << sequential_time / parallel_time << std::endl;
    std::sort(arr2, arr2 + n);
    ASSERT_TRUE(compareArrays(arr1, n, arr2, n));
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}

TEST(orlov_quicksort_Parallel, can_sort_array4) {
    double arr[6] = { 0, -23090, 12239, 0.002, -1290, 0.0022 };
    double sorted[6] = { -23090, -1290, 0, 0.002, 0.0022, 12239 };
    quicksortParallel(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
