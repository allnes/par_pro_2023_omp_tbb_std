// Copyright 2023 Raschetnov Alexei

#include "../../../modules/task_2/raschetnov_a_ccs_double_matrix/ccs_double_matrix.h"
#include <omp.h>
#include <utility>

SparseMatrix SparseMatrix::multiply(const SparseMatrix& matrix) {
    SparseMatrix result(row, matrix.col);
    result.pointer.push_back(0);
    for (int i = 1; i < pointer.size(); i++) {
        int counter = 0;
        std::vector<double> values_a(values.begin() + pointer[i - 1], values.begin() + pointer[i]);
        std::vector<double> row_a(rows.begin() + pointer[i - 1], rows.begin() + pointer[i]);
        #pragma omp parallel for schedule(static)
        for (int j = 1; j < matrix.pointer.size(); j++) {
            std::vector<double> values_b(matrix.values.begin() + matrix.pointer[j - 1],
                                         matrix.values.begin() + matrix.pointer[j]);
            std::vector<double> row_b(matrix.rows.begin() + matrix.pointer[j - 1],
                                      matrix.rows.begin() + matrix.pointer[j]);
            int k = 0;
            int s = 0;
            double sum = 0;
            while (k < values_a.size() && s < values_b.size()) {
                if (row_a[k] == row_b[s]) {
                    sum += values_a[k] * values_b[s];
                    k++;
                    s++;
                } else if (row_a[k] > row_b[s]) {
                    s++;
                } else {
                    k++;
                }
            }
            #pragma omp critical
            if (sum) {
                result.values.push_back(sum);
                counter++;
                result.rows.push_back(j - 1);
            }
        }
        result.pointer.push_back(result.pointer.back() + counter);
    }
    result.transpose();
    return result;
}

bool SparseMatrix::is_empty() {
    if (!values.size())
        return true;
    return false;
}

SparseMatrix& SparseMatrix::transpose() {
    if (is_empty())
        return *this;

    std::vector<int> row_indexes;
    std::vector<int> tmp_rows(row + 1);

    for (int i = 1; i < col + 1; i++) {
        std::vector<double> values_a(values.begin() + pointer[i - 1], values.begin() + pointer[i]);

        for (int j = 0; j < values_a.size(); j++)
            row_indexes.push_back(i - 1);
    }

    for (int i = 0; i < rows.size(); i++)
        tmp_rows[rows[i] + 1]++;

    for (int i = 2; i < tmp_rows.size(); i++)
        tmp_rows[i] += tmp_rows[i - 1];

    for (int i = 0; i < rows.size() - 1; i++)
        for (int j = 0; j < rows.size() - i - 1; j++) {
            if (rows[j] > rows[j + 1]) {
                int tmp = rows[j];
                rows[j] = rows[j + 1];
                rows[j + 1] = tmp;

                tmp = row_indexes[j];
                row_indexes[j] = row_indexes[j + 1];
                row_indexes[j + 1] = tmp;

                double dtmp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = dtmp;
            }
        }
    rows = row_indexes;
    pointer = tmp_rows;

    return *this;
}

bool SparseMatrix::operator==(const SparseMatrix& matrix) const {
    for (int i = 0; i < values.size(); i++)
        if (fabs(values[i] - matrix.values[i]) > 0.00001)
            return false;
    for (int i = 0; i < rows.size(); i++)
        if (rows[i] != matrix.rows[i])
            return false;
    for (int i = 0; i < pointer.size(); i++)
        if (pointer[i] != matrix.pointer[i])
            return false;
    return true;
}

void SparseMatrix::print() {
    for (int i = 0; i < values.size(); i++)
        std::cout << values[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < rows.size(); i++)
        std::cout << rows[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < pointer.size(); i++)
        std::cout << pointer[i] << " ";
    std::cout << std::endl;
}

// std::vector<double> sort_vec(std::vector<std::pair<int, double>>& vec) {
//     std::vector<double> result;

//     for (int i = 0; i < vec.size() - 1; i++)
//     for (int j = 0; j < vec.size() - i - 1; j++) {
//         if (vec[j].first > vec[j + 1].first) {
//             int tmp = vec[j].second;
//             vec[j].second = vec[j + 1].second;
//             vec[j + 1].second = tmp;
//         }
//     }
// }
