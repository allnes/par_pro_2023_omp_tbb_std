// Copyright 2023 Goncharova Anna

#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include "../../../modules/task_2/goncharova_a_sobel_omp/goncharova_a_sobel_omp.h"
#include "gtest/gtest.h"

TEST(sobel, uncorrect_width) { ASSERT_ANY_THROW(getRandomMatrix(0, 1));
}

TEST(sobel, uncorrect_height) { ASSERT_ANY_THROW(getRandomMatrix(1, 0));
}

TEST(sobel, uncorrect_size_1) { ASSERT_ANY_THROW(getRandomMatrix(0, 0));
}

TEST(sobel, correct_size_2) { ASSERT_NO_THROW(getRandomMatrix(1, 1));
}

TEST(sobel, equality_width) { image Ex1(16, 16); ASSERT_EQ(Ex1.width, 16);
}

TEST(sobel, equality_height) { image Ex1(16, 16); ASSERT_EQ(Ex1.height, 16);
}
