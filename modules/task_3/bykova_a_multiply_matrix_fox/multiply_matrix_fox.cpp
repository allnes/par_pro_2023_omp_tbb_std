// Copyright 2023 Bykova Aleksandra
#include "../../../modules/task_3/bykova_a_multiply_matrix_fox/multiply_matrix_fox.h"

#include <math.h>
#include <tbb/tbb.h>
#include <random>
#include <vector>
bool canMultiplicate(const matrix &a, const matrix &b) {
    if (a.empty() || b.empty()) return false;
    for (uint i = 0; i < a.size(); i++) {
        if (a[i].size() != b.size()) return false;
    }
    return true;
}

void prepareOutMatrix(matrix *matrixOut, uint sizeRow, uint sizeCol) {
    if ((*matrixOut).size() != sizeRow) (*matrixOut).resize(sizeRow);
    for (uint i = 0; i < (*matrixOut).size(); i++) {
        if ((*matrixOut)[i].size() != sizeCol) (*matrixOut)[i].resize(sizeCol);
        for (uint j = 0; j < (*matrixOut)[i].size(); j++) {
            (*matrixOut)[i][j] = 0;
        }
    }
}

bool simpleMaxtrixMultiply(const matrix &a, const matrix &b, matrix *out) {
    if (!canMultiplicate(a, b)) return false;
    prepareOutMatrix(out, a.size(), b.size());
    for (uint i = 0; i < a.size(); i++) {  // ixj j*k
        for (uint k = 0; k < b[0].size(); k++) {
            for (uint j = 0; j < b.size(); j++) {
                (*out)[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return true;
}

bool initMatrixRand(matrix *a, uint sizeRow, uint sizeCol) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1000.0, 1000.0);

    if ((*a).size() != sizeRow) (*a).resize(sizeRow);

    for (uint i = 0; i < sizeRow; i++) {
        if ((*a)[i].size() != sizeCol) (*a)[i].resize(sizeCol);

        for (uint j = 0; j < sizeCol; j++) {
            (*a)[i][j] = dis(gen);
        }
    }
    return true;
}

bool isSquareMatrix(const matrix &a, const matrix &b) {
    if (a.empty() || b.empty()) return false;
    if (a.size() != b.size()) return false;
    for (uint i = 0; i < a.size(); i++) {
        if (a[i].size() != a.size()) {
            return false;
        }
        if (a[i].size() != b[i].size()) return false;
    }
    return true;
}

class TbbFunctorFoxAlg {
 private:
    static uint threadCounter;
    static tbb::mutex myMutex;
    const matrix &a;
    const matrix &b;
    matrix *out;

 public:
    static void SetToZerothreadCounter() {
       threadCounter = 0;
    }
    TbbFunctorFoxAlg(const matrix &a_, const matrix &b_, matrix *out_)
        : a(a_), b(b_), out(out_) {}
    void operator()(const tbb::blocked_range<int> &iter) const {
        uint size = a.size();
        uint grid = sqrt(NTHREADS);  // NTHREADS perfect square
        uint blockSize = size / grid;

        tbb::mutex::scoped_lock lock;
        lock.acquire(myMutex);
        uint thread_coord1 = threadCounter / grid;
        uint thread_coord2 = threadCounter % grid;
        threadCounter++;
        lock.release();

        uint k1 = thread_coord1 * blockSize;
        uint k2 = thread_coord2 * blockSize;

        std::vector<double> aBlock(blockSize, 0.0);
          matrix bBlock(100);
            matrix cBlock(100);
            for (uint i = 0; i < 100; i++) {
                bBlock[i].reserve(1000);
                cBlock[i].reserve(1000);
            }
        prepareOutMatrix(&cBlock, blockSize, blockSize);
        prepareOutMatrix(&bBlock, blockSize, blockSize);
        if (size % grid == 0) {
            for (int l = iter.begin(); l != iter.end(); l++) {
                for (uint i = 0; i < size; i++) {  // формирование обработка блоков
                    for (uint j = 0; j < blockSize; j++) {  // заполнение блоков матрицы
                        uint s = (i + j + k1) % size;
                        aBlock[j] = a[j + k1][s];
                        for (uint k = 0; k < blockSize; k++) {
                            bBlock[j][k] = b[s][k + k2];
                        }
                    }
                    for (uint j = 0; j < blockSize; j++) {  // Compute C
                        for (uint k = 0; k < blockSize; k++) {
                            cBlock[j][k] += aBlock[j] * bBlock[j][k];
                        }
                    }
                }
                for (uint i = 0; i < blockSize; i++) {
                    for (uint j = 0; j < blockSize; j++) {
                        (*out)[i + k1][j + k2] = cBlock[i][j];
                    }
                }
            }
        }
    }
};

tbb::mutex TbbFunctorFoxAlg::myMutex;
uint TbbFunctorFoxAlg::threadCounter = 0;
bool algFoxMatrixMultiplyPar(const matrix &a, const matrix &b, matrix *out) {
    if (!isSquareMatrix(a, b)) return false;
    uint size = a.size();
    if ((size * size) % NTHREADS != 0)
        throw std::runtime_error(
            "size of matrix should devided by number of threads without "
            "reminder");
    TbbFunctorFoxAlg::SetToZerothreadCounter();
    prepareOutMatrix(out, size, size);
    TbbFunctorFoxAlg tbbHandler(a, b, out);
    tbb::parallel_for(tbb::blocked_range<int>(0, NTHREADS, 1), tbbHandler);

    return true;
}

bool algFoxMatrixMultiplySeq(const matrix &a, const matrix &b, matrix *out) {
    uint numThread = 1;
    if (!isSquareMatrix(a, b)) return false;
    uint size = a.size();
    uint grid = std::sqrt(numThread);
    uint blockSize = size / grid;
    std::vector<double> aBlock(size, 0.0);
    matrix bBlock;
    prepareOutMatrix(out, size, size);
    prepareOutMatrix(&bBlock, size, size);

    for (uint i = 0; i < blockSize; i++) {  // формирование обработка блока
        for (uint j = 0; j < blockSize; j++) {  // заполнение блоков матрицы
            uint s = (i + j) % blockSize;
            aBlock[j] = a[j][s];
            for (uint k = 0; k < blockSize; k++) {
                bBlock[j][k] = b[s][k];
            }
        }
        for (uint j = 0; j < blockSize; j++) {  // Compute C
            for (uint k = 0; k < blockSize; k++) {
                (*out)[j][k] += aBlock[j] * bBlock[j][k];
            }
        }
    }
    return true;
}
