// Copyright 2023 Gosteeva Ekaterina
#ifndef MODULES_TASK_2_GOSTEEVA_E_DIJKSTRA_DIJKSTRA_H_
#define MODULES_TASK_2_GOSTEEVA_E_DIJKSTRA_DIJKSTRA_H_

#include <omp.h>
#include <climits>
#include <vector>

std::vector<int> DijkstraSeq(std::vector<int> graph, 
    int source, int size);
std::vector<int> DijkstraParallel(std::vector<int> graph, 
    int source, int size);
    
#endif  // MODULES_TASK_2_GOSTEEVA_E_DIJKSTRA_DIJKSTRA_H_
