// Copyright 2023 Bochkarev Vladimir
#include <omp.h>
#include <time.h>
#include <functional>
#include <iostream>
#include "../../../modules/task_2/bochkarev_v_integral_tr/integral_omp.h"

double integral3D(double a, double b, double c, double d, double e,
double f, int n, const std::function<double(double, double, double)> &fun) {
    const double hx = (b-a)/n;
    const double hy = (d-c)/n;
    const double hz = (f-e)/n;
    double res = 0;
    int chunck;
    #pragma omp parallel for reduction(+: res)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                const double x1 = a + i*hx;
                const double x2 = a + (i+1)*hx;

                const double y1 = c + j*hy;
                const double y2 = c + (j+1)*hy;

                const double z1 = e + k*hz;
                const double z2 = e + (k+1)*hz;

                res+=0.5*(x2-x1)*(y2-y1)*(z2-z1)*(fun(x1, y1, z1)+fun(x2, y2, z2));
            }
    return res;
}
