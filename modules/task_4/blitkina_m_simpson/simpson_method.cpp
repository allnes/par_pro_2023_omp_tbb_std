// Copyright 2023 Blitkina Maria
#include "../../../modules/task_4/bykovskaya_a_simpson_method/simpson_method.h"
#include <vector>
#include <functional>
#include <utility>
#include <thread>

double calcIntegral(const std::vector<std::pair<double, double>>& scope,
        std::function<double(const std::vector<double>)> f, int accurancy,
        size_t level, std::vector<double> fix_var) {
    if (scope.size() == 0)
        throw "Bad scope";
    if (fix_var.size() == 0)
        for (auto i : scope)
            fix_var.push_back(i.first);
    if (level >= scope.size())
        throw "Bad level of recursion";
    double h = (scope[level].second - scope[level].first) / (2 * accurancy);
    std::vector<double> func_res(2 * accurancy);
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);
    int delta = (accurancy * 2) / (num_threads);
    int remainder = (accurancy * 2) % (num_threads);
    if (scope.size() == level + 1) {
        for (int i = 0; i < accurancy * 2; i++) {
            fix_var[level] = scope[level].first + i * h;
            func_res[i] = f(fix_var);
        }
    } else {
        for (int i = 0; i < num_threads; ++i) {
            threads[i] = std::thread([&](int begin, int end, const int id) {
                if (id == num_threads - 1)
                    end += remainder;
                for (int j = begin; j < end; ++j) {
                    fix_var[level] = scope[level].first + j * h;
                    func_res[j] =  calcIntegral(scope, f, accurancy,
                                                level + 1, fix_var);
                }
            }, i * delta, i * delta + delta, i);
        }
        for (int i = 0; i < num_threads; ++i)
            threads[i].join();
    }
    double res = func_res[0] + func_res[2 * accurancy - 1];
    for (int i = 1; i < 2 * accurancy - 1; i += 2)
        res += 4 * func_res[i];
    for (int i = 2; i < 2 * accurancy - 2; i += 2)
        res += 2 * func_res[i];
    res = res * h / 3.0;
    return res;
}
