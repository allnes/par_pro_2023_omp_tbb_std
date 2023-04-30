// Copyright 2023 Gosteeva Ekaterina

#include "../../../modules/task_2/gosteeva_e_dijkstra_omp/dijkstra.h"

std::vector<int> DijkstraSeq(std::vector<int> graph, int source, int size) {
    std::vector<int> dist(size);
    std::vector<bool> visited(size);
    int min = INT_MAX, index;
    for (int i = 0; i < size; i++) {
        dist.at(i) = INT_MAX;
        visited.at(i) = false;
    }
    dist.at(source) = 0;
    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (visited.at(i) == false && dist.at(i) <= min) {
                min = dist.at(i);
                index = i;
            }
        }
        visited.at(index) = true;
        for (int i = 0; i < size; i++) {
            if (!visited.at(i) && graph.at(index * size + i) && dist.at(index) != INT_MAX
            && dist.at(index) + graph.at(index * size + i) < dist.at(i)) {
                dist.at(i) = dist.at(index) + graph.at(index * size + i);
            }
        }
    }
    return dist;
}

std::vector<int> DijkstraParallel(std::vector<int> graph,
    int source, int size) {

    std::vector<int> dist(size);
    std::vector<int> visited(size);
    int min = INT_MAX, index;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        dist.at(i) = INT_MAX;
        visited.at(i) = false;
    }

    dist.at(source) = 0;

    for (int i = 0; i < size; i++) {
        min = INT_MAX;

        #pragma omp parallel for
        for (int j = 0; j < size; j++) {
            if (visited.at(j) == false && dist.at(j) <= min) {
                #pragma omp critical
                if (dist.at(j) <= min) {
                    min = dist.at(j);
                    index = j;
                }
            }
        }

        visited.at(index) = true;

        #pragma omp parallel for
        for (int k = 0; k < size; k++) {
            if (!visited.at(k) && graph.at(index * size + k) && dist.at(index) != INT_MAX
                && dist.at(index) + graph.at(index * size + k) < dist.at(k)) {
                #pragma omp critical
                if (dist.at(index) + graph.at(index * size + k) < dist.at(k)) {
                    dist.at(k) = dist.at(index) + graph.at(index * size + k);
                }
            }
        }
    }
    return dist;
}
