// Copyright 2023 Yurin Evgeny

#include "../../../modules/task_3/yurin_e_slau_gradient_tbb/slau_gradient.h"

dmat generateMatrix(int size, unsigned int seed) {
    dmat res = dmat(size, std::vector<double>(size));
    dvec v = generateVector(size, seed);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res[i][j] = v[i] * v[j];
        }
        res[i][i] += size;
    }
    return res;
}
dvec generateVector(int size, unsigned int seed) {
    dvec res = dvec(size);
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> urd(-5, 5);
    for (int i = 0; i < size; i++) {
        res[i] = urd(mt);
    }
    return res;
}

double scalarProduct(const dvec &a, const dvec &b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

dvec matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] =  scalarProduct(a[i], b);
    }
    return res;
}

dvec vec_vec_comb(double firstScalar, const dvec& firstVector, double secondScalar, const dvec& secondVector) {
    dvec res(firstVector.size());
    for (int i = 0; i < firstVector.size(); i++) {
        res[i] = firstScalar * firstVector[i] + secondScalar * secondVector[i];
    }
    return res;
}

dvec matrix_vec_parallel(const dmat &a, const dvec &b) {
    dvec res(a.size());
    #pragma omp parallel for
    for (int i = 0; i < a.size(); i++) {
        res[i] =  scalarProduct(a[i], b);
    }
    return res;
}

dvec solve(const dmat &matrix, const dvec& vector) {
    dvec res(matrix.size(), 0.0);

    dvec r(vector);
    dvec p(r);

    int k = 0;

    while (k++ < matrix.size()) {
        dvec r_prev;
        dvec mv = matrix_vec(matrix, p);
        r_prev = r;

        double d = scalarProduct(r, r) / std::max(scalarProduct(p, mv), EPS);
        res = vec_vec_comb(1.0, res, d, p);
        r = vec_vec_comb(1.0, r, -d, mv);

        if (sqrt(scalarProduct(r, r)) < EPS) break;

        double s = scalarProduct(r, r) / std::max(scalarProduct(r_prev, r_prev), EPS);
        p = vec_vec_comb(1.0, r, s, p);
    }
    return res;
}

dvec solve_parallel(const dmat &matrix, const dvec& vector) {
    dvec res(matrix.size(), 0.0);

    dvec r(vector);
    dvec p(r);

    int k = 0;

    while (k++ < matrix.size()) {
        dvec r_prev;
        dvec mv = matrix_vec_parallel(matrix, p);
        r_prev = r;

        double d = scalarProduct(r, r) / std::max(scalarProduct(p, mv), EPS);
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                 res = vec_vec_comb(1.0, res, d, p);
            }
            #pragma omp section
            {
                r = vec_vec_comb(1.0, r, -d, mv);
            }
        }
        if (sqrt(scalarProduct(r, r)) < EPS) break;

        double s = scalarProduct(r, r) / std::max(scalarProduct(r_prev, r_prev), EPS);
        p = vec_vec_comb(1.0, r, s, p);
    }
    return res;
}
