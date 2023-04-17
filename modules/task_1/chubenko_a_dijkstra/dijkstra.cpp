// Copyright 2023 Chubenko Andrey

#include "../../../modules/task_1/chubenko_a_dijkstra/dijkstra.h"

std::vector<int> get_dists_dijkstra(std::vector<int> graph,
                                    int size, int start) {
    std::vector<int> dists(size, INT_MAX);
    std::vector<bool> used(size, false);
    dists[start] = 0;
    for (int i = 0; i < size; i++) {
        int min_dist = INT_MAX;
        int min_vertex = -1;
        for (int j = 0; j < size; j++) {
            if (!used[j] && dists[j] < min_dist) {
                min_dist = dists[j];
                min_vertex = j;
            }
        }
        if (min_dist == INT_MAX) {
            break;
        }
        used[min_vertex] = true;
        for (int j = 0; j < size; j++) {
            if (graph[min_vertex * size + j] != 0) {
                int new_dist = dists[min_vertex] + graph[min_vertex * size + j];
                if (new_dist < dists[j]) {
                    dists[j] = new_dist;
                }
            }
        }
    }
    return dists;
}


