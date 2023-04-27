// Copyright 2023 Makarov Mikhail
#include "../../../modules/task_2/makarov_m_kanons_method/kanons_method.h"

Matrix CreateRandomMatrix(const int n) {
    if (n <= 0) throw std::invalid_argument("matrix size n should be positive");

    Matrix mat(n, Vector(n, 0));

    std::uniform_real_distribution<double> dis(0, 100);
    std::mt19937 gen;
    std::random_device dev;
    gen.seed(dev());

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = dis(gen);
        }
    }
    return mat;
}

Matrix MultUsual(const Matrix &A, const Matrix &B) {
    if (A[0].size() != B.size())
        throw std::invalid_argument(
            "A and B have incorrect sizes for multiplication");

    size_t n = A[0].size();
    size_t m = A.size();
    size_t l = B[0].size();
    Matrix result(m, std::vector<double>(l, 0));

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < l; j++) {
            for (size_t k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

bool ValuesNear(const double &a, const double &b, const double &eps) {
    return std::fabs(a - b) < eps;
}

bool MatricesNear(const Matrix &A, const Matrix &B) {
    if (A[0].size() != B[0].size() || A.size() != B.size()) {
        return false;
    }

    bool areNear = true;

    for (size_t i = 0; i < A.size(); ++i) {
        if (areNear == false) {
            break;
        }
        for (size_t j = 0; j < A[0].size(); ++j) {
            if (!ValuesNear(A[i][j], B[i][j], 0.00001)) {
                areNear = false;
                break;
            }
        }
    }

    return areNear;
}

Matrix MultBlock(const Matrix &A, const Matrix &B, const int &blockSize) {
    if (A[0].size() != B.size()) {
        throw std::invalid_argument(
            "A and B have incorrect sizes for multiplication");
    }
    int temp = blockSize;
    if (temp > static_cast<int>(A.size())) {
        throw std::invalid_argument("blockSize is incorrect");
    }

    int n = A[0].size();
    int jjMin, kkMin;
    Matrix result(n, std::vector<double>(n, 0));

    for (int jj = 0; jj < n; jj += blockSize) {
        jjMin = std::min(jj + blockSize, n);
        for (int kk = 0; kk < n; kk += blockSize) {
            kkMin = std::min(kk + blockSize, n);
            for (int i = 0; i < n; ++i) {
                for (int k = kk; k < kkMin; ++k) {
                    for (int j = jj; j < jjMin; ++j) {
                        result[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }

    return result;
}

Matrix CannonAlg(const Matrix &A, const Matrix &B, const int &numThreads) {
    if (A[0].size() != B.size())
        throw std::invalid_argument(
            "A and B have incorrect sizes for multiplication");
    if (numThreads <= 0)
        throw std::invalid_argument("numThreads cannot be <= 0");

    int n = A[0].size();
    int nOld = n;
    int p = std::sqrt(numThreads);

    Matrix tA = A;
    Matrix tB = B;

    if (n % p != 0) {
        while (n % p != 0) {
            tA.push_back(std::vector<double>(nOld, 0));
            tB.push_back(std::vector<double>(nOld, 0));
            ++n;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - nOld; ++j) {
                tA[i].push_back(0);
                tB[i].push_back(0);
            }
        }
    }
    int blockSize = n / p;
    Matrix result(n, std::vector<double>(n));

    #pragma omp parallel num_threads(p * p)
    {
        int threadi = omp_get_thread_num() / p;
        int threadj = omp_get_thread_num() % p;
        int blockiA = 0, blockjA = 0, blockiB = 0, blockjB = 0;

        Matrix num1(blockSize), num2(blockSize),
            numresult(blockSize, std::vector<double>(blockSize, 0));

        for (int k = 0; k < blockSize; ++k) {
            blockiA = threadi * blockSize + k;
            blockjA = ((threadj + threadi) % p) * blockSize;
            blockjB = threadj * blockSize;
            blockiB = blockjA + k;
            num1[k] = std::vector<double>(
                tA[blockiA].begin() + blockjA,
                tA[blockiA].begin() + blockjA + blockSize);
            num2[k] = std::vector<double>(
                tB[blockiB].begin() + blockjB,
                tB[blockiB].begin() + blockjB + blockSize);
        }
        for (int kk = 0; kk < p; ++kk) {
            for (int i = 0; i < blockSize; ++i) {
                for (int j = 0; j < blockSize; ++j) {
                    for (int s = 0; s < blockSize; ++s) {
                        numresult[i][j] += num1[i][s] * num2[s][j];
                    }
                }
            }

            if (kk == p - 1) {
                break;
            }

            for (int k = 0; k < blockSize; ++k) {
                int iA = threadi * blockSize + k;
                int jA = ((blockjA / blockSize + kk + 1) % p) * blockSize;
                int iB =
                    ((blockiB / blockSize + kk + 1) % p) * blockSize + k;
                int jB = threadj * blockSize;
                num1[k] = std::vector<double>(
                    tA[iA].begin() + jA, tA[iA].begin() + jA + blockSize);
                num2[k] = std::vector<double>(
                    tB[iB].begin() + jB, tB[iB].begin() + jB + blockSize);
            }
        }
        for (int i = 0; i < blockSize; ++i) {
            for (int j = 0; j < blockSize; ++j) {
                int ii = i + threadi * blockSize;
                int jj = j + threadj * blockSize;
                result[ii][jj] = numresult[i][j];
            }
        }
        #pragma omp barrier
        if (nOld != n) {
            #pragma omp parallel for
                for (int i = 0; i < nOld; ++i) {
                    result[i].resize(nOld);
                }
        }
    }
    result.resize(nOld);
    return result;
}
