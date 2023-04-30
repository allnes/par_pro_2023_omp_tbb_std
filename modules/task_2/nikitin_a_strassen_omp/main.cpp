// Copyright 2023 Nikitin Aleksandr

#include <gtest/gtest.h>

#include "./strassen.h"

TEST(STRASSEN_SEQ, TEST_1) {
  int n = 2;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_SEQ, TEST_2) {
  int n = 4;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_SEQ, TEST_3) {
  int n = 8;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_SEQ, TEST_4) {
  int n = 16;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_SEQ, TEST_5) {
  int n = 20;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}
