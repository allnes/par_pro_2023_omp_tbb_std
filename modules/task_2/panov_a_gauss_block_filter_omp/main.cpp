// Copyright 2023 Panov Alexey
#include <gtest/gtest.h>
#include "./gauss_block_filter_omp.h"

TEST(PanovGaussBlockFilterOMP, WhiteImage) {
    const Image source = generateImage(20, 50);
    const Image result = processImage(source);
    ASSERT_EQ(source, result);
}

TEST(PanovGaussBlockFilterOMP, GreenImage3x3) {
    const Image source = {
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} }
    };
    const Image expectedResult = {
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} },
        { {0, 255, 0}, {0, 255, 0}, {0, 255, 0} }
    };
    const Image result = processImage(source);
    ASSERT_EQ(expectedResult, result);
}

TEST(PanovGaussBlockFilterOMP, RedAndBlueImage2x2) {
    const Image source = {
        { {255, 0, 0}, {0, 0, 255} },
        { {255, 0, 0}, {0, 0, 255} }
    };
    const Image expectedResult = {
        { {191, 0, 63}, {63, 0, 191} },
        { {191, 0, 63}, {63, 0, 191} }
    };
    const Image result = processImage(source);
    ASSERT_EQ(expectedResult, result);
}

TEST(PanovGaussBlockFilterOMP, YellowAndPurpleImage2x3) {
    const Image source = {
        { {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0} },
        { {128, 0, 128}, {128, 0, 128} },
    };
    const Image expectedResult = {
        { {255, 255, 0}, {255, 255, 0} },
        { {223, 191, 32}, {223, 191, 32} },
        { {159, 63, 96}, {159, 63, 96} },
    };
    const Image result = processImage(source);
    ASSERT_EQ(expectedResult, result);
}

TEST(PanovGaussBlockFilterOMP, YellowAndPurpleImage2x4) {
    const Image source = {
        { {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0} },
        { {128, 0, 128}, {128, 0, 128} },
        { {128, 0, 128}, {128, 0, 128} }
    };
    const Image expectedResult = {
        { {255, 255, 0}, {255, 255, 0} },
        { {223, 191, 32}, {223, 191, 32} },
        { {159, 63, 96}, {159, 63, 96} },
        { {128, 0, 128}, {128, 0, 128} },
    };
    const Image result = processImage(source);
    ASSERT_EQ(expectedResult, result);
}
