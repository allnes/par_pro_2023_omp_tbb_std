// Copyright 2023 Terina Alina
#include <algorithm>
#include <vector>
#include <ctime>
#include <utility>
#include <random>
#include "../../../modules/task_1/terina_a_quicksort_smpl_merge/qs_smpl_mrg.h"

void quickSort(int l, int r, std::vector <int>* list) {
    while (r > l) {
        int lo = l;
        int hi = r;
        int p = list->at((l + r) / 2);
        while (lo <= hi) {
            while (list->at(lo) < p) {
                lo++;
            }
            while (list->at(hi) > p) {
                hi--;
            }
            if (lo <= hi) {
                std::swap(list->at(lo), list->at(hi));
                lo++;
                hi--;
            }
        }
        if (2 * lo > l + r) {
            quickSort(lo, r, list);
            r = lo - 1;
        } else {
            quickSort(l, lo - 1, list);
            l = lo;
        }
    }
    return;
}

std::vector <int> getRandomVector(int n) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution <int> dist(0, 100);
    std::vector <int> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}
std::vector<int> GetSortedVec(int n) {
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = i;
    }
    return vec;
}

std::vector<int> GetReversedVec(int n) {
    std::vector<int> vec(n);
    for (int i = n - 1; i <= 0; i--) {
        vec[i] = i;
    }
    return vec;
}
