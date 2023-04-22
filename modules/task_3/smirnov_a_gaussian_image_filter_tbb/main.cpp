// Copyright 2023 Smirnov Andrew
#include <gtest/gtest.h>
#include "../../../modules/task_3/smirnov_a_gaussian_image_filter_tbb/gaussian_image_filter_tbb.h"

TEST(TBB_parallel, No_throw_when_empty_image) {
  const int countRows = 0;
  const int countColumns = 0;
  auto image = genImage(countRows, countColumns);
  ASSERT_NO_THROW(gaussianFilterTBBParallel(image, countRows, countColumns));
}

TEST(TBB_parallel, Invalid_count_rows_or_columns) {
  const int countRows = 5;
  const int countColumns = 5;
  vector<intensityType> image = { 54, 251, 169, 80, 159, 95, 251, 220, 90 };
  ASSERT_ANY_THROW(gaussianFilterTBBParallel(image, countRows, countColumns));
}

TEST(TBB_parallel, Works_with_3x3_image) {
  const int countRows = 3;
  const int countColumns = 3;
  vector<intensityType> image = { 54, 251, 169, 80, 159, 95, 251, 220, 90 };
  vector<intensityType> referenceValue = { 102, 166, 169, 136, 155, 133, 207, 177, 119 };
  vector<intensityType> result = gaussianFilterTBBParallel(image, countRows, countColumns);
  ASSERT_EQ(result, referenceValue);
}

TEST(TBB_parallel, Works_with_4x3_image) {
  const int countRows = 4;
  const int countColumns = 3;
  vector<intensityType> image = { 93, 51, 79, 119, 150, 31, 33, 244, 34, 28, 109, 150 };
  vector<intensityType> referenceValue = { 93, 79, 69, 105, 108, 70, 86, 122, 93, 57, 108, 126 };
  vector<intensityType> result = gaussianFilterTBBParallel(image, countRows, countColumns);
  ASSERT_EQ(result, referenceValue);
}

TEST(TBB_parallel, Works_with_full_black_image) {
  const int countRows = 3;
  const int countColumns = 3;
  vector<intensityType> image = { 255, 255, 255, 255, 255, 255, 255, 255, 255 };
  vector<intensityType> referenceValue = { 255, 255, 255, 255, 255, 255, 255, 255, 255 };
  vector<intensityType> result = gaussianFilterTBBParallel(image, countRows, countColumns);
  ASSERT_EQ(result, referenceValue);
}

TEST(TBB_parallel, Works_with_full_white_image) {
  const int countRows = 3;
  const int countColumns = 3;
  vector<intensityType> image = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  vector<intensityType> referenceValue = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  vector<intensityType> result = gaussianFilterTBBParallel(image, countRows, countColumns);
  ASSERT_EQ(result, referenceValue);
}

TEST(TBB_parallel, Can_calculate_150x177_image) {
  const int countRows = 150;
  const int countColumns = 177;
  vector<intensityType> image = genImage(countRows, countColumns);
  ASSERT_NO_THROW(gaussianFilterTBBParallel(image, countRows, countColumns));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
