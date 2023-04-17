// Copyright 2023 Korobeynikova Alice
#include <gtest/gtest.h>

#include "./histogram_linear_stretching.h"

TEST(Sequential, Test_Image_1) {
  const Image example({255});
  Image image({255});
  linearHistogramStretching(&image);
  ASSERT_EQ(example, image);
}

TEST(Sequential, Test_Image_4) {
  const Image example({255, 0, 84, 122});
  Image image({128, 34, 65, 79});
  linearHistogramStretching(&image);
  ASSERT_EQ(example, image);
}

TEST(Sequential, Test_Image_9) {
  const Image example({214, 255, 145, 200, 170, 2, 242, 0, 214});
  Image image({183, 212, 133, 173, 151, 30, 203, 28, 183});
  linearHistogramStretching(&image);
  ASSERT_EQ(example, image);
}

TEST(Sequential, Test_Image_16) {
  const Image example({198, 0, 202, 82, 153, 150, 53, 159, 210, 85, 244, 255,
                       35, 233, 142, 58});
  Image image({196, 40, 199, 105, 160, 158, 82, 165, 205, 107, 232, 240, 68,
               223, 152, 86});
  linearHistogramStretching(&image);
  ASSERT_EQ(example, image);
}

TEST(Sequential, Test_Image_25) {
  const Image example({12,  210, 166, 32,  215, 152, 20,  161, 253,
                       99,  213, 231, 245, 0,   0,   156, 111, 255,
                       209, 235, 195, 131, 247, 184, 105});
  Image image({15, 202, 160, 34,  207, 147, 22,  156, 243, 97,  205, 222, 235,
               3,  3,   151, 108, 244, 201, 226, 188, 127, 237, 177, 103});
  linearHistogramStretching(&image);
  ASSERT_EQ(example, image);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
