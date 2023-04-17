// Copyright 2023 Mironov Nikita
#include "../../../modules/task_1/mironov_n_trapezoid_method/trapezoid.h"

double d1_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h = (bounds[0].second - bounds[0].first)/doubleStepsCount;

    double x = bounds[0].first + h;

    double result = 0;

    result += (h/2.0) * (f({bounds[0].first}) + f({bounds[0].second}));

    for (int i = 1; i < N; i++) {
        result += h * f({x});
        x += h;
    }

    return result;
}

double d2_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;

    double x = 0;
    double y = 0;

    double result = 0;

    result += 0.25 *
        (f({bounds[0].first, bounds[1].first}) +
        f({bounds[0].second, bounds[1].second}) +
        f({bounds[0].first, bounds[1].second}) +
        f({bounds[0].second, bounds[1].first}));

    for (int i = 1; i < N; i++) {
        x = bounds[0].first + h_for_x * i;
        result += 0.5 * (f({x, bounds[1].first}) +
        f({x, bounds[1].second}));

        y = bounds[1].first + h_for_y * i;

        result += 0.5 * (f({bounds[0].first, y}) +
        f({bounds[0].second, y}));
        for (int j = 1; j < N; j++) {
            y = bounds[1].first + h_for_y * j;

            result += f({x, y});
        }
    }

    result = result * h_for_x * h_for_y;

    return result;
}

double d3_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;
    double h_for_z = (bounds[2].second - bounds[2].first)/doubleStepsCount;

    double x = 0;
    double y = 0;
    double z = 0;

    double result = 0;

    result += 0.125 *
        (f({bounds[0].first, bounds[1].first, bounds[2].first}) +
        f({bounds[0].first, bounds[1].second, bounds[2].first}) +
        f({bounds[0].first, bounds[1].first, bounds[2].second}) +
        f({bounds[0].first, bounds[1].second, bounds[2].second}) +
        f({bounds[0].second, bounds[1].first, bounds[2].first}) +
        f({bounds[0].second, bounds[1].second, bounds[2].first}) +
        f({bounds[0].second, bounds[1].first, bounds[2].second}) +
        f({bounds[0].second, bounds[1].second, bounds[2].second}));
    for (int i = 1; i < N; i++) {
        x = bounds[0].first + h_for_x * i;
        y = bounds[1].first + h_for_y * i;
        z = bounds[2].first + h_for_z * i;

        result += 0.25 *
        (f({x, bounds[1].first, bounds[2].first}) +
        f({x, bounds[1].second, bounds[2].second}));

        result += 0.25 *
        (f({bounds[0].first, y, bounds[2].first}) +
        f({bounds[0].second, y, bounds[2].second}));

        result += 0.25 *
        (f({bounds[0].first, bounds[1].first, z}) +
        f({bounds[0].second, bounds[1].second, z}));
        for (int j = 1; j < N; j++) {
            x = bounds[0].first + h_for_x * i;
            z = bounds[2].first + h_for_z * j;

            result += 0.5 * (f({x, bounds[1].first, z}) +
            f({x, bounds[1].second, z}));

            y = bounds[1].first + h_for_y * i;

            result += 0.5 * (f({bounds[0].first, y, z}) +
            f({bounds[0].second, y, z}));

            y = bounds[1].first + h_for_y * j;

            result += 0.5 * (f({x, y, bounds[2].first}) +
            f({x, y, bounds[2].second}));

            for (int s = 1; s < N; s++) {
                z = bounds[2].first + h_for_z * s;

                result += f({x, y, z});
            }
        }
    }

    result = result * h_for_x * h_for_y * h_for_z;

    return result;
}

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int dimensions,
    int N) {
    if (dimensions != bounds.size()) {
        throw R"(The number of boundaries does not
        match the number of dimensions)";
    }
    if (dimensions == 1) {
        return d1_method(f, bounds, N);
    }
    if (dimensions == 2) {
        return d2_method(f, bounds, N);
    }
    if (dimensions == 3) {
        return d3_method(f, bounds, N);
    }
    return 0;
}
