// Copyright 2023 Kosterin Alexey
#include <gtest/gtest.h>
#include <vector>
#include "./jarvis.h"



TEST(Sequential, Test_Can_Create_Small3_Arr_Points) {
  const int size = 3;
  std::vector<SPoint> arr;
  ASSERT_NO_THROW(arr = CreateArray(size));
}

TEST(Sequential, Test_Can_Create_Big1000_Arr_Points) {
  const int size = 1000;
  std::vector<SPoint> arr;
  ASSERT_NO_THROW(arr = CreateArray(size));
}

TEST(Sequential, Test_Cant_Create_Small2_Arr_Points) {
  const int size = 2;
  std::vector<SPoint> arr;
  ASSERT_ANY_THROW(arr = CreateArray(size));
}

TEST(Sequential, Test_Can_Do_Jarvis_On_Small_Arr5) {
  const int size = 5;
  std::vector<SPoint> arr = CreateArray(size);
  ASSERT_NO_THROW(DoJarvis(arr, size));
}

TEST(Sequential, Test_Can_Do_Jarvis_On_Big_Arr100000) {
  const int size = 100000;
  std::vector<SPoint> arr = CreateArray(size);
  ASSERT_NO_THROW(DoJarvis(arr, size));
}

TEST(Sequential, Test_Jarvis_Do_True_On_Arr5) {
  const int size = 5;
  std::vector<SPoint> arr = CreateArray(size);
  std::vector<SPoint> arrJar = DoJarvis(arr, size);
  ASSERT_EQ(ChekJarvis(arrJar), true);
}

TEST(Sequential, Test_Jarvis_Do_True_On_Arr1000) {
  const int size = 1000;
  std::vector<SPoint> arr = CreateArray(size);
  std::vector<SPoint> arrJar = DoJarvis(arr, size);
  ASSERT_EQ(ChekJarvis(arrJar), true);
}

TEST(Sequential, Test_Jarvis_Do_True_On_Arr100000) {
  const int size = 100000;
  std::vector<SPoint> arr = CreateArray(size);
  std::vector<SPoint> arrJar = DoJarvis(arr, size);
  ASSERT_EQ(ChekJarvis(arrJar), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
