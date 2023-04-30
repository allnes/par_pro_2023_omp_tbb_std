// Copyright 2023 Grachev Valentin
#ifndef MODULES_TASK_2_GRACHEV_V_MULT_RARE_MATRIX_MULT_RARE_MATRIX_H_
#define MODULES_TASK_2_GRACHEV_V_MULT_RARE_MATRIX_MULT_RARE_MATRIX_H_

#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::vector;

double const maxValue = 100;
double const minValue = -100;
double const eps = 10e-9;

struct MatrixValue {
    double value;
    int col_number;

    MatrixValue(double _value, int _col_number) {
        value = _value;
        col_number = _col_number;
    }

    bool Equal(const MatrixValue &other);
};

class MatrixCRS {
 private:
    vector<vector<MatrixValue>> values;

    int strQuant;
    int colQuant;

 public:
    MatrixCRS(int strs, int cols);
    void Fill(double *arr);
    void FillRandom(int rarity);

    MatrixCRS Multiple(const MatrixCRS &matrix) const;
    MatrixCRS MultipleParallel(const MatrixCRS& matrix) const;

    MatrixCRS GetTranspose() const;

    void Print() const;

    bool Equal(const MatrixCRS &other);
};

double ScalarMultiple(const vector<MatrixValue> &v1,
                      const vector<MatrixValue> &v2);

#endif  // MODULES_TASK_2_GRACHEV_V_MULT_RARE_MATRIX_MULT_RARE_MATRIX_H_
