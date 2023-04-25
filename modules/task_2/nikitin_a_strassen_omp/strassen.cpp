// Copyright 2023 Nikitin Aleksandr

#include "../../../modules/task_2/nikitin_a_strassen_omp/strassen.h"

#include <omp.h>

#include <random>

void setToRandom(matrix* A, int n) {
  std::random_device dev;
  static std::mt19937 gen(dev());

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++) (*A)[i][j] = gen() % 100;
}

matrix multiply(matrix* A, matrix* B, int n) {
  matrix C(n, vector(n, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++) C[i][j] += (*A)[i][k] * (*B)[k][j];
  return C;
}

matrix add(matrix* M1, matrix* M2, int n) {
  matrix temp(n, vector(n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) temp[i][j] = (*M1)[i][j] + (*M2)[i][j];
  return temp;
}

matrix subtract(matrix* M1, matrix* M2, int n) {
  matrix temp(n, vector(n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) temp[i][j] = (*M1)[i][j] - (*M2)[i][j];
  return temp;
}

matrix strassenMultiply(matrix* A, matrix* B, int n, bool parallel) {
  if (n <= threshold) {
    matrix C(n, vector(n, 0));
    C = multiply(A, B, n);
    return C;
  }

  matrix C(n, vector(n, 0));
  int k = n / 2;

  matrix A11(k, vector(k, 0));
  matrix A12(k, vector(k, 0));
  matrix A21(k, vector(k, 0));
  matrix A22(k, vector(k, 0));
  matrix B11(k, vector(k, 0));
  matrix B12(k, vector(k, 0));
  matrix B21(k, vector(k, 0));
  matrix B22(k, vector(k, 0));

  for (int i = 0; i < k; i++)
    for (int j = 0; j < k; j++) {
      A11[i][j] = (*A)[i][j];
      A12[i][j] = (*A)[i][k + j];
      A21[i][j] = (*A)[k + i][j];
      A22[i][j] = (*A)[k + i][k + j];
      B11[i][j] = (*B)[i][j];
      B12[i][j] = (*B)[i][k + j];
      B21[i][j] = (*B)[k + i][j];
      B22[i][j] = (*B)[k + i][k + j];
    }

  matrix P1, P2, P3, P4, P5, P6, P7;

  if (parallel) {
#pragma omp parallel sections
    {
#pragma omp section
      {
        matrix S1 = subtract(&B12, &B22, k);
        P1 = strassenMultiply(&A11, &S1, k, parallel);
      }
#pragma omp section
      {
        matrix S2 = add(&A11, &A12, k);
        P2 = strassenMultiply(&S2, &B22, k, parallel);
      }
#pragma omp section
      {
        matrix S3 = add(&A21, &A22, k);
        P3 = strassenMultiply(&S3, &B11, k, parallel);
      }
#pragma omp section
      {
        matrix S4 = subtract(&B21, &B11, k);
        P4 = strassenMultiply(&A22, &S4, k, parallel);
      }
#pragma omp section
      {
        matrix S5 = add(&A11, &A22, k);
        matrix S6 = add(&B11, &B22, k);
        P5 = strassenMultiply(&S5, &S6, k, parallel);
      }
#pragma omp section
      {
        matrix S7 = subtract(&A12, &A22, k);
        matrix S8 = add(&B21, &B22, k);
        P6 = strassenMultiply(&S7, &S8, k, parallel);
      }
#pragma omp section
      {
        matrix S9 = subtract(&A11, &A21, k);
        matrix S10 = add(&B11, &B12, k);
        P7 = strassenMultiply(&S9, &S10, k, parallel);
      }
    }
  } else {
    matrix S1 = subtract(&B12, &B22, k);
    matrix S2 = add(&A11, &A12, k);
    matrix S3 = add(&A21, &A22, k);
    matrix S4 = subtract(&B21, &B11, k);
    matrix S5 = add(&A11, &A22, k);
    matrix S6 = add(&B11, &B22, k);
    matrix S7 = subtract(&A12, &A22, k);
    matrix S8 = add(&B21, &B22, k);
    matrix S9 = subtract(&A11, &A21, k);
    matrix S10 = add(&B11, &B12, k);

    P1 = strassenMultiply(&A11, &S1, k);
    P2 = strassenMultiply(&S2, &B22, k);
    P3 = strassenMultiply(&S3, &B11, k);
    P4 = strassenMultiply(&A22, &S4, k);
    P5 = strassenMultiply(&S5, &S6, k);
    P6 = strassenMultiply(&S7, &S8, k);
    P7 = strassenMultiply(&S9, &S10, k);
  }

  matrix S11 = add(&P5, &P4, k);
  matrix S12 = add(&S11, &P6, k);
  matrix S13 = add(&P5, &P1, k);
  matrix S14 = subtract(&S13, &P3, k);

  matrix C11 = subtract(&S12, &P2, k);
  matrix C12 = add(&P1, &P2, k);
  matrix C21 = add(&P3, &P4, k);
  matrix C22 = subtract(&S14, &P7, k);

  for (int i = 0; i < k; i++)
    for (int j = 0; j < k; j++) {
      C[i][j] = C11[i][j];
      C[i][j + k] = C12[i][j];
      C[k + i][j] = C21[i][j];
      C[k + i][k + j] = C22[i][j];
    }

  return C;
}
