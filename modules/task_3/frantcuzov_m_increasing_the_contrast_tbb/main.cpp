// Copyright 2023 Frantcuzov Maksim
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <vector>

#include "./increasing_the_contrast_tbb.h"

TEST(TBB_TEST, TestGetParallelOperations_3x3) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 3;
  int height = 3;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_128x128) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 128;
  int height = 128;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_256x256) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 256;
  int height = 256;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_512x512) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 512;
  int height = 512;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_1024x1024) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1024;
  int height = 1024;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_1920x1080) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1920;
  int height = 1080;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
