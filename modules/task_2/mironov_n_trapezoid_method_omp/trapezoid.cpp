// Copyright 2023 Mironov Nikita
#include "../../../modules/task_2/mironov_n_trapezoid_method_omp/trapezoid.h"

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

double d1_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h = (bounds[0].second - bounds[0].first)/doubleStepsCount;

    double x = 0;

    double result = 0;
        #pragma omp parallel for reduction(+: result)
        for (int i = 1; i < N; i++) {
            x = bounds[0].first + h * i;
            result += h * f({x});
        }

    result += (h/2.0) * (f({bounds[0].first}) + f({bounds[0].second}));

    return result;
}

double d2_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;
    int i;
    int j;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;

    double x = 0;
    double y = 0;

    double result = 0;
    #pragma omp parallel shared(N, bounds, h_for_x, h_for_y, result) {
        #pragma omp for nowait reduction(+: result)
        for (i = 1; i <= N; i++) {
            x = bounds[0].first + h_for_x * i;
            y = bounds[1].first + h_for_y * i;

            result += 0.5 * (f({x, bounds[1].first}) +
            f({x, bounds[1].second}));

            result += 0.5 * (f({bounds[0].first, y}) +
            f({bounds[0].second, y}));
        }

        #pragma omp for nowait collapse(2) reduction(+: result)
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                x = bounds[0].first + h_for_x * i;
                y = bounds[1].first + h_for_y * j;

                result += f({x, y});
            }
        }
    }
    result += 0.25 *
        (f({bounds[0].first, bounds[1].first}) +
        f({bounds[0].second, bounds[1].second}) +
        f({bounds[0].first, bounds[1].second}) +
        f({bounds[0].second, bounds[1].first}));

    result = result * h_for_x * h_for_y;

    return result;
}

double d3_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;
    int i;
    int j;
    int s;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;
    double h_for_z = (bounds[2].second - bounds[2].first)/doubleStepsCount;

    double x = 0;
    double y = 0;
    double z = 0;

    double result = 0;
    #pragma omp parallel shared(N, bounds, h_for_x, h_for_y, h_for_z, result) {
        #pragma omp for nowait reduction(+: result)
        for (i = 1; i <= N; i++) {
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
        }

        #pragma omp for nowait collapse(2) reduction(+: result)
        for (i = 1; i <= N; i++) {
            x = bounds[0].first + h_for_x * i;
            y = bounds[1].first + h_for_y * i;
            for (j = 1; j <= N; j++) {
                z = bounds[2].first + h_for_z * j;

                result += 0.5 * (f({bounds[0].first, y, z}) +
                f({bounds[0].second, y, z}));

                result += 0.5 * (f({x, bounds[1].first, z}) +
                f({x, bounds[1].second, z}));

                y = bounds[1].first + h_for_y * j;

                result += 0.5 * (f({x, y, bounds[2].first}) +
                f({x, y, bounds[2].second}));

                y = bounds[1].first + h_for_y * i;
            }
        }

        #pragma omp for nowait collapse(3) reduction(+: result)
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                for (s = 1; s <= N; s++) {
                    x = bounds[0].first + h_for_x * i;
                    z = bounds[2].first + h_for_z * s;
                    y = bounds[1].first + h_for_y * j;

                    result += f({x, y, z});
                }
            }
        }
    }

    result += 0.125 *
        (f({bounds[0].first, bounds[1].first, bounds[2].first}) +
        f({bounds[0].first, bounds[1].second, bounds[2].first}) +
        f({bounds[0].first, bounds[1].first, bounds[2].second}) +
        f({bounds[0].first, bounds[1].second, bounds[2].second}) +
        f({bounds[0].second, bounds[1].first, bounds[2].first}) +
        f({bounds[0].second, bounds[1].second, bounds[2].first}) +
        f({bounds[0].second, bounds[1].first, bounds[2].second}) +
        f({bounds[0].second, bounds[1].second, bounds[2].second}));

    result = result * h_for_x * h_for_y * h_for_z;

    return result;
}

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int dimensions,
    int N,
    bool useOMP) {
    if (dimensions != bounds.size()) {
        throw R"(The number of boundaries does not
        match the number of dimensions)";
    }
    if (dimensions == 1 && useOMP == false) {
        return d1_method(f, bounds, N);
    }
    if (dimensions == 2 && useOMP == false) {
        return d2_method(f, bounds, N);
    }
    if (dimensions == 3 && useOMP == false) {
        return d3_method(f, bounds, N);
    }

    if (dimensions == 1 && useOMP == true) {
        return d1_method_Openmp(f, bounds, N);
    }
    if (dimensions == 2 && useOMP == true) {
        return d2_method_Openmp(f, bounds, N);
    }
    if (dimensions == 3 && useOMP == true) {
        return d3_method_Openmp(f, bounds, N);
    }
    return 0;
}
