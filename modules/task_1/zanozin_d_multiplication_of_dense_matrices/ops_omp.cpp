// Copyright 2023 Zanozin Danila
#include <gtest/gtest.h>

#include <random>
#include <vector>

struct Matrix {
  std::vector<std::vector<double>> data;
  int size;

  explicit Matrix(int _size = 5)
      : size(_size), data(std::vector<std::vector<double>>(_size)) {
    for (int i = 0; i < size; i++) data.at(i) = std::vector<double>(_size);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        data.at(i).at(j) = 0;
      }
    }
  }

  void randomize() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        data.at(i).at(j) = std::rand() % 10;
      }
    }
  }

  void out() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        std::cout << data.at(i).at(j) << "\t";
      }
      std::cout << "\n";
    }
    std::cout << "\n--------------------\n";
  }

  void moveRight() {
    for (auto vec = data.begin(); vec != data.end(); ++vec) {
      double cache = vec->at(0);
      vec->erase(vec->begin());
      vec->push_back(cache);
    }
  }
  void moveUp() {
    std::vector<double> cache(data.at(0));
    data.erase(data.begin());
    data.push_back(cache);
  }
  void transponse() {
    for (int i = 0; i < size; i++) {
      for (int j = i; j < size; j++) {
        std::swap(data.at(i).at(j), data.at(j).at(i));
      }
    }
  }

  void leftInitialise() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < i; j++) {
        double cache = data.at(i).at(0);
        data.at(i).erase(data.at(i).begin());
        data.at(i).push_back(cache);
      }
    }
  }
  void upInitialise() {
    transponse();
    leftInitialise();
    transponse();
  }
  Matrix operator*(const Matrix& mult) {
    Matrix c(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++) {
          c.data.at(i).at(j) += data.at(i).at(k) * mult.data.at(k).at(j);
        }
      }
    }
    return c;
  }
  friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (rhs.size != lhs.size) return false;
    for (int i = 0; i < rhs.size; i++) {
      for (int j = 0; j < rhs.size; j++) {
        if (lhs.data.at(i).at(j) != rhs.data.at(i).at(j)) return false;
      }
    }
    return true;
  }
};

Matrix seqKannonMethod(Matrix a, Matrix b) {
  int size = a.size;

  Matrix c(size);
  a.leftInitialise();
  b.upInitialise();

  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        c.data.at(i).at(j) += a.data.at(i).at(j) * b.data.at(i).at(j);
      }
    }
    a.moveRight();
    b.moveUp();
  }
  return c;
}
