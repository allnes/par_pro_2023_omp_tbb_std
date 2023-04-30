// Copyright 2023 Kuleva Anna
#include <omp.h>
#include <vector>
#include <iostream>
#include <iterator>
#include <limits>
#include <algorithm>
#include <utility>
#include "../../../modules/task_2/kuleva_a_radix_double_batcher_omp/radix_double_batcher_omp.h"


using ull = uint64_t;

union Value {
    ull asLong;
    double asDouble;
};

ull getOffset(ull value, int exp) {
    return (value >> (8 * exp));
}

void radixSortForExp(std::vector<double>* _base, int exp) {
    Value value{ 0 };
    auto& base = *_base;
    std::vector<double> result(base.size());
    std::vector<int> sorterArray((1 << 8), 0);
    int mask = (1 << 8) - 1;

    for (double element : base) {
        value.asDouble = element;
        const int expValue = mask & getOffset(value.asLong, exp);
        sorterArray[expValue]++;
    }

    for (int i = 1; i < sorterArray.size(); i++) {
        sorterArray[i] += sorterArray[i - 1];
    }

    for (int i = base.size() - 1; i >= 0; i--) {
        value.asDouble = base[i];
        const int expValue = mask & getOffset(value.asLong, exp);
        result[sorterArray[expValue] - 1] = base[i];
        sorterArray[expValue]--;
    }

    for (int i = 0; i < base.size(); i++)
        base[i] = result[i];
}

void radixSort(std::vector<double>* _base) {
    auto& base = *_base;
    int maxExp = sizeof(double);

    std::vector<double> negative, positive;

    std::copy_if(base.begin(), base.end(), std::back_inserter(negative), [](double x) { return x < 0; });
    std::copy_if(base.begin(), base.end(), std::back_inserter(positive), [](double x) { return x >= 0; });

    for (int exp = 0; exp < maxExp; exp++) {
        radixSortForExp(&negative, exp);
        radixSortForExp(&positive, exp);
    }

    auto last = std::copy(negative.rbegin(), negative.rend(), base.begin());
    std::copy(positive.begin(), positive.end(), last);
}

void compareAndExchange(double* a, double* b) {
    if (*b < *a) std::swap(*a, *b);
}

std::vector<double> shuffle(const std::vector<double>& base) {
    std::vector<double> result(base);
    const int half = base.size() / 2;
    for (int i = 0, j = 0; j + half < result.size() && i + 1 < result.size(); i += 2, j++) {
        result[i] = base[j];
        result[i + 1] = base[j + half];
    }
    return result;
}

std::vector<double> batcherMerge(const std::vector<double>& left, const std::vector<double>& right) {
    std::vector<double> result(left.size() + right.size());
    result = shuffle(result);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());
    return result;
}

std::vector<double> radixBatcherSort(const std::vector<double>& base) {
    std::vector<double> result;

#pragma omp parallel
    {
        const int tid = omp_get_thread_num();
        const int tc = omp_get_num_threads();
        const int step = base.size() / tc + ((base.size() % tc) != 0);
        const int rightOffset = std::min(step * (tid + 1), static_cast<int>(base.size()));
        std::vector<double> local(base.begin() + step * tid, base.begin() + rightOffset);
        radixSort(&local);
#pragma omp critical
        {
            result = batcherMerge(local, result);
        }
    }

    return result;
}
