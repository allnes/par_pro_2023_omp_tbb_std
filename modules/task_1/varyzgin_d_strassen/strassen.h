// Copyright 2023 Varyzgin Dmitry
#ifndef MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
#include <vector>

std::vector<double> genRandomVector(int n);
void printMatrix(const std::vector<double>& Mat, std::size_t n);

// Standart multiplication alg
std::vector<double> usualMultiply(const std::vector<double>& A,
                               const std::vector<double>& B, int n);

// To add or substract some matrices
std::vector<double> add(std::vector<double> A, std::vector<double> B);
std::vector<double> sub(const std::vector<double>& A, const std::vector<double>& B);

// Strassen multiplication alg
std::vector<double> strassenMultiply(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);

#endif  // MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_