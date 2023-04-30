// Copyright 2023 Chernova Anna
#include "../../../modules/task_2/chernova_a_ccs_matrix_mult/ccs_matrix_mult.h"

#include <omp.h>

#include <algorithm>
#include <complex>
#include <random>
#include <vector>

using std::complex;
using std::equal;
using std::vector;

MatrixCSS::MatrixCSS(size_t numberRows, size_t numberColumns)
    : numberRows(numberRows), numberColumns(numberColumns) {
  values.reserve((numberRows * numberColumns) / 2);
  rows.reserve((numberRows * numberColumns) / 2);
  pointer.reserve(numberColumns + 1);
  pointer.push_back(0);
}

MatrixCSS::MatrixCSS(const vector<complex<double>>& v, size_t numberRows,
                     size_t numberColumns)
    : numberRows(numberRows), numberColumns(numberColumns) {
  values.reserve((numberRows * numberColumns) / 2);
  rows.reserve((numberRows * numberColumns) / 2);
  pointer.reserve(numberColumns + 1);
  pointer.push_back(0);

  for (size_t column = 0; column < numberColumns; ++column) {
    for (size_t row = 0; row < numberRows; ++row) {
      if (v[row * numberRows + column].real() != .0 ||
          v[row * numberRows + column].imag() != .0) {
        values.push_back(v[row * numberRows + column]);
        rows.push_back(row);
      }
    }
    pointer.push_back(values.size());
  }
}

MatrixCSS::MatrixCSS(const MatrixCSS& oth)
    : numberRows(oth.numberRows),
      numberColumns(oth.numberColumns),
      values(oth.values),
      rows(oth.rows),
      pointer(oth.pointer) {}

void MatrixCSS::transponse() {
  vector<vector<complex<double>>> tmpValues(pointer.size() - 1);
  vector<vector<int>> tmpRows(pointer.size() - 1);

  for (size_t column = 0; column < pointer.size() - 1; ++column) {
    for (size_t imageRow = pointer[column]; imageRow < pointer[column + 1];
         ++imageRow) {
      tmpValues[rows[imageRow]].push_back(values[imageRow]);
      tmpRows[rows[imageRow]].push_back(column);
    }
  }

  values.clear();
  rows.clear();
  pointer.clear();
  pointer.push_back(0);

  for (size_t column = 0; column < tmpValues.size(); ++column) {
    for (size_t row = 0; row < tmpValues[column].size(); ++row) {
      values.push_back(tmpValues[column][row]);
      rows.push_back(tmpRows[column][row]);
    }
    pointer.push_back(values.size());
  }
}

const MatrixCSS operator*(const MatrixCSS& left, const MatrixCSS& right) {
  MatrixCSS result(left.numberRows, right.numberColumns);
  MatrixCSS tLeft(left);
  tLeft.transponse();

  for (size_t leftColumn = 0; leftColumn < tLeft.numberColumns; ++leftColumn) {
    for (size_t rightColumn = 0; rightColumn < right.numberColumns;
         ++rightColumn) {
      complex<double> buff =
          columnMultiplication(tLeft, right, rightColumn, leftColumn);

      if (buff.real() != .0 || buff.imag() != .0) {
        result.values.push_back(buff);
        result.rows.push_back(rightColumn);
      }
    }
    result.pointer.push_back(result.values.size());
  }

  return result;
}

complex<double> columnMultiplication(const MatrixCSS& tLeft,
                                     const MatrixCSS& right, const size_t n,
                                     const size_t m) {
  complex<double> result(.0, .0);
  int tLeftColumn = tLeft.pointer[n];
  int rightColumn = right.pointer[m];

  while (tLeftColumn < tLeft.pointer[n + 1] &&
         rightColumn < right.pointer[m + 1]) {
    if (tLeft.rows[tLeftColumn] > right.rows[rightColumn])
      rightColumn += 1;
    else if (right.rows[rightColumn] > tLeft.rows[tLeftColumn])
      tLeftColumn += 1;
    else
      result += tLeft.values[tLeftColumn++] * right.values[rightColumn++];
  }

  return result;
}

bool operator==(const MatrixCSS& left, const MatrixCSS& right) {
  if (equal(left.values.begin(), left.values.end(), right.values.begin()) &&
      equal(left.rows.begin(), left.rows.end(), right.rows.begin()) &&
      equal(left.pointer.begin(), left.pointer.end(), right.pointer.begin())) {
    return true;
  }
  return false;
}

const MatrixCSS parallelCCSMultiplication(const MatrixCSS& left,
                                          const MatrixCSS& right) {
  int numberOfThread = omp_get_num_procs();
  MatrixCSS result(left.numberRows, right.numberColumns);
  MatrixCSS tLeft(left);
  tLeft.transponse();

  vector<vector<complex<double>>> vectorsOfValues =
      vector<vector<complex<double>>>(tLeft.numberColumns);
  vector<vector<int>> vectorsOfRows = vector<vector<int>>(tLeft.numberColumns);

#pragma omp parallel for
  for (int leftColumn = 0; leftColumn < tLeft.numberColumns; ++leftColumn) {
    for (int rightColumn = 0; rightColumn < right.numberColumns;
         ++rightColumn) {
      complex<double> buff =
          columnMultiplication(tLeft, right, rightColumn, leftColumn);

      if (buff.real() != .0 || buff.imag() != .0) {
        vectorsOfValues[leftColumn].push_back(buff);
        vectorsOfRows[leftColumn].push_back(rightColumn);
      }
    }
  }

  for (int i = 0; i < vectorsOfValues.size(); ++i) {
    for (int j = 0; j < vectorsOfValues[i].size(); ++j) {
      result.values.push_back(vectorsOfValues[i][j]);
      result.rows.push_back(vectorsOfRows[i][j]);
    }
    result.pointer.push_back(result.values.size());
  }

  return result;
}

vector<complex<double>> getRandomVector(size_t numberRows,
                                        size_t numberColumns) {
  double lowerBound = 0;
  double upperBound = 100;
  std::uniform_real_distribution<double> unif(lowerBound, upperBound);
  std::default_random_engine re;

  vector<complex<double>> result(numberRows * numberColumns);
  for (size_t i = 0; i < numberRows * numberColumns; ++i) {
    result[i] = complex<double>(unif(re), unif(re));
  }

  return result;
}
