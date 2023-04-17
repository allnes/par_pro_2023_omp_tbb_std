// Copyright 2023 Maxim Kolesov
#include <gtest/gtest.h>
#include "../../../modules/task_3/kolesov_m_linear_filtering_horizontal/linear_filtering_horizontal.h"

TEST(linear_filtering_horizontal, hexToColorsTest) {
  uint32_t hex = 0xFFAABB;
  uint8_t red, green, blue;

  hexToColors(hex, &red, &green, &blue);

  ASSERT_EQ(red, 0xFF);
  ASSERT_EQ(green, 0xAA);
  ASSERT_EQ(blue, 0xBB);
}

TEST(linear_filtering_horizontal, colorsToHexTest) {
  uint8_t red = 0xAA, green = 0xBB, blue = 0xCC;
  uint32_t result = colorsToHex(red, green, blue);

  ASSERT_EQ(result, 0xAABBCC);
}

TEST(linear_filtering_horizontal, process3x3) {
  std::vector<uint32_t> image = {0xFFFFFF, 0xFF0000, 0x0000FF,
                                 0xFFFFFF, 0xFF00FF, 0x000000,
                                 0xFFFFFF, 0xFF0000, 0x000000};

  std::vector<uint32_t> result = {0xFFFFFF, 0xFFFFFF, 0xFF00FF,
                                  0xFFFFFF, 0xFFFFFF, 0xFF00FF,
                                  0xFFFFFF, 0xFFFFFF, 0xFF0055};

  auto seqResult = process(image, 3, 3);
  auto parallelResult = processParallel(image, 3, 3);

  ASSERT_EQ(seqResult, parallelResult);
}

TEST(linear_filtering_horizontal, process5x5) {
  std::vector<uint32_t> image = {0x2110e, 0x3b728d, 0xa84e98, 0x5aa186, 0x7a991b,
                                 0x216b19, 0x394b85, 0x6b5a92, 0x99f74, 0x2eaa2,
                                 0x10558, 0x4891a5, 0x55f73, 0x439394, 0x496384,
                                 0x6456f, 0xa73e10, 0x82296b, 0x955d60, 0x89b94,
                                 0x811c40, 0x898e51, 0x46460, 0xa2274a, 0x8c712d};
  std::vector<uint32_t> result = {0xe3ffe6, 0xe8faff, 0xffffff, 0xffffff, 0xffffff,
                                  0x8cffff, 0xa8f2ff, 0xd3ffff, 0xd6ffff, 0xbaffff,
                                  0x8bffff, 0xc0e5ff, 0xfeffff, 0xb7ffff, 0x82ffff,
                                  0xf4ffff, 0xd9e5ff, 0xffffff, 0xf6ffff, 0xffffff,
                                  0xffffda, 0xffedee, 0xfffcf0, 0xffffff, 0xfffff0};

  auto seqResult = process(image, 5, 5);
  auto parallelResult = processParallel(image, 5, 5);

  ASSERT_EQ(seqResult, parallelResult);
}

TEST(linear_filtering_horizontal, process6x6) {
  std::vector<uint32_t> image = {0x4d772e, 0x9251f, 0x4a2b1c, 0x4e7339, 0x4579, 0x9516b,
                                 0x645e54, 0x756c2e, 0x164258, 0x605771, 0x122c68, 0x382d15,
                                 0x577738, 0x6b4e2b, 0x2d4ab, 0x365354, 0x223732, 0x76341f,
                                 0x244a61, 0x42b41, 0x6d3565, 0x556d1b, 0x624c1a, 0x233f60,
                                 0x4e6432, 0x51235, 0x2e3d3c, 0x603b71, 0x7603b, 0x695c66,
                                 0x2a5223, 0x172f10, 0x321a5c, 0x45351c, 0x2d30, 0x605523 };
  std::vector<uint32_t> result = {0xb0e88c, 0xabcf9b, 0xb3c2a6, 0x87b6e2, 0x8cd0d3, 0x71c1c7,
                                  0xe2f49b, 0xc6ffc5, 0xbaffdc, 0x7effff, 0x9ad2e5, 0x8baec5,
                                  0xdce1b3, 0xc2fffa, 0xc6fff6, 0xacfffe, 0xc6ccb8, 0xbda59e,
                                  0xbfd5c5, 0x9efce8, 0xa9eeef, 0xb1ffe6, 0xd2e4c4, 0xdad5c5,
                                  0x8dc9b7, 0x83a8bd, 0xa29cb9, 0xbac0b8, 0xc5e2b2, 0xc0e8c7,
                                  0xaad47d, 0x77a395, 0x8f82a6, 0x819abd, 0xb3cca5, 0xc8eca6};

  auto seqResult = process(image, 6, 6);
  auto parallelResult = processParallel(image, 6, 6);

  ASSERT_EQ(seqResult, parallelResult);
}
