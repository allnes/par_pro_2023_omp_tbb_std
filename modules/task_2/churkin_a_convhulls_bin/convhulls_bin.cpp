// Copyright 2023 Churkin Aleksandr
#include <omp.h>
#include <vector>
#include <utility>
#include <random>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include "../../../modules/task_2/churkin_a_convhulls_bin/convhulls_bin.h"

// 1. Generates random binary image with height M and width N
std::vector<int> GetRandomBinImage(int M, int N) {
    std::default_random_engine rnd;
    std::uniform_int_distribution<> dist(1, 10);

    std::vector<int> image(M * N);

    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++) {
            int number = dist(rnd);
            if (number <= 4) {
                image[i * N + j] = 1;
            } else {
                image[i * N + j] = 0;
            }
        }

    return image;
}

void PrintImage(int* image, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) std::cout << image[i * N + j] << " ";
        std::cout << '\n';
    }
}

bool isCoordinatesInImage(int x, int y, int M, int N) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

double rotate(const std::pair<int, int>& p1,
              const std::pair<int, int>& p2,
              const std::pair<int, int>& p3) {
    return (p2.first - p1.first) * (p3.second - p2.second) -
           (p2.second - p1.second) * (p3.first - p2.first);
}

Points GrahamScan(Points* points) {
    if ((*points).size() <= 2) return (*points);

    Points result;

    // Finding minimal point - point with minimum x and y (left bottom point)
    std::pair<int, int> minPoint = (*points)[0];
    int minPointIdx = 0;

    for (size_t i = 1; i < (*points).size(); i++) {
        if ((*points)[i].first < minPoint.first ||
            ((*points)[i].first == minPoint.first &&
             (*points)[i].second < minPoint.second)) {
            minPoint = (*points)[i];
            minPointIdx = i;
        }
    }

    // Removing minimal point from our points
    std::swap((*points)[minPointIdx], (*points)[(*points).size() - 1]);
    (*points).pop_back();

    // Sorting points by our custom criteria
    std::sort((*points).begin(), (*points).end(),
              [minPoint](const std::pair<int, int>& p1,
                         const std::pair<int, int>& p2) {
                  // Vector v1 coordinates
                  double v1x = p1.first - minPoint.first;
                  double v1y = p1.second - minPoint.second;
                  // Vector v2 coordinates
                  double v2x = p2.first - minPoint.first;
                  double v2y = p2.second - minPoint.second;

                  // Performing comparison by det
                  double det = v1x * v2y - v1y * v2x;

                  if (det > 0) {
                      // v1 < v2 by det
                      return true;
                  } else if (det == 0) {
                      // v1 == v2 by det. Let's compare by length of vectors
                      double len_v1 = sqrt(pow(v1x, 2) + pow(v1y, 2));
                      double len_v2 = sqrt(pow(v2x, 2) + pow(v2y, 2));

                      return len_v1 < len_v2;
                  } else {
                      // v1 > v2 by det
                      return false;
                  }
              });

    // Then we do Graham scan
    // minPoint and points[0]
    // are the first points of our convex hull
    result.push_back(minPoint), result.push_back((*points)[0]);

    for (size_t i = 1; i < (*points).size(); i++) {
        // p1
        std::pair<int, int> p1 = result[result.size() - 2];
        // p2
        std::pair<int, int> p2 = result[result.size() - 1];
        // p3
        std::pair<int, int> p3 = (*points)[i];

        double rot = rotate(p1, p2, p3);
        // p1, p2, p3 on one line -> replacing p2 with p3
        if (rot == 0) {
            result[result.size() - 1] = p3;
        } else if (rot < 0) {
            // While p1, p2, p3 form right turn -> exclude p2
            while (rotate(result[result.size() - 2], result[result.size() - 1],
                          p3) <= 0)
                result.pop_back();
            result.push_back(p3);
        } else {
            // left turns are ok - just adding p3 to our result
            result.push_back(p3);
        }
    }

    return result;
}

void RedrawImageFromComponents(int* image, const std::map<int, Points>& components,
    int M, int N) {
    for (int i = 0; i < M * N; i++)
        image[i] = 0;

    int labelCounter = 1;
    for (auto it = components.begin(); it != components.end(); it++, labelCounter++) {
        for (int i = 0; i < it->second.size(); i++) {
            image[(it->second[i].second) * N + (it->second[i].first)] = labelCounter;
        }
    }
}

/* ............................. SEQUENTIAL ............................. */

std::map<int, Points> allComponentsSeq;

void BFS(int* image, int M, int N, int yStart, int xStart,
         int label) {
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(xStart, yStart));
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (x >= 0 && y >= 0 && y < M && x < N && image[y * N + x] == 1) {
            image[y * N + x] = label;
            allComponentsSeq[label].push_back(std::make_pair(x, y));

            q.push(std::make_pair(x - 1, y - 1));  // bottom left
            q.push(std::make_pair(x - 1, y));      // left
            q.push(std::make_pair(x - 1, y + 1));  // top left
            q.push(std::make_pair(x, y + 1));      // top
            q.push(std::make_pair(x + 1, y + 1));  // top right
            q.push(std::make_pair(x + 1, y));      // right
            q.push(std::make_pair(x, y - 1));      // bottom
            q.push(std::make_pair(x + 1, y - 1));  // bottom right
        }
    }
}

// 2. Marks components on image (labeling starts from 2)
std::map<int, Points> MarkComponents(int* image, int M, int N) {
    allComponentsSeq.clear();

    int label = 2;
    // i is y coordinate
    for (int i = 0; i < M; i++)
        // j is x coordinate
        for (int j = 0; j < N; j++) {
            if (image[i * N + j] == 1)
                BFS(image, M, N, i, j, label), label++;
        }
    return allComponentsSeq;
}

// Here we should launch Graham for every component to get its convex hull
std::map<int, Points> LeaveOnlyHulls(
    std::map<int, Points>* components, int M, int N) {

    // Then, we should launch Graham for every component to get its convex hull
    std::map<int, Points> hulls;

    for (auto& kv : (*components)) {
        int label = kv.first;
        auto& points = kv.second;
        hulls[label] = GrahamScan(&points);
    }

    return hulls;
}

/* .............................. PARALLEL .............................. */

bool isCoordinatesInBounds(int x, int y, int imgYStart, int imgYEnd, int N) {
    return x >= 0 && x < N && y >= imgYStart && y < imgYEnd;
}

// Threads store their connected components in componentsOfThreads[threadNumber]
std::vector<std::map<int, Points>> componentsOfThreads;

void BFSParallel(int* image, int imgYStart, int imgYEnd, int N, int yStart, int xStart,
         int label) {
    int threadNumber = omp_get_thread_num();

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(xStart, yStart));
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();
        if (isCoordinatesInBounds(x, y, imgYStart, imgYEnd, N) && image[y * N + x] == 1) {
            // assigning label
            image[y * N + x] = label;

            componentsOfThreads[threadNumber][label].push_back(std::make_pair(x, y));

            q.push(std::make_pair(x - 1, y - 1));  // bottom left
            q.push(std::make_pair(x - 1, y));      // left
            q.push(std::make_pair(x - 1, y + 1));  // top left
            q.push(std::make_pair(x, y + 1));      // top
            q.push(std::make_pair(x + 1, y + 1));  // top right
            q.push(std::make_pair(x + 1, y));      // right
            q.push(std::make_pair(x, y - 1));      // bottom
            q.push(std::make_pair(x + 1, y - 1));  // bottom right
        }
    }
}

int label;

void MarkComponentsOfPart(int* image, int imgYStart, int imgYEnd, int N) {
    // i is y coordinate
    for (int i = imgYStart; i <= imgYEnd; i++)
        // j is x coordinate
        for (int j = 0; j < N; j++) {
            if (image[i * N + j] == 1) {
                int lTemp;
                # pragma omp critical
                {
                lTemp = ++label;
                }
                BFSParallel(image, imgYStart, imgYEnd, N, i, j, lTemp);
            }
        }
}

std::map<int, Points> MarkComponentsParallel(int* image, int M, int N) {
    // We divide our image on horizontal parts of piecesDefault height
    // (but the last part will have piecesDefault + piecesLeft height)
    std::string st;

    label = 1;

    int tasksCount;
    int piecesDefault;
    int piecesLeft;

    #pragma omp parallel private(st)
    {
        tasksCount = std::min(omp_get_num_threads(), M);
        piecesDefault = M / tasksCount;
        piecesLeft = M % tasksCount;

        #pragma omp single
        componentsOfThreads.resize(omp_get_num_threads());

        # pragma omp for
        for (int i = 0; i < tasksCount; i++) {
            // last thread will process remained part too
            if (i == tasksCount - 1) {
                MarkComponentsOfPart(image, i * piecesDefault, (i + 1) * piecesDefault + piecesLeft, N);
            } else {
                MarkComponentsOfPart(image, i * piecesDefault, (i + 1) * piecesDefault, N);
            }
        }
    }  // parallelism ends

    // There we will find parts that have connections between each other
    std::set<std::pair<int, int>> connections;

    for (int k = 0; k < tasksCount - 1; k++) {
        int y = ((k + 1) * piecesDefault - 1);

        for (int x = 0; x < N; x++) {
            // Checking 3 points that lying under (x, y)
            if (image[y * N + x] > 0) {
                if (isCoordinatesInImage((x - 1), (y + 1), M, N) &&
                    image[(y + 1) * N + (x - 1)] > 0) {
                    connections.insert(
                        std::make_pair(std::min(image[y * N + x],
                                       image[(y + 1) * N + (x - 1)]),
                                       std::max(image[y * N + x],
                                       image[(y + 1) * N + (x - 1)])));
                    }

                if (isCoordinatesInImage(x, (y + 1), M, N) &&
                    image[(y + 1) * N + x] > 0) {
                    connections.insert(
                        std::make_pair(std::min(image[y * N + x],
                                       image[(y + 1) * N + x]),
                                       std::max(image[y * N + x],
                                       image[(y + 1) * N + x])));
                    }

                if (isCoordinatesInImage((x + 1), (y + 1), M, N) &&
                    image[(y + 1) * N + (x + 1)] > 0) {
                    connections.insert(
                        std::make_pair(std::min(image[y * N + x],
                                       image[(y + 1) * N + (x + 1)]),
                                       std::max(image[y * N + x],
                                       image[(y + 1) * N + (x + 1)])));
                    }
            }
        }
    }

    // Let's save our components in one map
    std::map<int, Points> components;
    for (auto componentsOfSomeThread : componentsOfThreads) {
        components.insert(componentsOfSomeThread.begin(), componentsOfSomeThread.end());
        componentsOfSomeThread.clear();
    }
    componentsOfThreads.clear();

    std::map<int, int> redirections;

    for (auto it = connections.begin(); it != connections.end();) {
        auto conn = *it;

        int realConnFirst = conn.first;
        int realConnSecond = conn.second;

        while (redirections.find(realConnFirst) != redirections.end()) {
            if (realConnFirst <= redirections[realConnFirst])
                break;
            realConnFirst = redirections[realConnFirst];
        }
        while (redirections.find(realConnSecond) != redirections.end()) {
            if (realConnSecond <= redirections[realConnSecond])
                break;
            realConnSecond = redirections[realConnSecond];
        }

        if (realConnSecond == realConnFirst) {
            it = connections.erase(it);
            continue;
        }
        if (realConnSecond < realConnFirst)
            std::swap(realConnFirst, realConnSecond);

        // merging all points this way: conn.first <- conn.second
        components[realConnFirst]
            .insert(components[realConnFirst].end(),
                components[realConnSecond].begin(), components[realConnSecond].end());
        components.erase(realConnSecond);

        it = connections.erase(it);

        redirections[realConnSecond] = realConnFirst;
    }

    label = 1;

    return components;
}

std::map<int, Points> LeaveOnlyHullsParallel(
    std::map<int, Points>* components, int M, int N) {
    std::map<int, Points> hulls;

    componentsOfThreads.clear();

    // Collecting all keys of a map
    std::vector<int> labels((*components).size());
    for (auto it = (*components).begin(); it != (*components).end(); it++) {
        labels.push_back(it->first);
    }

    // Then using paralellism by connected components
    #pragma omp parallel
        #pragma omp single
            componentsOfThreads.resize(omp_get_num_threads());

        #pragma omp for
        for (int i = 0; i < labels.size(); i++) {
            componentsOfThreads[omp_get_thread_num()][labels[i]]
                = GrahamScan(&(*components)[labels[i]]);
        }

    for (auto componentsOfSomeThread : componentsOfThreads) {
        hulls.insert(componentsOfSomeThread.begin(), componentsOfSomeThread.end());
    }
    componentsOfThreads.clear();

    return hulls;
}
