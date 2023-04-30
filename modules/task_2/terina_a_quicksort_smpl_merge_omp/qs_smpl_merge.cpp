// Copyright 2023 Terina Alina
#include <omp.h>
#include <utility>
#include <vector>
#include "../../../modules/task_2/terina_a_quicksort_smpl_merge_omp/qs_smpl_merge.h"

void quickSort(int l, int r, std::vector <double>* list) {
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
std::vector <double> getRandomVector(int n) {
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> dist(0, 100);
    std::vector <double> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}
void quicksort(double* arr, int l, int r) {
    int lo = l, hi = r;
    double p = arr[(l + r) / 2];

    do {
        while (arr[lo] < p)
            lo++;
        while (arr[hi] > p)
            hi--;
        if (lo <= hi) {
            if (lo < hi) {
                std::swap(arr[lo], arr[hi]);
            }
            lo++;
            hi--;
        }
    } while (lo <= hi);

    if (lo < r)
        quicksort(arr, lo, r);
    if (l < hi)
        quicksort(arr, l, hi);
}

void genrndArr(double* arr, int n) {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> uid(0, n);
    for (int i = 0; i < n; i++) {
        arr[i] = uid(gen);
    }
}

void SimpleMerge(double* arr, int n, double* arr1, int m) {
    int i = 0, j = 0, k = 0;
    double* mergearr = new double[n + m];
    while (i < n && j < m) {
        if (arr[i] > arr1[j]) {
            mergearr[k++] = arr1[j++];
        } else {
            if (arr[i] < arr1[j]) {
                mergearr[k++] = arr[i++];
            } else {
                mergearr[k++] = arr[i++];
                mergearr[k++] = arr1[j++];
            }
        }
    }

    while (i < n) {
        mergearr[k++] = arr[i++];
    }

    while (j < m) {
        mergearr[k++] = arr1[j++];
    }

    for (int i = 0; i < m + n; i++) {
        arr[i] = mergearr[i];
    }
}

void quickSortPar_OMP(double* arr, int n) {
    int number_thrds = 2;
    omp_set_num_threads(number_thrds);
    std::vector<std::vector<int>> begin_end(number_thrds, std::vector<int>(2));
#pragma omp parallel
    {
        int thread = omp_get_thread_num();
        begin_end[thread][0] = thread * (n / number_thrds);

        if (thread == number_thrds - 1) {
            begin_end[thread][1] = n - 1;
        } else {
            begin_end[thread][1] = begin_end[thread][0] + n / number_thrds - 1;
        }
        quicksort(arr, begin_end[thread][0], begin_end[thread][1]);
    }
    int m = number_thrds / 2;
    while (begin_end.size() > 1) {
        omp_set_num_threads(m);
#pragma omp parallel
        {
            size_t thread = omp_get_thread_num();
            SimpleMerge(&arr[begin_end[thread * 2][0]],
             begin_end[thread * 2][1] - begin_end[thread * 2][0] + 1,
                &arr[begin_end[thread * 2 + 1][0]],
                 begin_end[thread * 2 + 1][1]
                  - begin_end[thread * 2 + 1][0] + 1);
            begin_end[thread * 2][1] = begin_end[thread * 2 + 1][1];
        }
        for (int i = 1; i <= m; i++) {
            begin_end.erase(begin_end.begin() + i);
        }
        number_thrds -= m;
        m = number_thrds / 2;
    }
}
