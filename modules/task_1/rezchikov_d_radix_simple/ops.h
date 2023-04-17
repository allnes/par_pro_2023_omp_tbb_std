// Copyright 2023 Rezchikov Dmitrii
#pragma once

#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

void countingSortSeq(std::vector<int> * array, int l, int r, int place);
void radSortSeq(std::vector<int> * vec);
void mergeRadixSort(std::vector<int> * vec);
std::vector<int> getRndVector(int size);
