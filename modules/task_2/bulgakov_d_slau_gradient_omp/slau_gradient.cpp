// Copyright 2023 Bulgakov Daniil

#include "../../../modules/task_2/bulgakov_d_slau_gradient_omp/slau_gradient.h"

#include <omp.h>
#include <time.h>

//----------------------------- Test Data Generation --------------------------

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

//----------------------------- Sequential Computing Methods ------------------

double vec_vec(const dvec &a, const dvec &b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

dvec matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] =  vec_vec(a[i], b);
    }
    return res;
}

dvec vec_vec_comb(double ma, const dvec& a, double mb, const dvec& b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] = ma * a[i] + mb * b[i];
    }
    return res;
}

double vec_norm(const dvec& a) {
    return sqrt(vec_vec(a, a));
}

//----------------------------- Parallel Computing Methods --------------------

dvec omp_matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());
    #pragma omp parallel for
    for (int i = 0; i < a.size(); i++) {
        res[i] =  vec_vec(a[i], b);
    }
    return res;
}

double omp_vec_vec(const dvec &a, const dvec &b) {
    double res = 0.0;
    #pragma omp parallel for reduction(+:res)
    for (int i = 0; i < a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}

//----------------------------- Conjugate Method Algorithm --------------------


dvec solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    double begin = omp_get_wtime();

    for (int i = 0; i < a.size(); i++) {
        dvec r_prev;
        dvec mv = matrix_vec(a, p);
        r_prev = r;

        double d = vec_vec(r, r) / std::max(vec_vec(p, mv), SMOL);
        res = vec_vec_comb(1.0, res, d, p);
        r = vec_vec_comb(1.0, r, -d, mv);

        if (vec_norm(r) < SMOL) break;

        double s = vec_vec(r, r) / std::max(vec_vec(r_prev, r_prev), SMOL);
        p = vec_vec_comb(1.0, r, s, p);
    }

    double end = omp_get_wtime();

    // std::cout << "SEQ TIME " << (end - begin) << std::endl;

    return res;
}

dvec omp_solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    double begin = omp_get_wtime();

    for (int i = 0; i < a.size(); i++) {
        dvec r_prev;
        dvec mv = omp_matrix_vec(a, p);
        r_prev = r;

        double d = omp_vec_vec(r, r) / std::max(omp_vec_vec(p, mv), SMOL);

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

        if (vec_norm(r) < SMOL) break;

        double s = omp_vec_vec(r, r) /
                std::max(omp_vec_vec(r_prev, r_prev), SMOL);

        p = vec_vec_comb(1.0, r, s, p);
    }

    double end = omp_get_wtime();

    // std::cout << "PARALLEL TIME " << (end - begin) << std::endl;

    return res;
}
