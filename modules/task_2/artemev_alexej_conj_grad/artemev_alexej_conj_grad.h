// Copyright 2023 Artemev Alexej
#ifndef MODULES_TASK_2_ARTEMEV_ALEXEJ_CONJ_GRAD_ARTEMEV_ALEXEJ_CONJ_GRAD_H_
#define MODULES_TASK_2_ARTEMEV_ALEXEJ_CONJ_GRAD_ARTEMEV_ALEXEJ_CONJ_GRAD_H_

#include <omp.h>
#include <iostream>
#include <vector>

double vecs_mult(const std::vector<double>& vec1, const std::vector<double>& vec2);
std::vector<double> mult_matrix_by_vec(const std::vector<std::vector<double>>& M,
const std::vector<double>& vec);
std::vector<double> mult_vec_by_number(const std::vector<double>& vec, double number);
std::vector<double> vecs_sum(const std::vector<double>& vec1,
const std::vector<double>& vec2);
std::vector<double> den_vec(const std::vector<double>& vec);
std::vector<double> conj_grad_method(const std::vector<std::vector<double>>& M,
const std::vector<double>& betta);
std::vector<double> random_vec(int size);
std::vector<std::vector<double>> random_matrix(int size);
std::vector<double> par_mult_matrix_by_vec(const std::vector<std::vector<double>>& M,
const std::vector<double>& vec, int n);
std::vector<double> par_conj_grad_method(const std::vector<std::vector<double>>& M,
const std::vector<double>& vec, int n);

#endif  // MODULES_TASK_2_ARTEMEV_ALEXEJ_CONJ_GRAD_ARTEMEV_ALEXEJ_CONJ_GRAD_H_
