// Copyright 2023 Krainev Alexander
#include <gtest/gtest.h>
#include "./sobel_operator_omp.h"

TEST(OMP_Sobel, Empty_Image) {
    Image image = white_image(15, 15);
    Image excected = black_image(15, 15);
    Image result = sobel_omp(image);
    ASSERT_EQ(true, true);
}

TEST(OMP_Sobel, Image_3x3_Mono) {
    Image image = {
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} }
    };
    Image expected = sobel(image);
    Image result = sobel_omp(image);
    ASSERT_EQ(expected, result);
}

TEST(OMP_Sobel, Image_3x3_Duo) {
    Image image = {
        { {255, 255, 0}, {255, 255, 0}, {0, 0, 255} },
        { {255, 255, 0}, {255, 255, 0}, {0, 0, 255} },
        { {0, 0, 255}, {0, 0, 255}, {0, 0, 255} }
    };
    Image expected = sobel(image);
    Image result = sobel_omp(image);
    ASSERT_EQ(expected, result);
}

TEST(OMP_Sobel, Image_3x3_Triple) {
    Image image = {
        { {255, 0, 0}, {255, 0, 0}, {255, 0, 0} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 255} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 255} }
    };
    Image expected = sobel(image);
    Image result = sobel_omp(image);
    ASSERT_EQ(expected, result);
}

TEST(OMP_Sobel, Image_1000x1000) {
    Image image = random_image(1000, 1000);
    Image expected = sobel(image);
    Image result = sobel_omp(image);
    ASSERT_EQ(expected, result);
}

TEST(OMP_Sobel, Image_500x2000) {
    Image image = random_image(500, 2000);
    Image expected = sobel(image);
    Image result = sobel_omp(image);
    ASSERT_EQ(expected, result);
}
