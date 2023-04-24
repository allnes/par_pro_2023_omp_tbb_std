// Copyright 2023 Sigachev Anton
#include "../../../modules/task_2/sigachev_a_shell_sort_odd_even_merge_omp/sort.h"
#include <random>

typedef std::vector<int>::size_type vec_size_t;

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int  i = 0; i < size; i++) {
        vec[i] = gen() % size;
    }
    return vec;
}

// Shell sort with Hibbard's step
// https://www.cyberforum.ru/cpp-beginners/thread2430694.html
void ShellSortSequantial(std::vector<int>* vec) {
    unsigned size = vec->size();
    unsigned k = 1;
    while ((k << 1 | 1) < size) {  // 2 * k + 1 < size
        k = (k << 1) | 1;  // k = 2 * k + 1
    }
    for (; k > 0; k >>= 1) {  // k /= 2
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

std::vector<int> merge(const std::vector<int>& vec_1,
                       const std::vector<int>& vec_2) {
    std::vector<int> vec_res(vec_1.size() + vec_2.size());
    size_t i = 0, j = 0, k = 0;
    while (i < vec_1.size() && j < vec_2.size()) {
        vec_res[k++] = (vec_1[i] < vec_2[j] ? vec_1[i++] : vec_2[j++]);
    }
    while (i < vec_1.size()) {
        vec_res[k++] = vec_1[i++];
    }
    while (j < vec_2.size()) {
        vec_res[k++] = vec_2[j++];
    }
    return vec_res;
}

void ShellSortParallel(std::vector<int>* vec) {
    int count_threads = omp_get_num_procs();
    int delta = vec->size() / count_threads;
    std::vector<std::vector<int>> proc_res(count_threads);
    #pragma omp parallel num_threads(count_threads)
    {
        int rank = omp_get_thread_num();
        auto end = vec->end();
        if (count_threads - 1 != rank) {
            end = vec->begin() + (rank + 1) * delta;
        }
        proc_res[rank] = { vec->begin() + rank * delta, end };
        ShellSortSequantial(&proc_res[rank]);
    }
    *vec = proc_res[0];
    for (int i = 1; i < count_threads; i++) {
        *vec = merge(*vec, proc_res[i]);
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
