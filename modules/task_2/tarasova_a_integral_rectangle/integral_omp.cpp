// Copyright 2023 Tarasova Anastasiya
#include "../../../modules/task_2/tarasova_a_integral_rectangle/integral_omp.h"
#include <vector>
#include <omp.h>

double getParallel(const double& a1, const double& a2, const double& a3, const double& b1,
    const double& b2, const double& b3, const double& h, double (*f)(double, double, double)) {
    double sum = 0.0, x, y, z;
    int n1, n2, n3;
    n1 = (int)((b1 - a1) / h);
    n2 = (int)((b2 - a2) / h);
    n3 = (int)((b3 - a3) / h);
    std::vector<double> x1(n1), y1(n2), z1(n3);
#pragma omp parallel for private (x)
    for (int i = 0; i < n1; i++) {
        x = a1 + i * h + h / 2;
        x1[i] = x;
    }
#pragma omp parallel for private (y)
    for (int i = 0; i < n2; i++) {
        y = a2 + i * h + h / 2;
        y1[i] = y;
    }
#pragma omp parallel for private (z)
    for (int i = 0; i < n3; i++) {
        z = a3 + i * h + h / 2;
        z1[i] = z;
    }
#pragma omp parallel for private (x, y, z, k)/reduction(+:sum)
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            for (int k = 0; k < n3; k++) {
                sum += f(x1[i], y1[j], z1[k]) * h * h * h;
            }
    return sum;
}

double getSequential(const double& a1, const double& a2, const double& a3, const double& b1,
    const double& b2, const double& b3, const double& h, double (*f)(double, double, double)) {
    double sum = 0.0, x, y, z;
    int n1, n2, n3;
    n1 = (int)((b1 - a1) / h);
    n2 = (int)((b2 - a2) / h);
    n3 = (int)((b3 - a3) / h);
    std::vector<double> x1(n1), y1(n2), z1(n3);
    for (int i = 0; i < n1; i++) {
        x = a1 + i * h + h / 2;
        x1[i] = x;
    }
    for (int i = 0; i < n2; i++) {
        y = a2 + i * h + h / 2;
        y1[i] = y;
    }
    for (int i = 0; i < n3; i++) {
        z = a3 + i * h + h / 2;
        z1[i] = z;
    }
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            for (int k = 0; k < n3; k++) {
                sum += f(x1[i], y1[j], z1[k]) * h * h * h;
            }
    return sum;
}