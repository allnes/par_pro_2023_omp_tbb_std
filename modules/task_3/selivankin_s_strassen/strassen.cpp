// Copyright 2023 Selivankin Sergey
#include <tbb/tbb.h>
#include <vector>
#include <random>
#include "../../../modules/task_3/selivankin_s_strassen/strassen.h"

std::vector<double> getRandomMatrix(int m, int n) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<double> vec(m * n);
    for (int i = 0; i < m * n; i++) { vec[i] = static_cast<double>(gen() % 100 + 1); }
    return vec;
}

int getNewSize(int m1, int n1, int m2, int n2) {
    int max = (std::max)((std::max)(m1, n1), (std::max)(m2, n2));
    int n = 1;
    for (; max > n; n*=2) {}
    return n;
}

std::vector<double> appendZeros(const std::vector<double>& mat, int m, int n, int size) {
    std::vector<double> result(size * size);

    for (int i = 0, j = 0; i < result.size(); ++i) {
        if (i % size < n && j < m * n) {
            result[i] = mat[j++];
        } else {
            result[i] = 0;
        }
    }

    return result;
}

std::vector<double> sumOrSub(bool isSum, const std::vector<double>& mat1, const std::vector<double>& mat2) {
    std::vector<double> result(mat1.size());

    for (int i = 0; i < mat1.size(); ++i) {
        result[i] = isSum ? mat1[i] + mat2[i] : mat1[i] - mat2[i];
    }

    return result;
}

std::vector<std::vector<double>> splitMatrix(const std::vector<double>& mat) {
    std::vector<std::vector<double>> result(4);
    int n = static_cast<int>(sqrt(mat.size()));

    for (int i = 0; i < 4; ++i) {
        std::vector<double> sub((n / 2) * (n / 2));
        result[i] = sub;
    }

    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            result[0][(i * n/2) + j] = mat[(i * n) + j];
            result[1][(i * n/2) + j] = mat[(i * n) + j + (n / 2)];
            result[2][(i * n/2) + j] = mat[(i * n) + (n * n / 2) + j];
            result[3][(i * n/2) + j] = mat[(i * n) + (n * n / 2) + j + (n / 2)];
        }
    }

    return result;
}

std::vector<double> mergeMatrix(const std::vector<std::vector<double>>& mats, int size) {
    std::vector<double> result(size);
    int n = static_cast<int>(sqrt(size));

    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            result[(i * n) + j] = mats[0][(i * n/2) + j];
            result[(i * n) + j + (n / 2)] = mats[1][(i * n/2) + j];
            result[(i * n) + (n * n / 2) + j] = mats[2][(i * n/2) + j];
            result[(i * n) + (n * n / 2) + j + (n / 2)] = mats[3][(i * n/2) + j];
        }
    }

    return result;
}

std::vector<double> strassen(const std::vector<double>& A, const std::vector<double>& B) {
    int base_size = static_cast<int>(A.size());

    if (base_size == 4) {
        double P1 = (A[0] + A[3]) * (B[0] + B[3]);
        double P2 = (A[2] + A[3]) * (B[0]);
        double P3 = (A[0]) * (B[1] - B[3]);
        double P4 = (A[3]) * (B[2] - B[0]);
        double P5 = (A[0] + A[1]) * (B[3]);
        double P6 = (A[2] - A[0]) * (B[0] + B[1]);
        double P7 = (A[1] - A[3]) * (B[2] + B[3]);

        std::vector<double> C(4);
        C[0] = P1 + P4 - P5 + P7;
        C[1] = P3 + P5;
        C[2] = P2 + P4;
        C[3] = P1 - P2 + P3 + P6;

        return C;
    } else {
        std::vector<std::vector<double>> subA = splitMatrix(A);
        std::vector<std::vector<double>> subB = splitMatrix(B);
        int split_size = static_cast<int>(subA[0].size());
        std::vector<std::vector<double>> P(7);

        P[0] = strassen(sumOrSub(true, subA[0], subA[3]), sumOrSub(true, subB[0], subB[3]));
        P[1] = strassen(sumOrSub(true, subA[2], subA[3]), subB[0]);
        P[2] = strassen(subA[0], sumOrSub(false, subB[1], subB[3]));
        P[3] = strassen(subA[3], sumOrSub(false, subB[2], subB[0]));
        P[4] = strassen(sumOrSub(true, subA[0], subA[1]), subB[3]);
        P[5] = strassen(sumOrSub(false, subA[2], subA[0]), sumOrSub(true, subB[0], subB[1]));
        P[6] = strassen(sumOrSub(false, subA[1], subA[3]), sumOrSub(true, subB[2], subB[3]));

        std::vector<std::vector<double>> C(4);

        for (int i = 0; i < 4; ++i) {
            std::vector<double> c(split_size);
            C[i] = c;
        }

        for (int i = 0; i < split_size; ++i) {
            C[0][i] += P[0][i] + P[3][i] - P[4][i] + P[6][i];
            C[1][i] += P[2][i] + P[4][i];
            C[2][i] += P[1][i] + P[3][i];
            C[3][i] += P[0][i] - P[1][i] + P[2][i] + P[5][i];
        }

        return mergeMatrix(C, base_size);
    }
}

std::vector<double> strassenParallel(const std::vector<double>& A, const std::vector<double>& B) {
    int base_size = static_cast<int>(A.size());

    if (base_size == 4) {
        double P1 = (A[0] + A[3]) * (B[0] + B[3]);
        double P2 = (A[2] + A[3]) * (B[0]);
        double P3 = (A[0]) * (B[1] - B[3]);
        double P4 = (A[3]) * (B[2] - B[0]);
        double P5 = (A[0] + A[1]) * (B[3]);
        double P6 = (A[2] - A[0]) * (B[0] + B[1]);
        double P7 = (A[1] - A[3]) * (B[2] + B[3]);

        std::vector<double> C(4);
        C[0] = P1 + P4 - P5 + P7;
        C[1] = P3 + P5;
        C[2] = P2 + P4;
        C[3] = P1 - P2 + P3 + P6;

        return C;
    } else {
        std::vector<std::vector<double>> subA = splitMatrix(A);
        std::vector<std::vector<double>> subB = splitMatrix(B);
        int split_size = static_cast<int>(subA[0].size());
        std::vector<std::vector<double>> P(7);

        tbb::parallel_invoke(
            [&]{ P[0] = strassen(sumOrSub(true, subA[0], subA[3]), sumOrSub(true, subB[0], subB[3])); },
            [&]{ P[1] = strassen(sumOrSub(true, subA[2], subA[3]), subB[0]); },
            [&]{ P[2] = strassen(subA[0], sumOrSub(false, subB[1], subB[3]));},
            [&]{ P[3] = strassen(subA[3], sumOrSub(false, subB[2], subB[0])); },
            [&]{ P[4] = strassen(sumOrSub(true, subA[0], subA[1]), subB[3]); },
            [&]{ P[5] = strassen(sumOrSub(false, subA[2], subA[0]), sumOrSub(true, subB[0], subB[1])); },
            [&]{ P[6] = strassen(sumOrSub(false, subA[1], subA[3]), sumOrSub(true, subB[2], subB[3])); });

        std::vector<std::vector<double>> C(4);

        for (int i = 0; i < 4; ++i) {
            std::vector<double> c(split_size);
            C[i] = c;
        }

        for (int i = 0; i < split_size; ++i) {
            C[0][i] += P[0][i] + P[3][i] - P[4][i] + P[6][i];
            C[1][i] += P[2][i] + P[4][i];
            C[2][i] += P[1][i] + P[3][i];
            C[3][i] += P[0][i] - P[1][i] + P[2][i] + P[5][i];
        }

        return mergeMatrix(C, base_size);
    }
}

std::vector<double> getStrassenSequence(const std::vector<double>& A, const std::vector<double>& B,
                                        int m1, int n1, int m2, int n2) {
    int s = getNewSize(m1, n1, m2, n2);
    std::vector<double> a = appendZeros(A, m1, n1, s);
    std::vector<double> b = appendZeros(B, m2, n2, s);

    return strassen(a, b);
}

std::vector<double> getStrassenParallel(const std::vector<double>& A, const std::vector<double>& B,
                                        int m1, int n1, int m2, int n2) {
    int s = getNewSize(m1, n1, m2, n2);
    std::vector<double> a = appendZeros(A, m1, n1, s);
    std::vector<double> b = appendZeros(B, m2, n2, s);

    return strassenParallel(a, b);
}
