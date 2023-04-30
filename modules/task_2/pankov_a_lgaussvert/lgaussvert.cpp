// Copyright 2023 Pankov Anatoliy
#include "../../../modules/task_2/pankov_a_lgaussvert/lgaussvert.h"

int Clamp(int value, int max, int min) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

std::vector<double> MakeRandomMatrix(int m, int n) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> Result(m * n);
    for (int i = 0; i < m * n; i++) Result[i] = gen() % 256;
    return Result;
}

std::vector<double> SeqGaussFilter(const std::vector<double>& matrix,
                                          int m, int n) {
    if (m <= 0 || n <= 0 || matrix.size() == 0) {
        throw "Incorrect dimensions";
    }
    const int Size = 3;
    const double Sigm = 1.0;
    const int Radius = 1;
    double Norm = 0;

    std::vector<double> Result(m * n);
    std::vector<double> Kernel(Size * Size);

    for (int i = -Radius; i < Radius + 1; i++) {
        for (int j = -Radius; j < Radius + 1; j++) {
            int Idx = (i + Radius) * Size + j + Radius;
            Kernel[Idx] = exp(-(i * i + j * j) / (Sigm * Sigm));
            Norm += Kernel[Idx];
        }
    }

    for (int i = 0; i < Size * Size; i++) {
        Kernel[i] /= Norm;
    }

    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            double Res = 0;
            for (int i = -Radius; i < Radius + 1; i++) {
                for (int j = -Radius; j < Radius + 1; j++) {
                    int Idx = (i + Radius) * Size + j + Radius;

                    int x_ = Clamp(x + j, m - 1, 0);
                    int y_ = Clamp(y + i, n - 1, 0);

                    double value = matrix[x_ * n + y_];

                    Res += value * Kernel[Idx];
                }
            }
            Res = Clamp(Res, 255, 0);
            Result[x * n + y] = Res;
        }
    }
    return Result;
}

std::vector<double> OMPGaussFilter(const std::vector<double>& matrix,
                                          int m, int n) {
    if (m <= 0 || n <= 0 || matrix.size() == 0) {
        throw -1;
    }

    const int Size = 3;
    const double Sigm = 1.0;
    const int Radius = 1;
    double Norm = 0;
    int x, y, i, j;

    std::vector<double> Result(m * n);
    std::vector<double> Kernel(Size * Size);

    for (i = -Radius; i < Radius + 1; ++i) {
        for (j = -Radius; j < Radius + 1; ++j) {
            int Idx = (i + Radius) * Size + j + Radius;
            Kernel[Idx] = exp(-(i * i + j * j) / (Sigm * Sigm));
            Norm = Norm + Kernel[Idx];
        }
    }

    for (i = 0; i < Size * Size; i++) {
        Kernel[i] = Kernel[i] / Norm;
    }

    #pragma omp parallel for private(i, j, x, y)
        for (x = 0; x < m; ++x) {
            for (y = 0; y < n; ++y) {
                double Res = 0;
                for (i = -Radius; i < Radius + 1; ++i) {
                    for (j = -Radius; j < Radius + 1; ++j) {
                        int Idx = (i + Radius) * Size + j + Radius;
                        int x_ = Clamp(x + j, m - 1, 0);
                        int y_ = Clamp(y + i, n - 1, 0);
                        double value = matrix[x_ * n + y_];
                        Res += value * Kernel[Idx];
                    }
                }
                Res = Clamp(Res, 255, 0);
                Result[x * n + y] = Res;
            }
        }

    return Result;
}
