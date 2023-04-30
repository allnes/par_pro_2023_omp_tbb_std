// Copyright 2023 Zagrebin S.

#ifndef MODULES_TASK_2_ZAGREBIN_S_CCS_MULT_CCS_MULT_H_
#define MODULES_TASK_2_ZAGREBIN_S_CCS_MULT_CCS_MULT_H_

#include <iostream>
#include <complex>
#include <random>
#include <vector>

using Comp = std::complex<double>;

struct CCS {
    struct elem{ size_t row; Comp val; };

    size_t shape[2];  // rows and columns
    std::vector<elem> data;
    std::vector<size_t> offset;

    CCS(size_t n, size_t m);
    CCS(size_t n, size_t m, int c);
    CCS(size_t n, size_t m, const Comp* arr);
    CCS T() const;
    friend std::ostream &operator<<(std::ostream &os, const CCS &_m);
};

std::ostream& operator<<(std::ostream &os, const CCS &_m);

void fill(CCS* m, double p, std::default_random_engine* eng);

using it = std::vector<CCS::elem>::const_iterator;
inline Comp mult(it i, it a, it j, it b);

CCS mult(const CCS& _l, const CCS& r);

#endif  // MODULES_TASK_2_ZAGREBIN_S_CCS_MULT_CCS_MULT_H_
