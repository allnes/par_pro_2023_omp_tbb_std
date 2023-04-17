// Copyright 2023 Zbruev Denis
#include <limits>
#include <random>
#include <set>
#include "../../../modules/task_2/zbruev_d_matrix_crs_complex/crs_complex.h"

bool equalZero(const std::complex<double>& a) {
    return std::abs(a) < std::numeric_limits<double>::epsilon();
}

SparseMatrix::SparseMatrix(int _size) {
    size = _size;
}

SparseMatrix::SparseMatrix(const SparseMatrix& a) : size(a.size),
values(a.values),
cols(a.cols),
pointers(a.pointers) {}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& a) {
    if (this == &a) return *this;
    size = a.size;
    values = a.values;
    cols = a.cols;
    pointers = a.pointers;
    return *this;
}

SparseMatrix::SparseMatrix(const std::vector<std::complex<double>>& a, int n) {
    size = n;
    pointers.push_back(0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (equalZero(a[i * n + j])) continue;
            values.push_back(a[i * n + j]);
            cols.push_back(j);
        }
        pointers.push_back(static_cast<int>(cols.size()));
    }
}

std::vector<std::complex<double>> SparseMatrix::getValues() const {
    return values;
}

std::vector<int> SparseMatrix::getCols() const {
    return cols;
}

std::vector<int> SparseMatrix::getPointers() const {
    return pointers;
}

int SparseMatrix::getSize() const {
    return size;
}

void SparseMatrix::setSize(const int size) {
    this->size = size;
}

void SparseMatrix::setValues(const std::vector<std::complex<double>>& val) {
    values = val;
}

void SparseMatrix::setCols(const std::vector<int>& col) {
    cols = col;
}

void SparseMatrix::setPointers(const std::vector<int>& pointers) {
    this->pointers = pointers;
}

std::vector<std::complex<double>> SparseMatrix::getDenseMatrix() const {
    std::vector<std::complex<double>> ans(
        size * size,
        std::complex<double>(0, 0));
    for (int row = 0; row < size; ++row) {
        for (int j = pointers[row]; j < pointers[row + 1]; ++j) {
            ans[row * size + cols[j]] = values[j];
        }
    }
    return ans;
}

SparseMatrix SparseMatrix::transposition() const {
    SparseMatrix a(size);
    std::vector<std::vector<int>> helpCols(size);
    std::vector<std::vector<std::complex<double>>> helpValues(size);
    for (int row = 0; row < size; ++row) {
        for (int j = pointers[row]; j < pointers[row + 1]; ++j) {
            helpCols[cols[j]].push_back(row);
            helpValues[cols[j]].push_back(values[j]);
        }
    }
    a.pointers.push_back(0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < static_cast<int>(helpCols[i].size()); ++j) {
            a.values.push_back(helpValues[i][j]);
            a.cols.push_back(helpCols[i][j]);
        }
        a.pointers.push_back(
            a.pointers.back() + static_cast<int>(helpCols[i].size()));
    }
    return a;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& a) {
    if (size != a.getSize()) {
        throw(std::string)"Wrong matrix sizes";
    }
    SparseMatrix ans(size);
    ans.pointers.push_back(0);
    SparseMatrix a_t = a.transposition();
    auto a_t_values = a_t.getValues();
    auto a_t_cols = a_t.getCols();
    auto a_t_pointers = a_t.getPointers();
    std::vector<int> used(size, -1);
    std::complex<double> cur(0, 0);
    for (int row1 = 0; row1 < size; ++row1) {
        for (int row2 = 0; row2 < size; ++row2) {
            used.assign(size, -1);
            cur = { 0, 0 };
            for (int i = pointers[row1]; i < pointers[row1 + 1]; ++i) {
                used[cols[i]] = i;
            }
            for (int i = a_t_pointers[row2]; i < a_t_pointers[row2 + 1]; ++i) {
                if (used[a_t_cols[i]] == -1) continue;
                cur += values[used[a_t_cols[i]]] * a_t_values[i];
            }
            if (!equalZero(cur)) {
                ans.cols.emplace_back(row2);
                ans.values.emplace_back(cur);
            }
        }
        ans.pointers.emplace_back(static_cast<int>(ans.values.size()));
    }
    return ans;
}

SparseMatrix SparseMatrix::openMPMultiplication(const SparseMatrix& a) {
    if (size != a.getSize()) {
        throw(std::string)"Wrong matrix sizes";
    }
    SparseMatrix a_t = a.transposition();
    auto a_t_values = a_t.getValues();
    auto a_t_cols = a_t.getCols();
    auto a_t_pointers = a_t.getPointers();
    std::vector<std::vector<int>> parallel_columns(size);
    std::vector<std::vector<std::complex<double>>> parallel_values(size);
    std::vector<int> used(size, -1);
    std::complex<double> cur(0, 0);
#pragma omp parallel
    {
#pragma omp for private(used, cur) schedule(static)
        for (int row1 = 0; row1 < size; ++row1) {
            for (int row2 = 0; row2 < size; ++row2) {
                used.assign(size, -1);
                cur = { 0, 0 };
                for (int i = pointers[row1]; i < pointers[row1 + 1]; ++i) {
                    used[cols[i]] = i;
                }
                for (int i = a_t_pointers[row2];
                    i < a_t_pointers[row2 + 1];
                    ++i) {
                    if (used[a_t_cols[i]] == -1) continue;
                    cur += values[used[a_t_cols[i]]] * a_t_values[i];
                }
                if (!equalZero(cur)) {
                    parallel_columns[row1].emplace_back(row2);
                    parallel_values[row1].emplace_back(cur);
                }
            }
        }
    }
    SparseMatrix ans(size);
    ans.pointers.emplace_back(0);
    for (int i = 0; i < size; ++i) {
        std::copy(parallel_columns[i].begin(),
            parallel_columns[i].end(),
            std::back_inserter(ans.cols));
        std::copy(parallel_values[i].begin(),
            parallel_values[i].end(),
            std::back_inserter(ans.values));
        ans.pointers.emplace_back(
            ans.pointers.back() +
            static_cast<int>(parallel_columns[i].size()));
    }
    return ans;
}

SparseMatrix generateRandomSparseMatrix(const int size,
    const int nonZeroElementsInEveryRow) {
    if (nonZeroElementsInEveryRow > size) {
        throw(std::string)"Wrong input arguments";
    }
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    SparseMatrix ans;
    ans.setSize(size);
    std::vector<std::complex<double>> val;
    std::vector<int> cols, pointers;
    pointers.push_back(0);
    for (int row = 0; row < size; ++row) {
        std::set<int> generatedCols;
        while (static_cast<int>(generatedCols.size()) <
            nonZeroElementsInEveryRow) {
            generatedCols.insert(gen() % size);
        }
        for (auto& i : generatedCols) {
            cols.push_back(i);
            val.push_back(std::complex<double>(
                static_cast<double>(gen()) / std::numeric_limits<int>::max(),
                static_cast<double>(gen()) / std::numeric_limits<int>::max()));
        }
        pointers.push_back(static_cast<int>(cols.size()));
    }
    ans.setPointers(pointers);
    ans.setCols(cols);
    ans.setValues(val);
    return ans;
}

std::vector<std::complex<double>>
stupidDenseMultiplication(const std::vector<std::complex<double>>& a,
    const std::vector<std::complex<double>>& b,
    const int size) {
    if (a.size() != size * size || b.size() != size * size) {
        throw(std::string)"Wrong size of matrices";
    }
    std::vector<std::complex<double>> ans(size * size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                ans[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
    return ans;
}
