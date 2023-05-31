// Copyright 2023 Gosteeva Ekaterina
#include "../../../modules/task_4/gosteeva_e_dijkstra_std/dijkstra.h"
#include "../../../3rdparty/unapproved/unapproved.h"

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

std::vector<int> DijkstraParallel(std::vector<int> graph, int source, int size) {
    std::vector<int> dist(size, INT_MAX);
    std::vector<bool> visited(size, false);
    dist[source] = 0;

    auto processNode = [&](int start, int end) {
        for (int i = start; i < end; i++) {
            int min = INT_MAX;
            int index = -1;
            for (int j = 0; j < size; j++) {
                if (!visited[j] && dist[j] <= min) {
                    min = dist[j];
                    index = j;
                }
            }
            if (index == -1)
                break;
            visited[index] = true;
            for (int j = 0; j < size; j++) {
                if (!visited[j] && graph[index * size + j] && dist[index] != INT_MAX
                    && dist[index] + graph[index * size + j] < dist[j]) {
                    dist[j] = dist[index] + graph[index * size + j];
                }
            }
        }
    };

    int numThreads = 1;
    std::vector<std::thread> threads(numThreads);
    int chunkSize = size / numThreads;
    int remainder = size % numThreads;
    int start = 0;
    int end = chunkSize;

    for (int i = 0; i < numThreads; i++) {
        if (i == numThreads - 1) {
            end += remainder;
        }

        threads[i] = std::thread(processNode, start, end);
        start = end;
        end += chunkSize;
    }

    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    return dist;
}
