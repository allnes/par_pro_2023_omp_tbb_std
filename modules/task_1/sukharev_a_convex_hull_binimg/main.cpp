// Copyright 2023 Sukharev Artem
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/sukharev_a_convex_hull_binimg/sukharev_a_convex_hull_binimg.h"

TEST(Parallel_Operations_OpenMP, Test_Full_Square) {
    std::vector<std::vector<int>> g = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
    std::vector<std::vector<int>> expRes = {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Empty_Img) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}


TEST(Parallel_Operations_OpenMP, Test_One_Line_Component) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Comp_In_Corners) {
    std::vector<std::vector<int>> g = {
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 1, 1}
    };
    std::vector<std::vector<int>> expRes = {
        {1, 1, 0, 0, 0, 0, 0, 2},
        {1, 0, 1, 0, 0, 0, 2, 0},
        {0, 0, 1, 0, 0, 0, 2, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 4, 0},
        {3, 0, 0, 3, 0, 4, 0, 4}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Some_Diffrent_Components) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 2, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 3, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Nested_Components) {
    std::vector<std::vector<int>> g = {
        {0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 2, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
