  // Copyright 2023 Nikolaev Alexander
#include <random>
#include <algorithm>
#include "../../../modules/task_2/nikolaev_a_mult_sparse_matr_omp/sparse_matrix.h"

void printMatrix(const std::vector<std::vector<Complex>>& Pmatrix) {
    const size_t sizeRow = Pmatrix.size();
    const size_t sizeCol = Pmatrix[0].size();
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            std::cout << Pmatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

CCSMatrix GetRandomMatrix(int SizeRow, int SizeCol, int nonZero) {
    CCSMatrix mtx;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> disValue(1, 10);
    std::uniform_int_distribution<> disRowIndex(0, SizeRow - 1);
    std::uniform_int_distribution<> disColIndex(0, SizeCol - 1);
    std::vector<std::vector<Complex>> matrix(SizeRow,
                std::vector<Complex>(SizeCol));
    mtx.sizeRow = SizeRow;
    mtx.sizeCol = SizeCol;
    int row = 0;
    int col = 0;
    for (int i = 0; i < nonZero; i++) {
        row = disRowIndex(gen);
        col = disColIndex(gen);
        while (matrix[row][col] != Complex(0, 0)) {
            row = disRowIndex(gen);
            col = disColIndex(gen);
        }
        matrix[row][col] = Complex(disValue(gen), 0);
    }

    int ind = 0;
    mtx.colIndex.push_back(0);
    for (int i = 0; i < SizeCol; i++) {
        for (int j = 0; j < SizeRow; j++) {
            if (matrix[j][i] == Complex(0, 0)) {
                continue;
            }
            mtx.value.push_back(matrix[j][i]);
            mtx.rowIndex.push_back(j);
            ind++;
        }
        mtx.colIndex.push_back(ind);
    }
    mtx.countNZ = mtx.rowIndex.size();
    return mtx;
}

CCSMatrix TransposeMatrix(const CCSMatrix& A) {
    CCSMatrix AT;

    AT.sizeCol = A.sizeRow;
    AT.sizeRow = A.sizeCol;
    AT.countNZ = A.countNZ;

    std::vector<std::vector<int>> rows(A.sizeRow);
    std::vector<std::vector<Complex>> values(A.sizeRow);

    for (int i = 0; i < A.sizeCol; ++i) {
        for (int j = A.colIndex[i]; j < A.colIndex[i + 1]; ++j) {
            rows[A.rowIndex[j]].push_back(i);
            values[A.rowIndex[j]].push_back(A.value[j]);
        }
    }

    AT.colIndex.resize(AT.sizeCol + 1);
    AT.colIndex[0] = 0;

    for (int i = 0; i < AT.sizeCol; ++i) {
        AT.colIndex[i + 1] = AT.colIndex[i] + values[i].size();
        int n = values[i].size();
        for (int j = 0; j < n; ++j) {
            AT.value.push_back(values[i][j]);
            AT.rowIndex.push_back(rows[i][j]);
        }
    }
    return AT;
}

CCSMatrix GetMultiplicateSequential(const CCSMatrix& A, const CCSMatrix& B) {
    CCSMatrix C;

    C.sizeRow = A.sizeCol;
    C.sizeCol = B.sizeCol;
    C.colIndex.push_back(0);

    int NonZero = 0;

    for (int i = 0; i < A.sizeCol; ++i) {
        std::vector<int> tmp(A.sizeRow, -1);
        for (int t = A.colIndex[i]; t < A.colIndex[i + 1]; ++t) {
            int row = A.rowIndex[t];
            tmp[row] = t;
        }
        for (int j = 0; j < B.sizeCol; ++j) {
            Complex sum = 0;
            for (int k = B.colIndex[j]; k < B.colIndex[j + 1]; ++k) {
                int row = B.rowIndex[k];
                int index = tmp[row];
                if (index > -1) {
                    sum += A.value[index] * B.value[k];
                }
            }
            if (sum.real() != 0 || sum.imag() != 0) {
                C.rowIndex.push_back(j);
                C.value.push_back(sum);
                NonZero++;
            }
        }
        C.colIndex.push_back(NonZero);
    }
    C.countNZ = NonZero;

    return C;
}

CCSMatrix GetMultiplicateParallel(const CCSMatrix& A, const CCSMatrix& B) {
    CCSMatrix C;

    C.sizeRow = A.sizeCol;
    C.sizeCol = B.sizeCol;

    int i, j, k, t;
    int numThreads = 0;

    #pragma omp parallel
    {
        numThreads = omp_get_num_threads();
    }

    std::vector<std::vector<Complex>> values(numThreads);
    std::vector<std::vector<int>> rowIndex(numThreads);
    std::vector<int> countNZ(C.sizeCol + 1);

    #pragma omp parallel for private(j, k, t)
    for (i = 0; i < A.sizeCol; ++i) {
        std::vector<int> tmp(A.sizeRow, -1);
        for (t = A.colIndex[i]; t < A.colIndex[i + 1]; ++t) {
            int row = A.rowIndex[t];
            tmp[row] = t;
        }
        for (j = 0; j < B.sizeCol; ++j) {
            Complex sum = 0;
            for (k = B.colIndex[j]; k < B.colIndex[j + 1]; ++k) {
                int row = B.rowIndex[k];
                int index = tmp[row];
                if (index > -1) {
                    #pragma omp critical
                    {
                        sum += A.value[index] * B.value[k];
                    }
                }
            }
            if (sum.real() != 0 || sum.imag() != 0) {
                #pragma omp critical
                {
                    rowIndex[omp_get_thread_num()].push_back(j);
                    values[omp_get_thread_num()].push_back(sum);
                    countNZ[i]++;
                }
            }
        }
    }
    for (int i = 0; i < numThreads; i++) {
        C.value.insert(C.value.end(), values[i].begin(), values[i].end());
        C.rowIndex.insert(C.rowIndex.end(),
            rowIndex[i].begin(), rowIndex[i].end());
    }

    int NZ = 0;
    for (j = 0; j < C.sizeCol; j++) {
        int tmp = countNZ[j];
        countNZ[j] = NZ;
        NZ += tmp;
    }
    countNZ[C.sizeCol] = NZ;

    C.colIndex.insert(C.colIndex.end(), countNZ.begin(), countNZ.end());

    C.countNZ = C.value.size();

    return C;
}

CCSMatrix MatrixtoCCSMatrix(const std::vector<std::vector<Complex>>& matrix) {
    const int sizeRow = matrix.size();
    const int sizeCol = matrix[0].size();
    CCSMatrix A;
    A.sizeRow = sizeRow;
    A.sizeCol = sizeCol;
    int ind = 0;
    A.colIndex.push_back(0);

    for (int i = 0; i < sizeCol; ++i) {
        for (int j = 0; j < sizeRow; ++j) {
            if (matrix[j][i] == Complex(0, 0)) {
                continue;
            }
            A.value.push_back(matrix[j][i]);
            A.rowIndex.push_back(j);
            ind++;
        }
        A.colIndex.push_back(ind);
    }
    A.countNZ = ind;
    return A;
}
