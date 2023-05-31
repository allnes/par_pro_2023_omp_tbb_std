// Copyright 2023 Varyzgin Dmitry
#pragma once

#include <vector>

int getNewSize(int m1, int n1, int m2, int n2);
std::vector<double> getRandomMatrix(int m, int n);
std::vector<double> appendZeros(const std::vector<double>& mat, int m, int n, int new_size);
std::vector<double> sumMatrix(bool isSum, const std::vector<double>& mat1, const std::vector<double>& mat2);
std::vector<std::vector<double>> splitMatrix(const std::vector<double>& mat);
std::vector<double> getStrassenSequence(const std::vector<double>& matA, const std::vector<double>& matB);
