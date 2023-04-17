// Copyright 2023 Chubenko Andrey
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/chubenko_a_dijkstra/dijkstra.h"

TEST(Dijkstra_Sequential, Test_Count_5) {
    const int size = 5;
    std::vector<int> graph = {0, 6, 7, 0, 0,
                              6, 0, 6, 1, 0,
                              7, 6, 0, 0, 1,
                              0, 1, 0, 0, 8,
                              0, 0, 1, 8, 0
                             };
    const std::vector<int> expected = {0, 6, 7, 7, 8};
    std::vector<int> dists = get_dists_dijkstra(graph, size, 0);

    ASSERT_EQ(dists, expected);
}

TEST(Dijkstra_Sequential, Test_Count_10_1) {
    const int size = 10;
    std::vector<int> graph = {0, 6, 1, 7, 4, 10, 7, 10, 10, 0,
                            6, 0, 0, 1, 0, 10, 9, 5, 5, 0,
                            1, 0, 0, 0, 7, 10, 2, 1, 3, 8,
                            7, 1, 0, 0, 0, 2, 0, 7, 4, 0,
                            4, 0, 7, 0, 0, 3, 0, 9, 7, 1,
                            10, 10, 10, 2, 3, 0, 0, 0, 1, 1,
                            7, 9, 2, 0, 0, 0, 0, 1, 0, 0,
                            10, 5, 1, 7, 9, 0, 1, 0, 10, 0,
                            10, 5, 3, 4, 7, 1, 0, 10, 0, 0,
                            0, 0, 8, 0, 1, 1, 0, 0, 0, 0
                            };

    const std::vector<int> expected = {0, 6, 1, 7, 4, 5, 3, 2, 4, 5};
    std::vector<int> dists = get_dists_dijkstra(graph, size, 0);

    ASSERT_EQ(dists, expected);
}

TEST(Dijkstra_Sequential, Test_Count_10_2) {
    const int size = 10;
    std::vector<int> graph = {0, 1, 2, 1, 9, 0, 8, 0, 6, 0,
                            1, 0, 4, 8, 0, 0, 0, 0, 1, 9,
                            2, 4, 0, 10, 1, 9, 5, 0, 3, 0,
                            1, 8, 10, 0, 5, 0, 7, 9, 0, 3,
                            9, 0, 1, 5, 0, 7, 10, 1, 8, 10,
                            0, 0, 9, 0, 7, 0, 0, 1, 3, 1,
                            8, 0, 5, 7, 10, 0, 0, 1, 0, 4,
                            0, 0, 0, 9, 1, 1, 1, 0, 0, 7,
                            6, 1, 3, 0, 8, 3, 0, 0, 0, 0,
                            0, 9, 0, 3, 10, 1, 4, 7, 0, 0,
                            };


    const std::vector<int> expected = {5, 4, 3, 4, 2, 0, 2, 1, 3, 1};
    std::vector<int> dists = get_dists_dijkstra(graph, size, 5);

    ASSERT_EQ(dists, expected);
}

TEST(Dijkstra_Sequential, Test_Count_2) {
    const int size = 2;
    std::vector<int> graph = {0, 1,
                              1, 0 };


    const std::vector<int> expected = {0, 1};
    std::vector<int> dists = get_dists_dijkstra(graph, size, 0);

    ASSERT_EQ(dists, expected);
}

TEST(Dijkstra_Sequential, Test_Count_7_Full) {
    const int size = 7;
    std::vector<int> graph = {0, 8, 1, 0, 1, 2, 0,
                             8, 0, 1, 4, 7, 4, 6,
                             1, 1, 0, 5, 4, 1, 0,
                             0, 4, 5, 0, 3, 8, 7,
                             1, 7, 4, 3, 0, 4, 9,
                             2, 4, 1, 8, 4, 0, 1,
                             0, 6, 0, 7, 9, 1, 0,
                             };

    const std::vector<int> expected = {0, 2, 1, 4, 1, 2, 3};
    std::vector<int> dists = get_dists_dijkstra(graph, size, 0);

    ASSERT_EQ(dists, expected);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
