// Copyright 2023 Silaeva Natalya

#include "../../../modules/task_3/silaeva_n_radix_sort_double_batcher/radix_sort_double_batcher.h"
#include <random>
#include <cmath>
#include<algorithm>
#include "tbb/tbb.h"

std::vector<std::vector<int>> get_vector_part_tbb(const std::vector<int>& vec,
    int part) {
    std::vector<std::vector<int>> result(part);
    int vec_size = vec.size();
    tbb::parallel_for(tbb::blocked_range<int>(0, result.size()),
        [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i < range.end(); i++) {
            for (int j = 0; j < vec_size / part; j++) {
                int index = i * (vec_size / part);
                result[i].push_back(vec[index + j]);
            }
        }
    });

    int result_size = result.size();
    if (part * (vec_size / part) < vec_size) {
        for (int i = part * (vec_size / part); i < vec_size; i++) {
            result[result_size - 1].push_back(vec[i]);
        }
    }
    return result;
}

std::vector<int> to_int_tbb(const std::vector<double>& vec,
    unsigned int count) {
    std::vector<int> result(vec.size());
    tbb::parallel_for(tbb::blocked_range<int>(0, vec.size()),
        [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i < range.end(); i++) {
            result[i] = static_cast<int>(vec[i] * pow(10, count));
        }
    });
    return result;
}

std::vector<double> to_double_tbb(const std::vector<int>& vec,
    unsigned int count) {
    std::vector<double> result(vec.size());
    tbb::parallel_for(tbb::blocked_range<int>(0, vec.size()),
        [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i < range.end(); i++) {
            result[i] = static_cast<double>(vec[i]) / pow(10.0, count);
        }
    });
    return result;
}

std::vector<int> counting_sort_tbb(const std::vector<int>& vec, int div) {
    std::vector<int> result(vec.size());
    std::vector<int> count(10, 0);
    int vec_size = vec.size();
    for (int i = 0; i < vec_size; i++) {
        int index = (vec[i] / div) % 10;
        count[index]++;
    }

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = vec_size - 1; i >= 0; i--) {
        result[count[(vec[i] / div) % 10] - 1] = vec[i];
        count[(vec[i] / div) % 10]--;
    }
    return result;
}

std::vector<double> radix_sort_tbb(const std::vector<double>& vec,
    unsigned int count) {
    std::vector<int> vec_int = to_int_tbb(vec, count);
    int num_thread = 4;
    std::vector<std::vector<int>> vector_part
        = get_vector_part_tbb(vec_int, num_thread);

    tbb::parallel_for(tbb::blocked_range<int>(0, num_thread, 1),
        [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i < range.end(); i++) {
            int m = *max_element(vector_part[i].begin(),
                vector_part[i].end());
            for (int div = 1; m / div > 0; div *= 10) {
                vector_part[i] = counting_sort_tbb(vector_part[i], div);
            }
        }
    });

    OddEvenMerge merge;
    std::vector<int> part_all
        = merge.odd_even_merge(vector_part[0], vector_part[1]);
    for (int i = 2; i < num_thread; i++) {
        part_all = merge.odd_even_merge(part_all, vector_part[i]);
    }
    std::vector<double> current_result = to_double_tbb(part_all, count);
    return current_result;
}

bool check_sort(const std::vector<double>& vec) {
    int vec_size = vec.size();
    for (int i = 0; i < vec_size - 1; i++) {
        if (vec[i] > vec[i + 1])
            return false;
    }
    return true;
}

std::vector<double> get_random_double_vector(unsigned int elements) {
    std::vector<double> result(elements);
    std::uniform_real_distribution<double> unif(10.0, 120.0);
    std::default_random_engine random_engine;
    for (unsigned int i = 0; i < elements; i++) {
        result[i] = unif(random_engine);
        result[i] -= remainder(result[i], 0.001);
    }
    return result;
}
