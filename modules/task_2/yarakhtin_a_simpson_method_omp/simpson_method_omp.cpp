// Copyright 2023 Yarakhtin Anton
#include "../../../modules/task_2/yarakhtin_a_simpson_method_omp/simpson_method_omp.h"
#include <cmath>

double simpson_method(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func) {
    int dim = scopes.size();
    std::vector<double> h(dim);
    int points_count = 1;
    double main_coef = 1.;
    for (int i = 0; i < dim; i++) {
        int partions = std::get<2>(scopes[i]);
        points_count *= (1 + 2 * partions);
        h[i] = (std::get<1>(scopes[i]) - std::get<0>(scopes[i])) / (2. * partions);
        main_coef *= h[i] / 3.;
    }

    double result = 0;
    std::vector<double> func_args(dim);
    for (int i = 0; i < points_count; i++) {
        int coef = 1;
        for (int j = 0, tmp = i; j < dim; j++) {
            int points = (1 + 2 * std::get<2>(scopes[j]));
            int index = tmp % points;
            tmp /= points;
            func_args[j] = std::get<0>(scopes[j]) + index * h[j];
            if (index != 0 && index != points - 1) {
                coef *= 2 * (1 + index % 2);
            }
        }
        result += coef * func(func_args);
    }
    return main_coef * result;
}

double simpson_method_omp(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func) {
    int dim = scopes.size();
    std::vector<double> h(dim);
    int points_count = 1;
    double main_coef = 1.;
    for (int i = 0; i < dim; i++) {
        int partions = std::get<2>(scopes[i]);
        points_count *= (1 + 2 * partions);
        h[i] = (std::get<1>(scopes[i]) - std::get<0>(scopes[i])) / (2. * partions);
        main_coef *= h[i] / 3.;
    }

    constexpr int chunk_size = 1024;
    int chunk_count = points_count / chunk_size + (points_count % chunk_size ? 1 : 0);

    double result = 0;
    #pragma omp parallel for
    for (int k = 0; k < chunk_count; k++) {
        double loc_result = 0;
        for (int i = k * chunk_size; i < (k + 1) * chunk_size && i < points_count; i++) {
            std::vector<double> func_args(dim);
            int coef = 1;
            for (int j = 0, tmp = i; j < dim; j++) {
                int points = (1 + 2 * std::get<2>(scopes[j]));
                int index = tmp % points;
                tmp /= points;
                func_args[j] = std::get<0>(scopes[j]) + index * h[j];
                if (index != 0 && index != points - 1) {
                    coef *= 2 * (1 + index % 2);
                }
            }
            loc_result += coef * func(func_args);
        }
        #pragma omp critical
        {
            result += loc_result;
        }
    }
    
    return main_coef * result;
}
