// Copyright 2023 Tychinin Alexey
#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <random>
#include <vector>
#include "shell_sort.h"  // NOLINT

std::vector<double> gen_vector(size_t vec_size) {
    std::random_device rnd_dev;
    std::mt19937 twister{rnd_dev()};
    std::uniform_real_distribution<> dist{};

    std::vector<double> res(vec_size);
    for (double& val : res) {
        val = dist(twister);
    }

    return res;
}

TEST(shell_sort, sort_empty_vector) {
    EXPECT_NO_THROW(task1::shell_sort(std::vector<double>{}));
}

TEST(shell_sort, sort_single_element_vector) {
    std::vector<double> vec{1.};
    EXPECT_EQ(task1::shell_sort(vec), vec);
}

TEST(shell_sort, sort_sorted_vector) {
    std::vector<double> vec{1., 3., 4., 5., 994., 12341.};
    EXPECT_EQ(task1::shell_sort(vec), vec);
}

TEST(shell_sort, sort_descending_vector) {
    std::vector<double> vec{12341, 994., 5., 4., 2., 1.};
    std::vector<double> shell_sorted = task1::shell_sort(vec);
    std::sort(vec.begin(), vec.end());
    EXPECT_EQ(shell_sorted, vec);
}

TEST(shell_sort, sort_random_vec) {
    std::random_device rnd_dev;
    std::mt19937 twister{rnd_dev()};
    std::uniform_int_distribution<> dist{100, 1000};
    auto random_vec = gen_vector(dist(twister));
    std::vector<double> shell_sorted = task1::shell_sort(random_vec);
    std::sort(random_vec.begin(), random_vec.end());
    EXPECT_EQ(shell_sorted, random_vec);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
