// Copyright 2023 Davydov Andrey
#include <tbb/tbb.h>
#include <vector>
#include <random>
#include "../../modules/task_3/davydov_a_monte_carlo/monte_carlo.h"

double funcSum(const std::vector<double>& arguments) {
    double result = 0.0;
    size_t argumentsLength = arguments.size();
    for (size_t i = 0; i < argumentsLength; ++i) {
        result += arguments[i];
    }
    return result;
}

double funcSub(const std::vector<double>& arguments) {
    double result = 0.0;
    size_t argumentsLength = arguments.size();
    for (size_t i = 0; i < argumentsLength; ++i) {
        result -= arguments[i];
    }
    return result;
}

double funcMultiply(const std::vector<double>& arguments) {
    double result = 1.0;
    size_t argumentsLength = arguments.size();
    for (size_t i = 0; i < argumentsLength; ++i) {
        result *= arguments[i];
    }
    return result;
}

double sequentialMonteCarlo(
    double (&f)(const std::vector<double>&),
    std::vector<double> a,
    std::vector<double> b,
    int n
) {
    int dimension = static_cast<int>(a.size());
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<std::uniform_real_distribution<double>> distribution(dimension);
    std::vector<double> arguments(dimension);
    double result = 0.0;

    for (int i = 0; i < dimension; ++i) {
        distribution[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dimension; ++j) {
            arguments[j] = distribution[j](gen);
        }

        result += f(arguments);
    }

    for (int i = 0; i < dimension; ++i) {
        result *= b[i] - a[i];
    }

    return result / n;
}

double parallelMonteCarlo(
    double (&f)(const std::vector<double>&),
    std::vector<double> a,
    std::vector<double> b,
    int n
) {
    int dimension = static_cast<int>(a.size());
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<std::uniform_real_distribution<double>> distribution(dimension);
    double result = 0.0;

    for (int i = 0; i < dimension; ++i) {
        distribution[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    }

    result = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, n),
        0.0,
        [&](tbb::blocked_range<int> range, double local_result) {
            std::vector<double> arguments(dimension);
            for (size_t i = range.begin(); i != range.end(); ++i) {
                for (int j = 0; j < dimension; ++j) {
                    arguments[j] = distribution[j](gen);
                }
                local_result += f(arguments);
            }
            return local_result;
        },
        std::plus<double>());

    for (int i = 0; i < dimension; ++i) {
        result *= b[i] - a[i];
    }

    return result / n;
}
