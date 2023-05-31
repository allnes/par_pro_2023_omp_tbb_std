// Copyright 2023 Varyzgin Dmitry
#include <vector>
#include <random>
#include "../../../modules/task_1/varyzgin_d_strassen/strassen.h"

std::vector<double> getRandomMatrix(int m, int n) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<double> vec(m * n);
    for (int i = 0; i < m * n; i++) { vec[i] = static_cast<double>(gen() % 100 + 1); }
    return vec;
}

int getNewSize(int m1, int n1, int m2, int n2) {
    int max = std::max(std::max(m1, n1), std::max(m2, n2));
    int n = 1;
    for (; max > n; n*=2) {}
    return n;
}

std::vector<double> appendZeros(const std::vector<double>& mat, int m, int n, int new_size) {
    std::vector<double> result((new_size) * (new_size));

    for (int i = 0, j = 0; i < result.size(); ++i) {
        if (i % new_size < n && j < m * n) {
            result[i] = mat[j++];
        } else {
            result[i] = 0;
        }
    }

    return result;
}

std::vector<double> sumMatrix(bool isSum, const std::vector<double>& mat1, const std::vector<double>& mat2) {
    std::vector<double> result(mat1.size());

    for (int i = 0; i < mat1.size(); ++i) {
        result[i] = isSum ? mat1[i] + mat2[i] : mat1[i] - mat2[i];
    }

    return result;
}

std::vector<std::vector<double>> splitMatrix(const std::vector<double>& mat) {
    std::vector<std::vector<double>> result(4);
    int n = static_cast<int>(sqrt(mat.size()));
    int split_n = n / 2;

    for (int i = 0; i < 4; ++i) {
        std::vector<double> subMat(split_n * split_n);
        result[i] = subMat;
    }

    for (int i = 0; i < mat.size() / 2; ++i) {
        int row = i / n;
        if (i % n >= split_n) {
            result[1][row * split_n + i % split_n] = mat[i];
        } else {
            result[0][row * split_n + i % split_n] = mat[i];
        }
    }
    for (int i = static_cast<int>(mat.size() / 2); i < mat.size(); ++i) {
        int row = i / n - n / 2;
        if (i % n >= split_n) {
            result[3][row * split_n + i % split_n] = mat[i];
        } else {
            result[2][row * split_n + i % split_n] = mat[i];
        }
    }

    return result;
}

std::vector<double> getStrassenSequence(const std::vector<double>& matA, const std::vector<double>& matB) {
    if (matA.size() == 4) {
        double P1 = (matA[0] + matA[3]) * (matB[0] + matB[3]);
        double P2 = (matA[2] + matA[3]) * (matB[0]);
        double P3 = (matA[0]) * (matB[1] - matB[3]);
        double P4 = (matA[3]) * (matB[2] - matB[0]);
        double P5 = (matA[0] + matA[1]) * (matB[3]);
        double P6 = (matA[2] - matA[0]) * (matB[0] + matB[1]);
        double P7 = (matA[1] - matA[3]) * (matB[2] + matB[3]);

        std::vector<double> matC(4);
        matC[0] = P1 + P4 - P5 + P7;
        matC[1] = P3 + P5;
        matC[2] = P2 + P4;
        matC[3] = P1 - P2 + P3 + P6;

        return matC;
    } else {
        std::vector<std::vector<double>> subMatsA(4);
        std::vector<std::vector<double>> subMatsB(4);

        subMatsA = splitMatrix(matA);
        subMatsB = splitMatrix(matB);

        std::vector<double> P1 = getStrassenSequence(sumMatrix(true, subMatsA[0], subMatsA[3]),
                                                     sumMatrix(true, subMatsB[0], subMatsB[3]) );
        std::vector<double> P2 = getStrassenSequence(sumMatrix(true, subMatsA[2], subMatsA[3]),
                                                     subMatsB[0]);
        std::vector<double> P3 = getStrassenSequence(subMatsA[0],
                                                     sumMatrix(false, subMatsB[1], subMatsB[3]));
        std::vector<double> P4 = getStrassenSequence(subMatsA[3], sumMatrix(false, subMatsB[2],
                                                                            subMatsB[0]));
        std::vector<double> P5 = getStrassenSequence(sumMatrix(true, subMatsA[0], subMatsA[1]),
                                                     subMatsB[3]);
        std::vector<double> P6 = getStrassenSequence(sumMatrix(false, subMatsA[2], subMatsA[0]),
                                                     sumMatrix(true, subMatsB[0], subMatsB[1]));
        std::vector<double> P7 = getStrassenSequence(sumMatrix(false, subMatsA[1], subMatsA[3]),
                                                     sumMatrix(true, subMatsB[2], subMatsB[3]));

        std::vector<double> C11(P1.size());
        std::vector<double> C12(P1.size());
        std::vector<double> C21(P1.size());
        std::vector<double> C22(P1.size());

        for (int i = 0; i < P1.size(); ++i) {
            C11[i] += P1[i] + P4[i] - P5[i] + P7[i];
            C12[i] += P3[i] + P5[i];
            C21[i] += P2[i] + P4[i];
            C22[i] += P1[i] - P2[i] + P3[i] + P6[i];
        }

        std::vector<double> matC(matA.size());

        int n = static_cast<int>(sqrt(matC.size()));
        int split_n = n / 2;

        for (int i = 0; i < matC.size() / 2; ++i) {
            int row = i / n;
            if (i % n >= split_n) {
                matC[i] = C12[row * split_n + i % split_n];
            } else {
                matC[i] = C11[row * split_n + i % split_n];
            }
        }
        for (int i = static_cast<int>(matC.size() / 2); i < matC.size(); ++i) {
            int row = i / n - n / 2;
            if (i % n >= split_n) {
                matC[i] = C22[row * split_n + i % split_n];
            } else {
                matC[i] = C21[row * split_n + i % split_n];
            }
        }

        return matC;
    }
}