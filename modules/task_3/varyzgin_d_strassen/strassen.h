// Copyright 2023 Varyzgin Dmitry
#ifndef MODULES_TASK_3_VARYZGIN_D_STRASSEN_STRASSEN_H_
#define MODULES_TASK_3_VARYZGIN_D_STRASSEN_STRASSEN_H_
#include <tbb/tbb.h>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<double> genVec(int n);
void printMatrix(const std::vector<double>& Mat, std::size_t n);
std::vector<double> mult(const std::vector<double>& A,
                               const std::vector<double>& B, int n);
std::vector<double> add(std::vector<double> A, std::vector<double> B);
std::vector<double> sub(const std::vector<double>& A, const std::vector<double>& B);
std::vector<double> strassen(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);
std::vector<double> strassenTbb(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);

#endif  // MODULES_TASK_3_VARYZGIN_D_STRASSEN_STRASSEN_H_
