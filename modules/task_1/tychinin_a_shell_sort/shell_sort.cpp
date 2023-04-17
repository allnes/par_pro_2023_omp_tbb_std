// Copyright 2023 Tychinin Alexey

#include "shell_sort.h"  // NOLINT

namespace task1 {
    std::vector<double> shell_sort(std::vector<double> vec) {
        for (int interval = vec.size() / 2; interval > 0; interval /= 2) {
            for (int i = interval; i < vec.size(); i++) {
                double tmp = vec[i];
                int j = i;
                for (; j >= interval && vec[j - interval] > tmp; j -= interval) {
                    vec[j] = vec[j - interval];
                }
                vec[j] = tmp;
            }
        }

        return vec;
    }

}  // namespace task1
