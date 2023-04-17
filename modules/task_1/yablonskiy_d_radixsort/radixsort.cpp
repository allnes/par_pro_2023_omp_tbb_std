// Copyright 2023 Yablonskiy Dmitriy
#include "../../../modules/task_1/yablonskiy_d_radixsort/radixsort.h"

#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> radixSort(const std::vector<int>& arr) {
    std::vector<int> arr_;
    arr_ = arr;
    std::vector<int> ares;
    int num = 0;
    int maxv = 0;
    for (int i = 0; i < arr_.size(); i++) {
        if (maxv <= arr_[i]) {
            maxv = arr_[i];
        }
    }
    while (maxv > 0) {
        num++;
        maxv /= 10;
    }
    std::vector<int> temp(arr_.size());
    for (int i = 0; i < num; i++) {
        std::vector<int> co(10);
        int exp = pow(10, i);
        for (int j = 0; j < arr_.size(); j++) {
            int d = (arr_[j] / exp) % 10;
            co[d]++;
        }
        for (int j = 1; j < co.size(); j++) {
            co[j] += co[j - 1];
        }
        for (int j = arr_.size() - 1; j >= 0; j--) {
            int d = (arr_[j] / exp) % 10;
            temp[co[d] - 1] = arr_[j];
            co[d]--;
        }
        swap(arr_, temp);
    }

    return arr_;
}

