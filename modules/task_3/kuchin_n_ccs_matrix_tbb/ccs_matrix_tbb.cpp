// Copyright 2023 Kuchin Nikita

#include "../../../modules/task_3/kuchin_n_ccs_matrix_tbb/ccs_matrix_tbb.h"

#include <tbb/concurrent_vector.h>
// #include <tbb/mutex.h>
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
    if (A.n != B.n) {
        throw std::invalid_argument("Matrices have different sizes.");
    }
    SparceMatrix BT = transport(B);
    SparceMatrix C;
    C.n = A.n;
    std::vector<double> emptyd;
    std::vector<int> emptyi;
    for (int i = 0; i < A.n; i++) {
        C.row_id.push_back(emptyi);
        C.data.push_back(emptyd);
    }
    C.col_ptr.push_back(0);

    tbb::parallel_for(
        tbb::blocked_range<int>(0, A.n), [&](const tbb::blocked_range<int>& r) {
            for (int i = r.begin(); i < r.end(); i++) {
                for (int j = 0; j < B.n; j++) {
                    double dot_product = 0;
                    int k1 = A.col_ptr[i];
                    int k2 = BT.col_ptr[j];
                    while (k1 < A.col_ptr[i + 1] && k2 < BT.col_ptr[j + 1]) {
                        if (A.row_id[k1] < BT.row_id[k2]) {
                            k1++;
                        } else if (A.row_id[k1] > BT.row_id[k2]) {
                            k2++;
                        } else {
                            dot_product += A.data[k1] * BT.data[k2];
                            k1++;
                            k2++;
                        }
                    }
                    if (dot_product != 0) {
                        tbb::mutex::scoped_lock lock(C.data[i].mutex);
                        C.data[i].push_back(dot_product);
                        C.row_id[i].push_back(j);
                        C.col_ptr[j + 1]++;
                    }
                }
            }
        });

    for (int i = 0; i < C.n; i++) {
        C.col_ptr.push_back(C.col_ptr[i] + C.data[i].size());
    }

    return C;
}
