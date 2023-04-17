// Copyright 2023 Nosonova Darina

#include <gtest/gtest.h>

#include "./nosonova_d_double_radix_sort_omp.h"

TEST(OMP, Test_OMP_MergeRadixSort_1) {
    DCArray array(10);
    array.setRandValue(-100, 100);
    OMPRadixSort(&array, 8);
    EXPECT_TRUE(array.isSorted());
}

TEST(OMP, Test_OMP_MergeRadixSort_2) {
    DCArray array(100);
    array.setRandValue(-100, 100);
    OMPRadixSort(&array, 8);
    EXPECT_TRUE(array.isSorted());
}

TEST(OMP, Test_OMP_MergeRadixSort_3) {
    DCArray array(1000);
    array.setRandValue(-100, 100);
    OMPRadixSort(&array, 8);
    EXPECT_TRUE(array.isSorted());
}

TEST(OMP, Test_OMP_MergeRadixSort_4) {
    DCArray array(10000);
    array.setRandValue(-100, 100);
    OMPRadixSort(&array, 8);
    EXPECT_TRUE(array.isSorted());
}

TEST(OMP, Test_OMP_MergeRadixSort_5) {
    DCArray array(100000);
    array.setRandValue(-100, 100);
    OMPRadixSort(&array, 8);
    EXPECT_TRUE(array.isSorted());
}
