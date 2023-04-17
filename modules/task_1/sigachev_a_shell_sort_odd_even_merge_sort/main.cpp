// Copyright 2023 Sigachev Anton
#include <gtest/gtest.h>
#include "./sort.h"

bool test(unsigned size) {
    std::vector<int> vec = getRandomVector(size);
    ShellSort(&vec);
    return checkSort(vec);
}

TEST(ShellSort, test_size_101) {
    ASSERT_TRUE(test(101));
}

TEST(ShellSort, test_size_1503) {
    ASSERT_TRUE(test(1503));
}

TEST(ShellSort, test_size_10021) {
    ASSERT_TRUE(test(10021));
}

TEST(ShellSort, test_size_32322) {
    ASSERT_TRUE(test(32322));
}

TEST(ShellSort, test_size_132322) {
    ASSERT_TRUE(test(132322));
}
