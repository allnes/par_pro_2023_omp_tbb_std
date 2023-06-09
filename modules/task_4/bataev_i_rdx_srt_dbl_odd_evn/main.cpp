// Copyright 2023 Bataev Ivan
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_4/bataev_i_rdx_srt_dbl_odd_evn/rdx_srt_dbl_odd_evn.h"

TEST(Parallel, Test_RadixSort) {
    const int size = 9;
    std::vector<double> v1 = { 7698721.0, -456412.0, 2342432.0, 333276.0, -11.0, 765.0, -2019.0, 0.0, 11113.0 };
    // printVector(v1);

    parRdxSrt(&v1, size, 1);
    // printVector(v1);

    std::vector<double> v2 = { -456412.0, -2019.0, -11.0, 0.0, 765.0, 11113.0, 333276.0, 2342432.0, 7698721.0 };
    ASSERT_EQ(v1, v2);
}

TEST(Parallel, Test_OddEvenMerge) {
    std::vector<double> v1 = { -33.5539, -16.0284, 0.0245546, 63.516,
                                    -3.70987, 1.50916, 9.31509, 48.857,
                                        -39.0917, 0.0, 1.59403, 16.7192 };
    // all 3 parts are sorted and the same size 4

    std::vector<double> tmp(v1.size());
    oddEvnMerge(&v1, &tmp, 3, 4);
    // sorting network that was built and used:
    // Comparators: [(1, 2), (0, 1), (1, 2)]
    // Steps: [{(1, 2)}, {(0, 1)}, {(1, 2)}]

    std::vector<double> v2 = { -39.0917, -33.5539, -16.0284, -3.70987,
                                    0.0, 0.0245546, 1.50916, 1.59403,
                                        9.31509, 16.7192, 48.857, 63.516 };
    ASSERT_EQ(v1, v2);
}

TEST(Parallel, Test_RadixSort_OddEvenMerge_1) {
    const int size = 11;
    std::vector<double> v1 = { 262.163, 581.331, -893.141, -602.229, 468.981,
                                -183.773, 831.814, 600.811, 72.1124, 581.331, -16.6527 };

    parRdxSrt(&v1, size, 4);  // 4 - 11 % 4 = 1 -> 1 temp elem will be added
    // sorting network that was built and used:
    // Comparators: [(0, 1), (2, 3), (0, 2), (1, 3), (1, 2)]
    // Steps: [{(0, 1), (2, 3)}, {(0, 2), (1, 3)}, {(1, 2)}]

    std::vector<double> v2 = { -893.141, -602.229, -183.773, -16.6527, 72.1124,
                                262.163, 468.981, 581.331, 581.331, 600.811, 831.814 };
    ASSERT_EQ(v1, v2);
}

TEST(Parallel, Test_RadixSort_OddEvenMerge_2) {
    const int size = 16; const double left = -1000.0; const double right = 1000.0;
    std::vector<double> v1 = getRandomVector(size, left, right);
    std::vector<double> v2(v1);

    parRdxSrt(&v1, size, 6);  // 6 - 16 % 6 = 2 -> 2 temp elems will be added
    // sorting network that was built and used:
    // Comparators: [(1, 2), (0, 1), (1, 2), (4, 5), (3, 4), (4, 5),
    //               (0, 3), (2, 5), (2, 3), (1, 4), (1, 2), (3, 4)]
    // Steps: [{(1, 2), (4, 5)}, {(0, 1), (3, 4)}, {(1, 2), (4, 5), (0, 3)},
    //         {(2, 5), (1, 4)}, {(2, 3)}, {(1, 2), (3, 4)}]

    std::sort(v2.begin(), v2.end());
    ASSERT_EQ(v1, v2);
}

TEST(Parallel, Test_Default_Threads_1) {
    const int size = 100000; const double left = -100000.0; const double right = 100000.0;
    std::vector<double> v1 = getRandomVector(size, left, right);
    std::vector<double> v2(v1);

    parRdxSrt(&v1, size);  // numParts = default number of threads

    std::sort(v2.begin(), v2.end());
    ASSERT_EQ(v1, v2);
}

// TEST(Parallel, Test_Default_Threads_2) {
//     const int size = 1000000; const double left = -100000.0; const double right = 100000.0;
//     std::vector<double> v1 = getRandomVector(size, left, right);
//     std::vector<double> v2(v1);

//     parRdxSrt(&v1, size);  // numParts = default number of threads

//     std::sort(v2.begin(), v2.end());
//     ASSERT_EQ(v1, v2);
// }

// TEST(Parallel, Test_Default_Threads_3) {
//     const int size = 10000000; const double left = -100000.0; const double right = 100000.0;
//     std::vector<double> v1 = getRandomVector(size, left, right);
//     std::vector<double> v2(v1);

//     parRdxSrt(&v1, size);  // numParts = default number of threads

//     std::sort(v2.begin(), v2.end());
//     ASSERT_EQ(v1, v2);
// }

TEST(Parallel, Test_AlreadySorted) {
    const int size = 6;
    std::vector<double> v1 = { -6121.59, -5547.74, -3844.54, -3275.25, 3760.91, 4208.38 };

    parRdxSrt(&v1, size);  // numParts = default number of threads

    std::vector<double> v2 = { -6121.59, -5547.74, -3844.54, -3275.25, 3760.91, 4208.38 };
    ASSERT_EQ(v1, v2);
}

TEST(Parallel, Test_AlreadySortedBack) {
    const int size = 6;
    std::vector<double> v1 = { 7737.72, 6376.71, 2712.32, -1113.24, -2503.59, -7777.65 };

    parRdxSrt(&v1, size);  // numParts = default number of threads

    std::vector<double> v2 = { -7777.65, -2503.59, -1113.24, 2712.32, 6376.71, 7737.72 };
    ASSERT_EQ(v1, v2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
