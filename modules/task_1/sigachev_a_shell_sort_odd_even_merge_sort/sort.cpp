// Copyright 2023 Sigachev Anton
#include <random>
#include <algorithm>
#include "../../../modules/task_1/sigachev_a_shell_sort_odd_even_merge_sort/sort.h"

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int  i = 0; i < size; i++) {
        vec[i] = gen() % size;
    }
    return vec;
}

void ShellSort(std::vector<int>* vec) {
    unsigned size = vec->size();
    unsigned k = 1;
    while ((k << 1 | 1) < size) {
        k = (k << 1) | 1;
    }
    for (; k > 0; k >>= 1) {
        for (unsigned i = k; i < size; i++) {
            int t = (*vec)[i];
            unsigned j = i;
            for (; (j >= k) && (t < (*vec)[j - k]); j -= k) {
                (*vec)[j] = (*vec)[j - k];
            }
            (*vec)[j] = t;
        }
    }
}

bool checkSort(const std::vector<int>& vec) {
    unsigned size = vec.size();
    for (unsigned i = 1; i < size; i++) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}
