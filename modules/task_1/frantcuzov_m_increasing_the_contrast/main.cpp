// Copyright 2023 Frantcuzov Maksim
#include <gtest/gtest.h>

#include <vector>

#include "./increasing_the_contrast.h"

TEST(TestForFunctions, TestGetGaussKernel) {
  std::vector<float> res = getGaussKernel(1, 1.5);

  ASSERT_NEAR(res[4], 0.147761, 0.001);
}

TEST(TestForFunctions, TestCalcNewPixColor_0_0) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  std::vector<float> img{0, 128, 255, 0, 128, 255, 0, 128, 255};
  float color = calcNewPixColor(0, 0, 3, 3, kernel, 1, img);


  ASSERT_NEAR(color, 27.2716, 0.001);
}

TEST(TestForFunctions, TestCalcNewPixColor_0_1) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  std::vector<float> img{0, 128, 255, 0, 128, 255, 0, 128, 255};
  float color = calcNewPixColor(0, 1, 3, 3, kernel, 1, img);

  ASSERT_NEAR(color, 39.3986, 0.001);
}

TEST(TestForFunctions, TestCalcNewPixColor_center) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  std::vector<float> img{0, 128, 255, 0, 128, 255, 0, 128, 255};
  float color = calcNewPixColor(1, 1, 3, 3, kernel, 1, img);

  ASSERT_NEAR(color, 127.692, 0.001);
}

TEST(TestForFunctions, TestCalcNewPixColor_width_height) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  std::vector<float> img{0, 128, 255, 0, 128, 255, 0, 128, 255};
  float color = calcNewPixColor(2, 2, 3, 3, kernel, 1, img);

  ASSERT_NEAR(color, 95.1219, 0.001);
}

TEST(TestForFunctions, TestGetSequentialOperations) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  std::vector<float> img{0, 128, 255, 0, 128, 255, 0, 128, 255};

  std::vector<float> res = getSequentialOperations(3, 3, kernel, img);
  std::vector<float> res_check{27.2716, 88.3884, 95.1219, 39.3986, 127.692,
                               137.42,  27.2716, 88.3884, 95.1219};

  for (int i = 0; i < 9; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}
