// Copyright 2023 Chubenko Andrey

#ifndef MODULES_TASK_3_CHUBENKO_A_DIJKSTRA_TBB_DIJKSTRA_H_
#define MODULES_TASK_3_CHUBENKO_A_DIJKSTRA_TBB_DIJKSTRA_H_

#include <tbb/tbb.h>
#include <climits>
#include <vector>
#include <iostream>

std::vector<int> get_dists_dijkstra(std::vector<int> graph,
    int size, int start);

std::vector<int> get_dists_dijkstra_parallel(std::vector<int> graph,
    int size, int start);

#endif  // MODULES_TASK_3_CHUBENKO_A_DIJKSTRA_TBB_DIJKSTRA_H_
