// Copyright 2023 Selivankin Sergey
#pragma once

#include <vector>

std::vector<double> getRandomMatrix(int m, int n);
std::vector<double> getStrassenSequence(const std::vector<double>& A, const std::vector<double>& B,
                                        int m1, int n1, int m2, int n2);
std::vector<double> getStrassenParallel(const std::vector<double>& A, const std::vector<double>& B,
                                        int m1, int n1, int m2, int n2);
