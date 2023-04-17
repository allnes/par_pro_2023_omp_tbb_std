// Copyright 2023 Nikitin Aleksandr

#include <math.h>

#include <stdexcept>
#include <string>

#include "../../modules/task_1/nikitin_a_strassen/strassen.h"

void naive_mult(double* a, double* b, double* c, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      c[i * size + j] = 0;
      for (int k = 0; k < size; k++) {
        c[i * size + j] += a[i * size + k] * b[k * size + j];
      }
    }
  }
}

void get_p1(double* a11, double* a22, double* res1, double* b11, double* b22,
            double* res2, double* slice, int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = a11[i] + a22[i];
    res2[i] = b11[i] + b22[i];
  }
  strassen(res1, res2, slice, size);
}
void get_p2(double* a21, double* a22, double* res1, double* b11, double* slice,
            int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = a21[i] + a22[i];
  }
  strassen(res1, b11, slice, size);
}
void get_p3(double* a11, double* res1, double* b12, double* b22, double* slice,
            int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = b12[i] - b22[i];
  }
  strassen(a11, res1, slice, size);
}
void get_p4(double* a22, double* res1, double* b21, double* b11, double* slice,
            int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = b21[i] - b11[i];
  }
  strassen(a22, res1, slice, size);
}
void get_p5(double* a11, double* a12, double* res1, double* b22, double* slice,
            int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = a11[i] + a12[i];
  }
  strassen(res1, b22, slice, size);
}
void get_p6(double* a21, double* a11, double* res1, double* b11, double* b12,
            double* res2, double* slice, int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = a21[i] - a11[i];
    res2[i] = b11[i] + b12[i];
  }
  strassen(res1, res2, slice, size);
}
void get_p7(double* a12, double* a22, double* res1, double* b21, double* b22,
            double* res2, double* slice, int size) {
  for (int i = 0; i < size * size; i++) {
    res1[i] = a12[i] - a22[i];
    res2[i] = b21[i] + b22[i];
  }
  strassen(res1, res2, slice, size);
}

bool is_exp_of_2(int n) { return (n & (n - 1)) == 0; }

void strassen(double* a, double* b, double* c, int size) {
  if (!is_exp_of_2(size)) {
    throw std::invalid_argument("no power 2");
  }

  if (size <= 64) {
    naive_mult(a, b, c, size);
    return;
  }

  int part_size = static_cast<int>(size * size / 4);

  double* a11 = new double[size * size * 2];
  double* a12 = a11 + part_size;
  double* a21 = a12 + part_size;
  double* a22 = a21 + part_size;

  double* b11 = a22 + part_size;
  double* b12 = b11 + part_size;
  double* b21 = b12 + part_size;
  double* b22 = b21 + part_size;

  double* c11 = new double[size * size + part_size * 9];
  double* c12 = c11 + part_size;
  double* c21 = c12 + part_size;
  double* c22 = c21 + part_size;

  double* slice1 = c22 + part_size;
  double* slice2 = slice1 + part_size;
  double* slice3 = slice2 + part_size;
  double* slice4 = slice3 + part_size;
  double* slice5 = slice4 + part_size;
  double* slice6 = slice5 + part_size;
  double* slice7 = slice6 + part_size;

  double* res1 = slice7 + part_size;
  double* res2 = res1 + part_size;

  int half_split = static_cast<int>(size / 2);
  for (int i = 0; i < half_split; i++) {
    for (int j = 0; j < half_split; j++) {
      a11[i * half_split + j] = a[i * size + j];
      a12[i * half_split + j] = a[i * size + half_split + j];
      a21[i * half_split + j] = a[(half_split + i) * size + j];
      a22[i * half_split + j] = a[(half_split + i) * size + half_split + j];

      b11[i * half_split + j] = b[i * size + j];
      b12[i * half_split + j] = b[i * size + half_split + j];
      b21[i * half_split + j] = b[(half_split + i) * size + j];
      b22[i * half_split + j] = b[(half_split + i) * size + half_split + j];
    }
  }

  get_p1(a11, a22, res1, b11, b22, res2, slice1, size / 2);
  get_p2(a21, a22, res1, b11, slice2, size / 2);
  get_p3(a11, res1, b12, b22, slice3, size / 2);
  get_p4(a22, res1, b21, b11, slice4, size / 2);
  get_p5(a11, a12, res1, b22, slice5, size / 2);
  get_p6(a21, a11, res1, b11, b12, res2, slice6, size / 2);
  get_p7(a12, a22, res1, b21, b22, res2, slice7, size / 2);

  for (int i = 0; i < (size / 2) * (size / 2); i++) {
    res1[i] = slice1[i] + slice4[i];
    res2[i] = res1[i] - slice5[i];
    c11[i] = res2[i] + slice7[i];

    c12[i] = slice3[i] + slice5[i];

    c21[i] = slice2[i] + slice4[i];

    res1[i] = slice1[i] - slice2[i];
    res2[i] = res1[i] + slice3[i];
    c22[i] = res2[i] + slice6[i];
  }

  for (int i = 0; i < half_split; i++) {
    for (int j = 0; j < half_split; j++) {
      c[i * size + j] = c11[i * half_split + j];
      c[i * size + half_split + j] = c12[i * half_split + j];
      c[(half_split + i) * size + j] = c21[i * half_split + j];
      c[(half_split + i) * size + half_split + j] = c22[i * half_split + j];
    }
  }

  delete[] a11;
  delete[] c11;
}
