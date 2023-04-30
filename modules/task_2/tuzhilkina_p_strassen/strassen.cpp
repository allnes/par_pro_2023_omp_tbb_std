// Copyright 2023 Tuzhilkina Polina
#include "../../../modules/task_2/tuzhilkina_p_strassen/strassen.h"

std::vector<double> genRandomVector(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 9.0);

    std::vector<double> vec(n);

    for (int i = 0; i < n; i++) {
        vec[i] = dis(gen);
    }

    return vec;
}

void printMatrix(const std::vector<double>& Mat, std::size_t n) {
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            std::cout << Mat[i * n + j] << " ";
        }
        std::cout << '\n';
    }
}

// Matrices A and B have sizes n x n and are represented as vectors
std::vector<double> usualMultiply(const std::vector<double>& A,
                               const std::vector<double>& B, int n) {
    std::vector<double> C(n * n, 0);

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            for (std::size_t k = 0; k < n; k++) {
                C[i * n + j] += A.at(i * n + k) * B.at(k * n + j);
            }
        }
    }
    return C;
}

std::vector<double> add(std::vector<double> A, std::vector<double> B) {
    std::vector<double> C(A.size());
    for (int i = 0; i < A.size(); i++) C[i] = A[i] + B[i];
    return C;
}

std::vector<double> sub(const std::vector<double>& A, const std::vector<double>& B) {
    std::vector<double> C(A.size());
    for (int i = 0; i < A.size(); i++) C[i] = A[i] - B[i];
    return C;
}

// Matrices A and B have sizes n x n and are represented as vectors
std::vector<double> seqStrassenMultiply(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n) {
    // Basic case
    if (n == 1) {
        std::vector<double> C = {A[0] * B[0]};
        return C;
    }

    // Splitting matrices into submatrices
    std::size_t m = n / 2;
    std::vector<double> A11(m * m), A12(m * m), A21(m * m), A22(m * m);
    std::vector<double> B11(m * m), B12(m * m), B21(m * m), B22(m * m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i * m + j] = A[i * n + j];
            A12[i * m + j] = A[i * n + (j + m)];
            A21[i * m + j] = A[(i + m) * n + j];
            A22[i * m + j] = A[(i + m) * n + (j + m)];
            B11[i * m + j] = B[i * n + j];
            B12[i * m + j] = B[i * n + (j + m)];
            B21[i * m + j] = B[(i + m) * n + j];
            B22[i * m + j] = B[(i + m) * n + (j + m)];
        }
    }

    // Recursive calls for submatrices
    std::vector<double> P1 = seqStrassenMultiply(A11, sub(B12, B22), m);
    std::vector<double> P2 = seqStrassenMultiply(add(A11, A12), B22, m);
    std::vector<double> P3 = seqStrassenMultiply(add(A21, A22), B11, m);
    std::vector<double> P4 = seqStrassenMultiply(A22, sub(B21, B11), m);
    std::vector<double> P5 = seqStrassenMultiply(add(A11, A22), add(B11, B22), m);
    std::vector<double> P6 = seqStrassenMultiply(sub(A12, A22), add(B21, B22), m);
    std::vector<double> P7 = seqStrassenMultiply(sub(A11, A21), add(B11, B12), m);

    // Result calculation
    std::vector<double> C(n * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i * n + j] =
                P5[i * m + j] + P4[i * m + j] - P2[i * m + j] + P6[i * m + j];
            C[i * n + (j + m)] = P1[i * m + j] + P2[i * m + j];
            C[(i + m) * n + j] = P3[i * m + j] + P4[i * m + j];
            C[(i + m) * n + (j + m)] =
                P5[i * m + j] + P1[i * m + j] - P3[i * m + j] - P7[i * m + j];
        }
    }

    return C;
}


std::vector<double> ompStrassenMultiply(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n) {
    // Basic case
    if (n == 1) {
        std::vector<double> C = {A[0] * B[0]};
        return C;
    }

    // Splitting matrices into submatrices
    std::size_t m = n / 2;
    std::vector<double> A11(m * m), A12(m * m), A21(m * m), A22(m * m);
    std::vector<double> B11(m * m), B12(m * m), B21(m * m), B22(m * m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i * m + j] = A[i * n + j];
            A12[i * m + j] = A[i * n + (j + m)];
            A21[i * m + j] = A[(i + m) * n + j];
            A22[i * m + j] = A[(i + m) * n + (j + m)];
            B11[i * m + j] = B[i * n + j];
            B12[i * m + j] = B[i * n + (j + m)];
            B21[i * m + j] = B[(i + m) * n + j];
            B22[i * m + j] = B[(i + m) * n + (j + m)];
        }
    }

    std::vector<double> P1, P2, P3, P4, P5, P6, P7;

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                P1 = seqStrassenMultiply(A11, sub(B12, B22), m);
            }
            #pragma omp section
            {
                P2 = seqStrassenMultiply(add(A11, A12), B22, m);
            }
            #pragma omp section
            {
                P3 = seqStrassenMultiply(add(A21, A22), B11, m);
            }
            #pragma omp section
            {
                P4 = seqStrassenMultiply(A22, sub(B21, B11), m);
            }
            #pragma omp section
            {
                P5 = seqStrassenMultiply(add(A11, A22), add(B11, B22), m);
            }
            #pragma omp section
            {
                P6 = seqStrassenMultiply(sub(A12, A22), add(B21, B22), m);
            }
            #pragma omp section
            {
                P7 = seqStrassenMultiply(sub(A11, A21), add(B11, B12), m);
            }
        }
    }

    // Result calculation
    std::vector<double> C(n * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i * n + j] =
                P5[i * m + j] + P4[i * m + j] - P2[i * m + j] + P6[i * m + j];
            C[i * n + (j + m)] = P1[i * m + j] + P2[i * m + j];
            C[(i + m) * n + j] = P3[i * m + j] + P4[i * m + j];
            C[(i + m) * n + (j + m)] =
                P5[i * m + j] + P1[i * m + j] - P3[i * m + j] - P7[i * m + j];
        }
    }

    return C;
}
