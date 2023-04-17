// Copyright 2023 Kandrin Alexey
#include <gtest/gtest.h>

#include "./component_marking.h"

namespace {
template <class T>
Matrix<T> TwoDimensionalVectorToMatrix(
    std::initializer_list<std::initializer_list<T>> initializerList) {
  std::vector<std::vector<T>> vec(initializerList.begin(),
                                  initializerList.end());
  Matrix<T> result(vec.size(), vec[0].size());
  for (size_t i = 0; i < result.GetRowCount(); ++i) {
    for (size_t j = 0; j < result.GetColCount(); ++j) {
      result[i][j] = vec.at(i).at(j);
    }
  }
  return result;
}
}  // namespace

TEST(Sequential, WhiteImage) {
  // 1 is the black area(object)
  // 0 is the white area(background)
  BinaryImage image(5, 5, 1);
  LabelImage expectedLabelImage =
      TwoDimensionalVectorToMatrix<Label>({{1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1}});
  LabelImage labelImage =
      GetComponentMarking<ExecutionPolicy::Sequential>(image);
  ASSERT_EQ(labelImage, expectedLabelImage);
}

TEST(Sequential, BlackImage) {
  BinaryImage image(5, 5, 0);
  LabelImage expectedLabelImage =
      TwoDimensionalVectorToMatrix<Label>({{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0}});
  LabelImage labelImage =
      GetComponentMarking<ExecutionPolicy::Sequential>(image);
  ASSERT_EQ(labelImage, expectedLabelImage);
}
TEST(Sequential, ChessImage) {
  // 1 is the black area(object)
  // 0 is the white area(background)
  BinaryImage image =
      TwoDimensionalVectorToMatrix<BinaryPixel>({{1, 0, 1, 0, 1},
                                                 {0, 1, 0, 1, 0},
                                                 {1, 0, 1, 0, 1},
                                                 {0, 1, 0, 1, 0},
                                                 {1, 0, 1, 0, 1}});
  LabelImage expectedLabelImage =
      TwoDimensionalVectorToMatrix<Label>({{1, 0, 2, 0, 3},
                                           {0, 4, 0, 5, 0},
                                           {6, 0, 7, 0, 8},
                                           {0, 9, 0, 10, 0},
                                           {11, 0, 12, 0, 13}});
  LabelImage labelImage =
      GetComponentMarking<ExecutionPolicy::Sequential>(image);
  ASSERT_EQ(labelImage, expectedLabelImage);
}

TEST(Sequential, TwoTrianglesImage) {
  // 1 is the black area(object)
  // 0 is the white area(background)
  BinaryImage image =
      TwoDimensionalVectorToMatrix<BinaryPixel>({{1, 1, 1, 0, 0},
                                                 {1, 1, 0, 0, 0},
                                                 {1, 0, 0, 0, 1},
                                                 {0, 0, 0, 1, 1},
                                                 {0, 0, 1, 1, 1}});
  LabelImage expectedLabelImage =
      TwoDimensionalVectorToMatrix<Label>({{1, 1, 1, 0, 0},
                                           {1, 1, 0, 0, 0},
                                           {1, 0, 0, 0, 2},
                                           {0, 0, 0, 2, 2},
                                           {0, 0, 2, 2, 2}});
  LabelImage labelImage =
      GetComponentMarking<ExecutionPolicy::Sequential>(image);
  ASSERT_EQ(labelImage, expectedLabelImage);
}

TEST(Sequential, UnionImage) {
  // 1 is the black area(object)
  // 0 is the white area(background)
  BinaryImage image =
      TwoDimensionalVectorToMatrix<BinaryPixel>({{1, 0, 1, 0, 1},
                                                 {1, 0, 1, 0, 0},
                                                 {1, 0, 1, 0, 1},
                                                 {1, 0, 1, 0, 0},
                                                 {1, 1, 1, 0, 1}});
  LabelImage expectedLabelImage =
      TwoDimensionalVectorToMatrix<Label>({{1, 0, 1, 0, 2},
                                           {1, 0, 1, 0, 0},
                                           {1, 0, 1, 0, 3},
                                           {1, 0, 1, 0, 0},
                                           {1, 1, 1, 0, 4}});
  LabelImage labelImage =
      GetComponentMarking<ExecutionPolicy::Sequential>(image);
  ASSERT_EQ(labelImage, expectedLabelImage);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
