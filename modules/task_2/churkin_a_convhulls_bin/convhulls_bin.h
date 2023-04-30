// Copyright 2023 Churkin Aleksandr
#ifndef MODULES_TASK_2_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_
#define MODULES_TASK_2_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_

#include <vector>
#include <map>
#include <utility>

typedef std::vector<std::pair<int, int>> Points;

// .......... Common functions ..........................
std::vector<int> GetRandomBinImage(int M, int N);
void PrintImage(int* image, int M, int N);

bool isCoordinatesInImage(int x, int y, int M, int N);
double rotate(const std::pair<int, int>& p1,
              const std::pair<int, int>& p2,
              const std::pair<int, int>& p3);
Points GrahamScan(Points* points);

// Helpful function to compare that everything is ok
void RedrawImageFromComponents(int* image, const std::map<int, Points>& components, int M, int N);
// ......................................................

// .......... Functions for SEQUENTIAL algorighm ..........
void BFS(int* image, int M, int N, int yStart, int xStart,
         int label);
std::map<int, Points> MarkComponents(int* image, int M, int N);
std::map<int, Points> LeaveOnlyHulls(
    std::map<int, Points>* components, int M, int N);
// ......................................................

// .......... Functions for PARALLEL algorighm ..........
bool isCoordinatesInBounds(int x, int y, int imgYStart, int imgYEnd, int N);

void BFSParallel(int* image, int imgYStart, int imgYEnd, int N, int yStart, int xStart,
         int label);
void MarkComponentsOfPart(int* image, int imgYStart, int imgYEnd, int N);

std::map<int, Points> MarkComponentsParallel(int* image, int M, int N);
std::map<int, Points> LeaveOnlyHullsParallel(
    std::map<int, Points>* components, int M, int N);
// ......................................................

#endif  // MODULES_TASK_2_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_
