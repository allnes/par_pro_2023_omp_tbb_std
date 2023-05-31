// Copyright 2023 Varyzgin Dmitry
#ifndef MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
#include <vector>

std::vector<double> genVec(int n);
std::vector<double> mult(const std::vector<double>& A,
                               const std::vector<double>& B, int n);
std::vector<double> add(std::vector<double> A, std::vector<double> B);
std::vector<double> sub(const std::vector<double>& A, const std::vector<double>& B);
std::vector<double> strassen(const std::vector<double>& A,
                                  const std::vector<double>& B, std::size_t n);

#endif  // MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
