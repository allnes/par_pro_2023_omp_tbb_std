// Copyright 2023 Mokrousov Artem

#include "../../../modules/task_1/mokrousov_a_crs_mult_matrix_seq/mokrousov_a_crs_mult_matrix_seq.h"

#include <omp.h>

Matrix seq_crs_mult(Matrix A, Matrix B) {
    B.transponse();
    Matrix result;
    int resIndex = 0;
    for (int i = 0; i < A.pointer.size() - 1; i++) {
        for (int j = 0; j < B.pointer.size() - 1; j++) {
            int sumVal = 0;
            for (int AvalInd = A.pointer.at(i); AvalInd < A.pointer.at(i + 1);
                 AvalInd++) {
                for (int BvalInd = B.pointer.at(j);
                     BvalInd < B.pointer.at(j + 1); BvalInd++) {
                    if (A.colums.at(AvalInd) == B.colums.at(BvalInd)) {
                        sumVal += A.values.at(AvalInd) * B.values.at(BvalInd);
                    }
                }
            }
            if (result.pointer.size() == i) result.pointer.push_back(resIndex);
            if (sumVal > 0) {
                result.values.push_back(sumVal);
                result.colums.push_back(j);
                resIndex++;
            }
        }
    }
    result.pointer.push_back(result.values.size());
    return result;
}
