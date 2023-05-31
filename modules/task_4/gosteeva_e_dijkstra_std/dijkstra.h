// Copyright 2023 Gosteeva Ekaterina
#ifndef MODULES_TASK_4_GOSTEEVA_E_DIJKSTRA_STD_DIJKSTRA_H_
#define MODULES_TASK_4_GOSTEEVA_E_DIJKSTRA_STD_DIJKSTRA_H_

#include <vector>
#include <queue>
#include <random>
#include <climits>
#include <utility>

std::vector<int> DijkstraSeq(std::vector<int> graph,
    int source, int size);
std::vector<int> DijkstraParallel(std::vector<int> graph,
    int source, int size);
#endif  // MODULES_TASK_4_GOSTEEVA_E_DIJKSTRA_STD_DIJKSTRA_H_
