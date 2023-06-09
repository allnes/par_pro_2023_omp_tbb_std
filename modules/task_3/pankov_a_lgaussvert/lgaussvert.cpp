// Copyright 2023 Pankov Anatoliy
#include "../../../modules/task_3/pankov_a_lgaussvert/lgaussvert.h"

int Clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

std::vector<double> MakeRandomMatrix(int m, int n) {
    std::mt19937 gen;
    std::vector<double> Result(m * n);
    for (int i = 0; i < m * n; ++i) {
        Result[i] = gen() % 256;
    }
    return Result;
}

std::vector<double> SeqGaussFilter(const std::vector<double>& matrix,
                                          int m, int n) {
    if (m <= 0 || n <= 0 || matrix.size() == 0) {
        throw "Incorrect dimensions";
    }

    int Size = 3;
    double Sigm = 1.0;
    int Radius = 1;
    double Norm = 0;

    std::vector<double> Kernel(Size * Size);
    std::vector<double> Result(m * n);

    for (int i = -Radius; i < Radius + 1; ++i) {
        for (int j = -Radius; j < Radius + 1; ++j) {
            int Idx = (i + Radius) * Size + j + Radius;
            Kernel[Idx] = exp(-(i * i + j * j) / (Sigm * Sigm));
            Norm += Kernel[Idx];
        }
    }

    for (int i = 0; i < Size * Size; ++i) {
        Kernel[i] /= Norm;
    }

    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            double Res = 0;
            for (int i = -Radius; i < Radius + 1; ++i) {
                for (int j = -Radius; j < Radius + 1; ++j) {
                    int x_ = Clamp(j + x, 0, m - 1);
                    int y_ = Clamp(i + y, 0, n - 1);

                    double value = matrix[y_ + x_ * n];

                    Res += value * Kernel[(i + Radius) * Size + j + Radius];
                }
            }
            Res = Clamp(Res, 0, 255);
            Result[y + x * n] = Res;
        }
    }
    return Result;
}

std::vector<double> TBBGaussFilter(const std::vector<double>& matrix, int m,
                                   int n) {
    if (m <= 0 || n <= 0 || matrix.size() == 0) {
        throw -1;
    }

    int Size = 3;
    double Sigm = 1.0;
    int Radius = 1;
    double Norm = 0;

    std::vector<double> Kernel(Size * Size);
    std::vector<double> Result(m * n);

    for (int i = -Radius; i <= Radius; ++i) {
        for (int j = -Radius; j <= Radius; ++j) {
            int Idx = (i + Radius) * Size + j + Radius;
            Kernel[Idx] = exp(-(i * i + j * j) / (Sigm * Sigm));
            Norm += Kernel[Idx];
        }
    }

    for (int i = 0; i < Size * Size; ++i) {
        Kernel[i] /= Norm;
    }

    for (int x = 0; x < m; ++x) {
        tbb::parallel_for(
            tbb::blocked_range<int>(0, n, 1),
            [&](const tbb::blocked_range<int>& range) {
                for (int y = range.begin(); y != range.end(); ++y) {
                    double resColor = 0;
                    for (int i = -Radius; i <= Radius; ++i) {
                        for (int j = -Radius; j <= Radius; ++j) {
                            int Idx = (i + Radius) * Size + j + Radius;

                            int x_ = Clamp(x + j, 0, m - 1);
                            int y_ = Clamp(y + i, 0, n - 1);

                            double value = matrix[y_ + x_ * n];
                            resColor += value * Kernel[Idx];
                        }
                    }
                    resColor = Clamp(resColor, 0, 255);
                    Result[y + x * n] = resColor;
                }
            });
    }

    return Result;
}
