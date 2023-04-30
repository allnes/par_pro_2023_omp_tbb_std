// Copyright 2023 Gosteeva Ekaterina
#include <gtest/gtest.h>
#include "../../../modules/task_2/gosteeva_e_dijkstra_omp/dijkstra.h"

TEST(Dijkstra, Test1) {
    std::vector<int> graph = {
        0, 10, 20, 0, 0, 0,
        10, 0, 0, 50, 10, 0,
        20, 0, 0, 20, 33, 0,
        0, 50, 20, 0, 20, 2,
        0, 10, 33, 20, 0, 1,
        0, 0, 0, 2, 1, 0 };
    std::vector<int> resSeq = DijkstraSeq(graph, 0, 6);
    std::vector<int> resParallel = DijkstraParallel(graph, 0, 6);
    ASSERT_EQ(resSeq, resParallel);
}

TEST(Dijkstra, Test2) {
    std::vector<int> graph = {
        0, 7, 9, 0, 0, 14,
        7, 0, 10, 15, 0, 0,
        9, 10, 0, 11, 0, 2,
        0, 15, 11, 0, 6, 0,
        0, 0, 0, 6, 0, 9,
        14, 0, 2, 0, 9, 0 };
    std::vector<int> resSeq = DijkstraSeq(graph, 0, 6);
    std::vector<int> resParallel = DijkstraParallel(graph, 0, 6);
    ASSERT_EQ(resSeq, resParallel);
}

TEST(Dijkstra, Test3) {
    std::vector<int> graph = {
        0, 1, 1, 40, 0, 0,
        1, 0, 30, 70, 0, 0,
        1, 30, 0, 50, 3, 20,
        40, 70, 50, 0, 15, 5,
        0, 0, 3, 15, 0, 2,
        0, 0, 20, 5, 2, 0 };
    std::vector<int> resSeq = DijkstraSeq(graph, 0, 6);
    std::vector<int> resParallel = DijkstraParallel(graph, 0, 6);
    ASSERT_EQ(resSeq, resParallel);
}

TEST(Dijkstra, Test4) {
    std::vector<int> graph = {
        0, 5, 0, 6, 0, 0, 0,
        5, 0, 10, 5, 4, 0, 0,
        0, 10, 0, 11, 0, 0, 0,
        6, 5, 11, 0, 5, 4, 6,
        0, 4, 0, 5, 0, 8, 9,
        0, 0, 0, 4, 8, 0, 7,
        0, 0, 0, 6, 9, 7, 0 };
    std::vector<int> resSeq = DijkstraSeq(graph, 0, 7);
    std::vector<int> resParallel = DijkstraParallel(graph, 0, 7);
    ASSERT_EQ(resSeq, resParallel);
}

TEST(Dijkstra, Test5) {
    std::vector<int> graph = {
        0, 4, 0, 0, 0, 0, 0, 8, 0,
        4, 0, 8, 0, 0, 0, 0, 11, 0,
        0, 8, 0, 7, 0, 0, 0, 0, 2,
        0, 0, 7, 0, 9, 14, 0, 0, 0,
        0, 0, 0, 9, 0, 10, 0, 0, 0,
        0, 0, 0, 14, 10, 0, 2, 0, 0,
        0, 0, 0, 0, 0, 2, 0, 1, 6,
        8, 11, 0, 0, 0, 0, 1, 0, 7,
        0, 0, 2, 0, 0, 0, 6, 7, 0 };
    std::vector<int> resSeq = DijkstraSeq(graph, 0, 9);
    std::vector<int> resParallel = DijkstraParallel(graph, 0, 9);
    ASSERT_EQ(resSeq, resParallel);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
