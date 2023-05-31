// Copyright 2023 Varyzgin Dmitry
#include <vector>
#include <random>
#include "../../../modules/task_1/varyzgin_d_strassen/strassen.h"

std::vector<double> getRandomMatrix(int m, int n) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<double> vec(m * n);
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    for (int i = 0; i < m * n; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}

int getNewSize(int m1, int n1, int m2, int n2) {
    return std::max({m1, n1, m2, n2});
}

std::vector<double> appendZeros(const std::vector<double>& mat, int m, int n, int new_size) {
    std::vector<double> result(new_size * new_size, 0.0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i * new_size + j] = mat[i * n + j];
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
    int n = static_cast<int>(sqrt(mat.size()));
    int split_n = n / 2;

    std::vector<std::vector<double>> result(4, std::vector<double>(split_n * split_n));

    for (int i = 0; i < mat.size() / 2; ++i) {
        int row = i / n;
        int col = i % n;
        int subMatIndex = (col < split_n) ? 0 : 1;
        result[subMatIndex][row * split_n + col % split_n] = mat[i];
    }

    for (int i = static_cast<int>(mat.size() / 2); i < mat.size(); ++i) {
        int row = i / n - n / 2;
        int col = i % n;
        int subMatIndex = (col < split_n) ? 2 : 3;
        result[subMatIndex][row * split_n + col % split_n] = mat[i];
    }

    return result;
}

std::vector<double> getStrassenSequence(const std::vector<double>& matA, const std::vector<double>& matB) {
    if (matA.size() == 4) {
        double P1 = (matA[0] + matA[3]) * (matB[0] + matB[3]);
        double P2 = (matA[2] + matA[3]) * matB[0];
        double P3 = matA[0] * (matB[1] - matB[3]);
        double P4 = matA[3] * (matB[2] - matB[0]);
        double P5 = (matA[0] + matA[1]) * matB[3];
        double P6 = (matA[2] - matA[0]) * (matB[0] + matB[1]);
        double P7 = (matA[1] - matA[3]) * (matB[2] + matB[3]);

        std::vector<double> matC(4);
        matC[0] = P1 + P4 - P5 + P7;
        matC[1] = P3 + P5;
        matC[2] = P2 + P4;
        matC[3] = P1 - P2 + P3 + P6;

        return matC;
    } else {
        std::vector<std::vector<double>> subMatsA = splitMatrix(matA);
        std::vector<std::vector<double>> subMatsB = splitMatrix(matB);

        std::vector<double> P1 = getStrassenSequence(sumMatrix(true, subMatsA[0], subMatsA[3]),
                                                     sumMatrix(true, subMatsB[0], subMatsB[3]));
        std::vector<double> P2 = getStrassenSequence(sumMatrix(true, subMatsA[2], subMatsA[3]),
                                                     subMatsB[0]);
        std::vector<double> P3 = getStrassenSequence(subMatsA[0],
                                                     sumMatrix(false, subMatsB[1], subMatsB[3]));
        std::vector<double> P4 = getStrassenSequence(subMatsA[3],
                                                     sumMatrix(false, subMatsB[2], subMatsB[0]));
        std::vector<double> P5 = getStrassenSequence(sumMatrix(true, subMatsA[0], subMatsA[1]),
                                                     subMatsB[3]);
        std::vector<double> P6 = getStrassenSequence(sumMatrix(false, subMatsA[2], subMatsA[0]),
                                                     sumMatrix(true, subMatsB[0], subMatsB[1]));
        std::vector<double> P7 = getStrassenSequence(sumMatrix(false, subMatsA[1], subMatsA[3]),
                                                     sumMatrix(true, subMatsB[2], subMatsB[3]));

        std::vector<double> C11 = sumMatrix(true, sumMatrix(false, sumMatrix(true, P1, P4), P7), P5);
        std::vector<double> C12 = sumMatrix(true, P3, P5);
        std::vector<double> C21 = sumMatrix(true, P2, P4);
        std::vector<double> C22 = sumMatrix(true, sumMatrix(true, sumMatrix(true, P1, P3), P6), P7);

        int n = static_cast<int>(sqrt(matA.size()));
        int split_n = n / 2;
        std::vector<double> matC(matA.size());

        for (int i = 0; i < matA.size() / 2; ++i) {
            int row = i / n;
            int col = i % n;
            int subMatIndex = (col < split_n) ? 0 : 1;
            matC[i] = (col < split_n) ? C11[row * split_n + col] : C12[row * split_n + col % split_n];
        }

        for (int i = static_cast<int>(matA.size() / 2); i < matA.size(); ++i) {
            int row = (i / n) - split_n;
            int col = i % n;
            int subMatIndex = (col < split_n) ? 2 : 3;
            matC[i] = (col < split_n) ? C21[row * split_n + col] : C22[row * split_n + col % split_n];
        }

        return matC;
    }
}
