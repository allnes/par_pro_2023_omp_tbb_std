// Copyright 2023 Nikiforova Lada
#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_2/nikiforova_l_trapezoidal_method_omp/trapezoidal_method.h"

double trapezoidalMethod(double (*function)(std::vector<double>),
             std::vector<std::pair<double, double>> front, int p) {
    int dim = front.size();
    int seg = 1;
    std::vector<double> dlt(dim);
    int i = 0;
    while (i < dim) {
        dlt[i] = (front[i].second - front[i].first) / p;
        seg *= p;
        i++;
    }
    double res = 0.0;
    #pragma omp parallel shared(res, dim, seg, dlt, front, p)
    {
        std::vector<double> prm(dim);
        int const THREAD_NUMBER = omp_get_thread_num();
        int const NUMBER_THREADS = omp_get_num_threads();
        int start = seg / NUMBER_THREADS * THREAD_NUMBER;
        int n = seg / NUMBER_THREADS;
        if ((seg % NUMBER_THREADS) < THREAD_NUMBER) {
            n++;
            start += THREAD_NUMBER;
        } else {
            start += (seg % NUMBER_THREADS);
        }
        for (int i = 0; i < n; i++) {
            int k = i + start;
            for (int j = 0; j < dim; j++) {
                prm[j] = front[j].first + dlt[j] * (k % p);
                k /= p;
            }
            double trm = function(prm);
            for (int j = 0; j < dim; j++) {
                if (prm[j] == front[j].first) {
                trm /= 2;
                }
                if (prm[j] == front[j].second) {
                trm /= 2;
                }
            }
            #pragma omp atomic
                res += trm;
        }
    }
    int n = 0;
    while (n < dim) {
        res *= dlt[n];
        n++;
    }
    return res;
}
