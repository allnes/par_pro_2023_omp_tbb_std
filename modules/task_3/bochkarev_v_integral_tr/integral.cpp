// Copyright 2023 Bochkarev Vladimir
#include <tbb/tbb.h>
#include <time.h>
#include <functional>
#include <iostream>
#include "../../../modules/task_3/bochkarev_v_integral_tr/integral.h"

class trFunctor {
private:
    double hx,hy,hz;
    double a, c, e;
    double res;
    const std::function<double(double, double, double)> &fun;

public:
    explicit trFunctor(double _hx, double _hy, double _hz, double _a, double _c, double _e, 
    const std::function<double(double, double, double)> &_fun):
    hx(_hx), hy(_hy), hz(_hz), a(_a), c(_c), e(_e), res(0), fun(_fun) {}

    trFunctor(const trFunctor& f, tbb::split): hx(f.hx), hy(f.hy), hz(f.hz), a(f.a), c(f.c), e(f.e), res(0), fun(f.fun) {}

    void operator()(const tbb::blocked_range3d<int>& r) {
        int i = r.pages().begin(), i_end = r.pages().end();
        int j = r.rows().begin(), j_end = r.rows().end();
        int k = r.cols().begin(), k_end = r.cols().end();

        for(i = r.pages().begin(); i < i_end; i++)
            for(j = r.rows().begin(); j < j_end; j++)
                for(k = r.cols().begin(); k < k_end; k++) {
                    const double x1 = a + i*hx;
                    const double x2 = a + (i+1)*hx;

                    const double y1 = c + j*hy;
                    const double y2 = c + (j+1)*hy;

                    const double z1 = e + k*hz;
                    const double z2 = e + (k+1)*hz;

                    res+=0.5*(x2-x1)*(y2-y1)*(z2-z1)*(fun(x1, y1, z1)+fun(x2, y2, z2));
                }
    }

    void join(const trFunctor& f) {
        res += f.res;
    }

    double result() {
        return res;
    }
};

double integral3D(double a, double b, double c, double d, double e,
double f, int n, const std::function<double(double, double, double)> &fun) {
    double hx = (b-a)/n;
    double hy = (d-c)/n;
    double hz = (f-e)/n;

    trFunctor ftr(hx, hy, hz, a, c, e, fun);
    tbb::parallel_reduce(tbb::blocked_range3d<int>(0, n, 0, n, 0, n), ftr);
    return ftr.result();
}
