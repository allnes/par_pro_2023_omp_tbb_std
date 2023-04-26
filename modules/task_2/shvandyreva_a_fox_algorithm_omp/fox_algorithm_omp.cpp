// Copyright 2023 Shvandyreva Alina
#include <omp.h>
#include "../../../modules/task_2/shvandyreva_a_fox_algorithm_omp/fox_algorithm_omp.h"

static matrix sum_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(A[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

static matrix multiply_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(B[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < A[0].size(); k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

matrix generate_matrix(size_t x_size, size_t y_size) {
    matrix result(y_size, std::vector<double>(x_size));
    std::random_device device;
    std::mt19937 mt(device());
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            result[y][x] = 0.1 * (mt() % 100);
        }
    }
    return result;
}

matrix generate_identity_matrix(size_t size) {
    matrix result(size, std::vector<double>(size));
    for (int i = 0; i < size; i++) {
        result[i][i] = 1;
    }
    return result;
}

matrix seq_multiply(const matrix& A, const matrix& B) {
    return multiply_block(A, B);
}

matrix omp_multiply(const matrix& A, const matrix& B, int thread_by_dim) {
    int td = thread_by_dim < 1 ? 1 : thread_by_dim;
    if (td == 1) {
        return multiply_block(A, B);
    }
    matrix result(A.size(), std::vector<double>(B[0].size()));

    int p = A.size() / td;  // portion
#pragma omp parallel num_threads(td * td)
    {
        int tid = omp_get_thread_num();
        int x = tid % td;
        int y = tid / td;

        int a_x = y + x;
        int a_y = y;

        int b_x = x;
        int b_y = y + x;

        if (a_x >= td) {
            a_x -= td;
        }
        if (b_y >= td) {
            b_y -= td;
        }

        for (int iter = 0; iter < td; iter++) {
            for (int i = 0; i < p; i++) {
                for (int j = 0; j < p; j++) {
                    for (int k = 0; k < p; k++) {
                        result[i + y * p][j + x * p]
                            += A[i + a_y * p][k + a_x * p] * B[k + b_y * p][j + b_x * p];
                    }
                }
            }

            if (++a_x >= td) {
                a_x = 0;
            }
            if (++b_y >= td) {
                b_y = 0;
            }
        }
#pragma omp barrier
    }
    return result;
}
