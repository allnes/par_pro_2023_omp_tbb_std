// Copyright 2023 Bulgakov Daniil

#include "../../../modules/task_3/bulgakov_d_slau_gradient_tbb/slau_gradient.h"

#define NOMINMAX

#include <time.h>
#include <tbb/tbb.h>

// #define DEBUG

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

dvec tbb_matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());

    tbb::parallel_for(tbb::blocked_range<size_t>(0, a.size()),
    [&](const tbb::blocked_range<size_t>& r) {
        for (size_t i = r.begin(); i < r.end(); i++) {
            res[i] = vec_vec(a[i], b);
        }
    });

    return res;
}

class VecVecFunctor {
 private:
    const dvec a, b;
    double res;
 public:
    explicit VecVecFunctor(const dvec &v1, const dvec &v2):
    a(v1), b(v2), res(0) {}
    VecVecFunctor(const VecVecFunctor& f, tbb::split):
    a(f.a), b(f.b), res(0) {}
    void operator()(const tbb::blocked_range<size_t>& r) {
        size_t begin = r.begin();
        size_t end = r.end();
        res += std::inner_product((a.begin() + r.begin()),
                                  (a.begin() + r.end()),
                                  (b.begin() + r.begin()), 0.0);
    }
    void join(const VecVecFunctor& f) {
        res += f.res;
    }
    double result() {
        return res;
    }
};

double tbb_vec_vec(const dvec &a, const dvec &b) {
    double ans = 0;

    VecVecFunctor vf(a, b);
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0, a.size()), vf);

    return vf.result();
}

//----------------------------- Conjugate Method Algorithm --------------------


dvec solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    #ifdef DEBUG
    tbb::tick_count begin = tbb::tick_count::now();
    #endif

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

    #ifdef DEBUG
    tbb::tick_count end = tbb::tick_count::now();
    std::cout << "SEQ TIME " << (end - begin).seconds() << std::endl;
    #endif

    return res;
}

dvec tbb_solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    #ifdef DEBUG
    tbb::tick_count begin = tbb::tick_count::now();
    #endif

    for (int i = 0; i < a.size(); i++) {
        dvec r_prev;
        dvec mv = tbb_matrix_vec(a, p);
        r_prev = r;

        double d = tbb_vec_vec(r, r) / std::max(tbb_vec_vec(p, mv), SMOL);

        tbb::parallel_invoke(
        [&]{ res = vec_vec_comb(1.0, res, d, p); },
        [&]{ r = vec_vec_comb(1.0, r, -d, mv); });


        if (vec_norm(r) < SMOL) break;

        double s = tbb_vec_vec(r, r) /
                std::max(tbb_vec_vec(r_prev, r_prev), SMOL);

        p = vec_vec_comb(1.0, r, s, p);
    }

    #ifdef DEBUG
    tbb::tick_count end = tbb::tick_count::now();
    std::cout << "PARALLEL TIME " << (end - begin).seconds() << std::endl;
    #endif

    return res;
}
