// Copyright 2023 Artemev Alexej
#include "../../../modules/task_1/artemev_alexej_conj_grad/artemev_alexej_conj_grad.h"

std::vector<double> den_vec(const std::vector<double>& vec) {
    size_t size = vec.size();
    std::vector<double> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = -vec[i];
    }
    return result;
}
std::vector<double> vecs_sum(const std::vector<double>& vec1,
const std::vector<double>& vec2) {
    size_t size = vec1.size();
    std::vector<double> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

double vecs_mult(const std::vector<double>& vec1,
const std::vector<double>& vec2) {
    double result = 0;
    size_t size = vec1.size();
    for (size_t i = 0; i < size; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

std::vector<double> mult_vec_by_number(const std::vector<double>& vec, double number) {
    size_t size = vec.size();
    std::vector<double> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = vec[i] * number;
    }
    return result;
}

std::vector<double> mult_matrix_by_vec(const std::vector<std::vector<double>>& M,
const std::vector<double>& vec) {
    size_t size = vec.size();
    std::vector<double> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = vecs_mult(M[i], vec);
    }
    return result;
}

std::vector<double> conj_grad_method(const std::vector<std::vector<double>>& M,
const std::vector<double>& vec) {
    size_t size = vec.size();
    std::vector<double> x(size);
    std::vector<double> r(size);
    std::vector<double> z(size);
    r = vecs_sum(vec, den_vec(mult_matrix_by_vec(M, x)));
    z = r;
    for (size_t i = 0; i < size; i++) {
        double alfa;
        double betta;
        std::vector<double> new_r(size);
        alfa = vecs_mult(r, r) / vecs_mult(mult_matrix_by_vec(M, z), z);
        x = vecs_sum(x, mult_vec_by_number(z, alfa));
        new_r = vecs_sum(r, den_vec(mult_vec_by_number(mult_matrix_by_vec(M, z), alfa)));
        betta = vecs_mult(new_r, new_r) / vecs_mult(r, r);
        z = vecs_sum(new_r, mult_vec_by_number(z, betta));
        r = new_r;
    }
    return x;
}

