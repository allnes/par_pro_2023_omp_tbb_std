// Copyright 2023 Tuzhilkina Polina
#ifndef MODULES_TASK_2_TUZHILKINA_P_STRASSEN_STRASSEN_H_
#define MODULES_TASK_2_TUZHILKINA_P_STRASSEN_STRASSEN_H_
#include <omp.h>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<double> genRandomVector(int n);
void printMatrix(const std::vector<double>& Mat, std::size_t n);

// Standart multiplication alg
std::vector<double> usualMultiply(const std::vector<double>& A,
                               const std::vector<double>& B, int n);

// To add or substract some matrices
std::vector<double> add(std::vector<double> A, std::vector<double> B);
std::vector<double> sub(const std::vector<double>& A, const std::vector<double>& B);

// Strassen multiplication alg
std::vector<double> seqStrassenMultiply(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);
std::vector<double> ompStrassenMultiply(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);

#endif  // MODULES_TASK_2_TUZHILKINA_P_STRASSEN_STRASSEN_H_
