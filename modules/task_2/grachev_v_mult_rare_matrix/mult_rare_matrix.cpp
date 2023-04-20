// Copyright 2023 Grachev Valentin
#include "../../../modules/task_2/grachev_v_mult_rare_matrix/mult_rare_matrix.h"

MatrixCRS::MatrixCRS(int strs, int cols)
    : strQuant(strs), colQuant(cols),
      values(vector<vector<MatrixValue>>(strs)) {}

void MatrixCRS::Fill(double *arr) {
    for (int i = 0; i < strQuant; i++) {
        for (int j = 0; j < colQuant; j++) {
            if (arr[i * colQuant + j] != 0) {
                MatrixValue mValue(arr[i * colQuant + j], j);
                values[i].push_back(mValue);
            }
        }
    }
}

void MatrixCRS::FillRandom(int rarity) {
    std::random_device dev;
    std::mt19937 gen(dev());

    for (int i = 0; i < strQuant; i++) {
        for (int j = 0; j < colQuant; j++) {
            bool elemIsNotZero = gen() % rarity == 0;
            if (elemIsNotZero) {
                double value =
                    minValue + (gen() % (static_cast<int>(maxValue) -
                                         static_cast<int>(minValue)));
                MatrixValue mValue(value, j);
                values[i].push_back(mValue);
            }
        }
    }
}

MatrixCRS MatrixCRS::Multiple(const MatrixCRS &matrix) const {
    MatrixCRS res = MatrixCRS(strQuant, matrix.colQuant);
    MatrixCRS mTrans = matrix.GetTranspose();

    for (int i = 0; i < strQuant; i++) {
        for (int j = 0; j < mTrans.values.size(); j++) {
            double value = ScalarMultiple(values[i], mTrans.values[j]);
            MatrixValue mValue(value, j);

            if (abs(value) > eps)
                res.values[i].push_back(mValue);
        }
    }

    return res;
}

MatrixCRS MatrixCRS::MultipleParallel(const MatrixCRS &matrix) const {
    MatrixCRS res = MatrixCRS(strQuant, matrix.colQuant);
    MatrixCRS mTrans = matrix.GetTranspose();

#pragma omp parallel for
    for (int i = 0; i < strQuant; i++) {
        for (int j = 0; j < mTrans.values.size(); j++) {
            double value = ScalarMultiple(values[i], mTrans.values[j]);
            MatrixValue mValue(value, j);

            if (abs(value) > eps)
                res.values[i].push_back(mValue);
        }
    }

    return res;
}

MatrixCRS MatrixCRS::GetTranspose() const {
    MatrixCRS res = MatrixCRS(colQuant, strQuant);

    for (int i = 0; i < strQuant; i++) {
        for (int k = 0; k < values[i].size(); k++) {
            int j = values[i][k].col_number;
            double value = values[i][k].value;
            MatrixValue elem = MatrixValue(value, i);
            res.values[j].push_back(elem);
        }
    }

    return res;
}

void MatrixCRS::Print() const {
    cout << "Matrix:\n";
    for (int i = 0; i < strQuant; i++) {
        for (int j = 0; j < colQuant; j++) {
            bool hasElem = false;
            int k = 0;
            for (; k < values[i].size(); k++)
                if (values[i][k].col_number == j) {
                    hasElem = true;
                    break;
                }

            if (hasElem)
                cout << values[i][k].value << "\t";
            else
                cout << 0 << "\t";
        }
        cout << "\n";
    }
}

bool MatrixCRS::Equal(const MatrixCRS &other) {
    if (strQuant != other.strQuant || colQuant != other.colQuant ||
        values.size() != other.values.size())
        return false;
    for (int i = 0; i < values.size(); i++) {
        if (values[i].size() != other.values[i].size())
            return false;
        for (int j = 0; j < values[i].size(); j++)
            if (!values[i][j].Equal(other.values[i][j]))
                return false;
    }

    return true;
}

double ScalarMultiple(const vector<MatrixValue> &v1,
                      const vector<MatrixValue> &v2) {
    double res = 0;
    int p1 = 0, p2 = 0;

    while (p1 < v1.size() && p2 < v2.size()) {
        if (v1[p1].col_number == v2[p2].col_number) {
            res += v1[p1].value * v2[p2].value;
            p1++;
            p2++;
        } else if (v1[p1].col_number < v2[p2].col_number) {
            p1++;
        } else {
            p2++;
        }
    }
    return res;
}

bool MatrixValue::Equal(const MatrixValue &other) {
    return fabs(value - other.value) < eps && col_number == other.col_number;
}
