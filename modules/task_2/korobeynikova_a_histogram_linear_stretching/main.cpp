// Copyright 2023 Korobeynikova Alice
#include <gtest/gtest.h>

#include "./histogram_linear_stretching.h"

TEST(Parallel_Operations_OpenMP, Test_Image_1) {
  const Image example({255});
  Image seq_image(example), par_image(example);
  sequentialLinearHistogramStretching(&seq_image);
  parallelLinearHistogramStretching(&par_image);
  ASSERT_EQ(seq_image, par_image);
}

TEST(Parallel_Operations_OpenMP, Test_Image_4) {
  const Image example({128, 34, 65, 79});
  Image seq_image(example), par_image(example);
  sequentialLinearHistogramStretching(&seq_image);
  parallelLinearHistogramStretching(&par_image);
  ASSERT_EQ(seq_image, par_image);
}

TEST(Parallel_Operations_OpenMP, Test_Image_9) {
  const Image example({183, 212, 133, 173, 151, 30, 203, 28, 183});
  Image seq_image(example), par_image(example);
  sequentialLinearHistogramStretching(&seq_image);
  parallelLinearHistogramStretching(&par_image);
  ASSERT_EQ(seq_image, par_image);
}

TEST(Parallel_Operations_OpenMP, Test_Image_16) {
  const Image example({196, 40, 199, 105, 160, 158, 82, 165, 205, 107, 232, 240,
                       68, 223, 152, 86});
  Image seq_image(example), par_image(example);
  sequentialLinearHistogramStretching(&seq_image);
  parallelLinearHistogramStretching(&par_image);
  ASSERT_EQ(seq_image, par_image);
}

TEST(Parallel_Operations_OpenMP, Test_Image_25) {
  const Image example({15,  202, 160, 34,  207, 147, 22,  156, 243,
                       97,  205, 222, 235, 3,   3,   151, 108, 244,
                       201, 226, 188, 127, 237, 177, 103});
  Image seq_image(example), par_image(example);
  sequentialLinearHistogramStretching(&seq_image);
  parallelLinearHistogramStretching(&par_image);
  ASSERT_EQ(seq_image, par_image);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
