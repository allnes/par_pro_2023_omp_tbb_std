// Copyright 2023 Lebedinskiy Ilya
#include "gtest/gtest.h"
#include "../../../modules/task_1/lebedinskiy_i_grackham/grackham.h"

TEST(grackham_seq, test_size_50) {
    std::vector<std::pair<int, int>> dots;
    int size = 50;
    dots = gen_dots(size);
    std::vector<std::pair<int, int>> seq_res;
    seq_res = greckham_seq(dots);
    ASSERT_EQ(seq_res, seq_res);
}

TEST(grackham_seq, test_size_100) {
    int size = 100;
    std::vector<std::pair<int, int>> dots;
    dots = gen_dots(size);
    std::vector<std::pair<int, int>> seq_res;
    seq_res = greckham_seq(dots);
    ASSERT_EQ(seq_res, seq_res);
}

TEST(grackham_seq, test_size_500) {
    std::vector<std::pair<int, int>> dots;
    int size = 500;
    dots = gen_dots(size);
    std::vector<std::pair<int, int>> seq_res;
    seq_res = greckham_seq(dots);
    ASSERT_EQ(seq_res, seq_res);
}

TEST(grackham_seq, test_size_8) {
    std::vector<std::pair<int, int>> dots = {
        { 0, 3 }, { 1, 1 },
        { 2, 2 }, { 4, 4 },
        { 0, 0 }, { 1, 2 },
        { 3, 1 }, { 3, 3 }
    };
    std::vector<std::pair<int, int>> seq_res;
    std::vector<std::pair<int, int>> expected = {
        { 0, 0 }, { 3, 1 }, { 4, 4 }, { 0, 3 }
    };
    seq_res = greckham_seq(dots);
    ASSERT_EQ(seq_res, expected);
}

TEST(grackham_seq, test_size_3000) {
    std::vector<std::pair<int, int>> dots;
    int size = 3000;
    dots = gen_dots(size);
    std::vector<std::pair<int, int>> seq_res;
    seq_res = greckham_seq(dots);
    ASSERT_EQ(seq_res, seq_res);
}
