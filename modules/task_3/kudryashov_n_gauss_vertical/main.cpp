  // Copyright 2023 Kudryashov Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./kudryashov_n_gauss_vertical.h"

TEST(gauss_vertical, test_image_3x3) {
    int height = 3;
    int width = 3;
    std::vector<std::vector<int>> img = { {123, 226, 1},
                                          {181, 143, 223},
                                          {243, 83, 196} };

    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);

    std::vector<std::vector<int>> resultImgParallel = gauss_filter_parallel(
        img, height, width);

    ASSERT_EQ(resultImgParallel, resultImg);
}

TEST(gauss_vertical, test_image_4x4) {
    int height = 4;
    int width = 4;
    std::vector<std::vector<int>> img = { {234, 125, 174, 146},
                                          {238, 146, 158, 138},
                                          {220, 225, 92, 132},
                                          {135, 161, 37, 233} };

    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);

    std::vector<std::vector<int>> resultImgParallel = gauss_filter_parallel(
        img, height, width);

    ASSERT_EQ(resultImgParallel, resultImg);
}

TEST(gauss_vertical, test_image_5x5) {
    int height = 5;
    int width = 5;
    std::vector<std::vector<int>> img = { {203, 78, 115, 27, 90},
                                          {7, 206, 96, 22, 169},
                                          {28, 141, 106, 21, 255},
                                          {202, 197, 97, 250, 168},
                                          {161, 108, 118, 90, 190} };

    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);

    std::vector<std::vector<int>> resultImgParallel = gauss_filter_parallel(
        img, height, width);

    ASSERT_EQ(resultImgParallel, resultImg);
}

TEST(gauss_vertical, test_image_6x4) {
    int height = 6;
    int width = 4;
    std::vector<std::vector<int>> img = { {142, 202, 45, 115},
                                          {1, 47, 224, 162},
                                          {87, 37, 4, 253},
                                          {95, 92, 29, 67},
                                          {186, 241, 52, 83},
                                          {13, 67, 115, 123} };

    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);

    std::vector<std::vector<int>> resultImgParallel = gauss_filter_parallel(
        img, height, width);

    ASSERT_EQ(resultImgParallel, resultImg);
}

TEST(gauss_vertical, test_image_4x6) {
    int height = 4;
    int width = 6;
    std::vector<std::vector<int>> img = { {183, 16, 27, 224, 130, 217},
                                          {227, 108, 222, 164, 102, 143},
                                          {103, 125, 90, 198, 0, 49},
                                          {23, 254, 17, 221, 150, 84} };

    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);

    std::vector<std::vector<int>> resultImgParallel = gauss_filter_parallel(
        img, height, width);

    ASSERT_EQ(resultImgParallel, resultImg);
}
