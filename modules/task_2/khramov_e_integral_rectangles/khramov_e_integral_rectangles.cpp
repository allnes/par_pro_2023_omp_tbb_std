// Copyright 2023 Khramov Egor
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../../../modules/task_2/khramov_e_integral_rectangles/khramov_e_integral_rectangles.h"


double getRectangleValue(IntegralFunction f, double x, double y, double z, double* h) {
    return f(x + h[0] / 2, y + h[1] / 2, z + h[2] / 2);
}

double integrateSequential(IntegralFunction func, double a[3], double b[3], int n[3]) {
    double result = 0.0;

    double h[3];
    for (int i = 0; i < 3; i++) {
        h[i] = (b[i] - a[i]) / n[i];
    }

    for (int i = 0; i < n[0]; i++) {
        for (int j = 0; j < n[1]; j++) {
            for (int k = 0; k < n[2]; k++) {
                double x = a[0] + h[0] * i;
                double y = a[1] + h[1] * j;
                double z = a[2] + h[2] * k;
                double value = getRectangleValue(func, x, y, z, h);
                result += h[0] * h[1] * h[2] * value;
            }
        }
    }

    return result;
}

double integrateParallel(IntegralFunction func, double a[3], double b[3], int n[3]) {
    double result = 0.0;

    double h[3];
    for (int i = 0; i < 3; i++) {
        h[i] = (b[i] - a[i]) / n[i];
    }

    #pragma omp parallel for reduction(+: result)
        for (int i = 0; i < n[0]; i++) {
            for (int j = 0; j < n[1]; j++) {
                for (int k = 0; k < n[2]; k++) {
                    double x = a[0] + h[0] * i;
                    double y = a[1] + h[1] * j;
                    double z = a[2] + h[2] * k;
                    double value = getRectangleValue(func, x, y, z, h);
                    result += h[0] * h[1] * h[2] * value;
                }
            }
        }

    return result;
}
