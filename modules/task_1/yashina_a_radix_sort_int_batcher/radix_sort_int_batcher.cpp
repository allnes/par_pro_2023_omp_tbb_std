// Copyright 2023 Yashina Anastasia
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <utility>
#include <random>
#include "../../../modules/task_1/yashina_a_radix_sort_int_batcher/radix_sort_int_batcher.h"

bool checkSort(std::vector<int> arr) {
    return std::is_sorted(std::begin(arr), std::end(arr));
}

void radixSort(std::vector<int> *vec) {
    int max = getMax(vec);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(vec, exp);
    }
}

void countSort(std::vector<int> *vec, int exp) {
    int size = vec->size();
    std::vector<int> output(size);
    int i, count[10] = { 0 };
    for (i = 0; i < size; i++) {
        count[(vec->at(i) / exp) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = size - 1; i >= 0; i--) {
        output[count[(vec->at(i) / exp) % 10] - 1] = vec->at(i);
        count[ (vec->at(i) / exp) % 10 ]--;
    }
    for (i = 0; i < size; i++) {
        vec->at(i) = output[i];
    }
}

int getMax(std::vector<int> *vec) {
    int size = vec->size();
    int max = vec->at(0);
    for (int i = 1; i < size; i++) {
        if (vec->at(i) > max) {
            max = vec->at(i);
        }
    }
    return max;
}

std::vector<int> EvenOddBatch(std::vector<int> vec1, std::vector<int> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int size = size1 + size2;
    std::vector<int> res(size);
    int i = 0, j = 0, k = 0;

    while ((j < size1) && (k < size2)) {
        res[i] = vec1[j];
        res[i + 1] = vec2[k];
        i += 2;
        j++;
        k++;
    }

    if ((k >= size2) && (j < size1)) {
        for (int l = i; l < size; l++) {
            res[l] = vec1[j];
            j++;
        }
    }

    for (int i = 0; i < size - 1; i++) {
        if (res[i] > res[i + 1]) {
            std::swap(res[i], res[i + 1]);
        }
    }

    return res;
}

std::vector<int> evenBatch(std::vector<int> vec1, std::vector<int> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int res_size = size1 / 2 + size2 / 2 + size1 % 2 + size2 % 2;
    std::vector<int> res(res_size);
    int i1 = 0;
    int i2 = 0;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (vec1[i1] <= vec2[i2]) {
            res[i] = vec1[i1];
            i1 += 2;
        } else {
            res[i] = vec2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[i] = vec2[l];
            i++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[i] = vec1[l];
            i++;
        }
    }
    return res;
}

std::vector<int> oddBatch(std::vector<int> vec1, std::vector<int> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int res_size = size1 / 2 + size2 / 2;
    std::vector<int> res(res_size);
    int i1 = 1;
    int i2 = 1;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (vec1[i1] <= vec2[i2]) {
            res[i] = vec1[i1];
            i1 += 2;
        } else {
            res[i] = vec2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[i] = vec2[l];
            i++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[i] = vec1[l];
            i++;
        }
    }

    return res;
}

std::vector<int> GetRandVector(int size) {
    if (size < 1)
        throw - 1;
    std::mt19937 gen;
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % 100;
    }

    return vec;
}
