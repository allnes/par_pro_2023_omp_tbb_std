// Copyright 2023 Kuchin Nikita

#include "../../../modules/task_3/kuchin_n_ccs_matrix_tbb/ccs_matrix_tbb.h"

#include <tbb/blocked_range.h>
#include <tbb/concurrent_vector.h>
#include <tbb/queuing_mutex.h>
#include <tbb/tbb.h>

#include <cmath>
#include <vector>

SparceMatrix transport(SparceMatrix A) {
    SparceMatrix AT;
    AT.n = A.n;
    std::vector<std::vector<int>> row;
    std::vector<std::vector<double>> val;
    std::vector<int> emptyr;
    std::vector<double> emptyv;
    for (int i = 0; i < A.n; i++) {
        row.push_back(emptyr);
        val.push_back(emptyv);
    }
    std::vector<int> js;
    int f = 0;

    for (int i = 1; i < A.n + 1; i++) {
        for (int j = 0; j < A.col_ptr[i] - A.col_ptr[i - 1]; j++) {
            js.push_back(f);
        }
        f++;
    }
    for (int i = 0; i < js.size(); i++) {
        row[A.row_id[i]].push_back(js[i]);
        val[A.row_id[i]].push_back(A.data[i]);
    }

    std::vector<int> resrow;
    std::vector<double> resval;
    std::vector<int> ind;
    ind.push_back(0);
    int indic = 0;

    for (int i = 0; i < row.size(); i++) {
        for (int j = 0; j < row[i].size(); j++) {
            resrow.push_back(row[i][j]);
        }
        for (int k = 0; k < val[i].size(); k++) {
            resval.push_back(val[i][k]);
        }
        indic += row[i].size();
        ind.push_back(indic);
    }
    if (row.size() < A.n) {
        for (int i = 0; i < A.n - row.size(); i++) {
            ind.push_back(indic);
        }
    }
    AT.data = resval;
    AT.row_id = resrow;
    AT.col_ptr = ind;
    return AT;
}

SparceMatrix multiply(SparceMatrix A, SparceMatrix B) {
    SparceMatrix C;
    std::vector<double> temp(A.col_ptr.size() - 1);
    for (int j = 0; j < B.col_ptr.size() - 1; j++) {
        fill(temp.begin(), temp.end(), 0);
        for (int k = B.col_ptr[j]; k < B.col_ptr[j + 1]; k++) {
            int row = B.row_id[k];
            double val = B.data[k];
            for (int i = A.col_ptr[row]; i < A.col_ptr[row + 1]; i++) {
                int col = A.row_id[i];
                temp[col] += A.data[i] * val;
            }
        }
        C.col_ptr.push_back(C.data.size());
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] != 0) {
                C.data.push_back(temp[i]);
                C.row_id.push_back(i);
            }
        }
    }
    C.col_ptr.push_back(C.data.size());
    C.n = A.col_ptr.size() - 1;
    return C;
}

SparceMatrix tbbmultiply(SparceMatrix A, SparceMatrix B) {
    SparceMatrix C;
    tbb::concurrent_vector<double> temp(A.col_ptr.size() - 1);
    tbb::concurrent_vector<double> data;
    tbb::concurrent_vector<int> row_id;
    std::vector<int> col_ptr;
    tbb::queuing_mutex col_ptr_mutex;

    col_ptr.push_back(0);

    tbb::parallel_for(
        tbb::blocked_range<int>(0, B.col_ptr.size() - 1),
        [&](const tbb::blocked_range<int>& range) {
            for (int j = range.begin(); j < range.end(); j++) {
                std::fill(temp.begin(), temp.end(), 0);
                for (int k = B.col_ptr[j]; k < B.col_ptr[j + 1]; k++) {
                    int row = B.row_id[k];
                    double val = B.data[k];
                    for (int i = A.col_ptr[row]; i < A.col_ptr[row + 1]; i++) {
                        int col = A.row_id[i];
                        temp[col] += A.data[i] * val;
                    }
                }
                int data_size = 0;
                for (int i = 0; i < temp.size(); i++) {
                    if (temp[i] != 0) {
                        data.push_back(temp[i]);
                        row_id.push_back(i);
                        data_size++;
                    }
                }
                {
                    tbb::queuing_mutex::scoped_lock lock(col_ptr_mutex);
                    col_ptr.push_back(col_ptr.back() + data_size);
                }
            }
        });

    C.data = std::vector<double>(data.begin(), data.end());
    C.row_id = std::vector<int>(row_id.begin(), row_id.end());
    C.col_ptr = col_ptr;
    C.n = A.col_ptr.size() - 1;
    return C;
}
