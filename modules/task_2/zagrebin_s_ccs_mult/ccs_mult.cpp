// Copyright 2023 Zagrebin S.

#include <omp.h>
#include <list>
#include <random>
#include "../../../modules/task_2/zagrebin_s_ccs_mult/ccs_mult.h"

CCS::CCS(size_t n, size_t m): shape{n, m}, offset(m+1) {}

CCS::CCS(size_t n, size_t m, int c): shape{n, m}, offset(m+1), data(c) {}

CCS::CCS(size_t n, size_t m, const Comp* arr): shape{n, m}, offset(m+1) {
    offset[0] = 0;
    for (size_t i = 0; i < shape[1]; ++i) {
        size_t n = 0;
        for (size_t j = 0; j < shape[0]; ++j) {
            Comp x = arr[j * shape[1] + i];
            if (std::abs(x) > 0.0001) {
                data.push_back({j, x});
                ++n;
            }
        }
        offset[i+1] = offset[i] + n;
    }
}

CCS CCS::T() const {
    CCS res(shape[1], shape[0], data.size());

    std::vector<size_t> count(shape[0]);  // count elements in row
    for (auto const &elem : data)
        ++count[elem.row];

    res.offset[0] = 0;
    for (size_t i = 1; i < shape[0]+1; ++i)
        res.offset[i] = res.offset[i-1] + count[i-1];

    for (size_t i = 0; i < shape[1]; ++i)
        for (size_t j = offset[i]; j < offset[i+1]; ++j) {
            size_t row = data[j].row;
            size_t offset = res.offset[row];

            res.data[offset].val = data[j].val;
            res.data[offset].row = i;
            ++res.offset[row];
        }

    for (size_t i = res.offset.size()-1; i > 0; --i)
        res.offset[i] = res.offset[i-1];
    res.offset[0] = 0;
    return res;
}

std::ostream& operator<<(std::ostream &os, const CCS &_m) {
    CCS m(_m.T());
    size_t elem_ind = 0;

    for (size_t i = 0; i < _m.shape[0]; ++i) {
        for (size_t j = 0; j < _m.shape[1]; ++j) {
            if (elem_ind < m.offset[i+1] && m.data[elem_ind].row == j) {
                os << m.data[elem_ind++].val << ' ';
            } else {
                os << "0 ";
            }
        }
        os << '\n';
    }
    return os;
}

void fill(CCS* m, double p, std::default_random_engine* eng) {
    std::uniform_real_distribution<double> coin(0, 1);
    std::uniform_int_distribution<int> cube(-5, 5);

    m->offset[0] = 0;
    for (size_t i = 0; i < m->shape[1]; ++i) {
        size_t n = 0;
        for (size_t j = 0; j < m->shape[0]; ++j)
            if (coin(*eng) < p) {
                Comp x{static_cast<double>(cube(*eng)),
                       static_cast<double>(cube(*eng))};
                m->data.push_back({j, x});
                ++n;
            }
        m->offset[i+1] = m->offset[i] + n;
    }
}

inline Comp mult(it i, it a, it j, it b) {
    Comp res{};
    while (i != a && j != b)
        if (i->row == j->row)
            res += (i++)->val * (j++)->val;
        else if (i->row < j->row)
            ++i;
        else
            ++j;

    return res;
}

CCS mult(const CCS& _l, const CCS& r) {
    CCS res(_l.shape[0], r.shape[1]);
    CCS l(_l.T());
    std::vector<std::list<CCS::elem>> tmp(res.shape[1]);

    res.offset[0] = 0;
    #pragma omp parallel for
    for (int i = 0; i < res.shape[1]; ++i) {  //  col from right
        //  #pragma omp parallel for
        for (size_t j = 0; j < res.shape[0]; ++j) {  //  row from left
            Comp x = mult(l.data.cbegin()+l.offset[j],
                          l.data.cbegin()+l.offset[j+1],
                          r.data.cbegin()+r.offset[i],
                          r.data.cbegin()+r.offset[i+1]);
            if (std::abs(x) > 0.0001) {
                tmp[i].push_back(CCS::elem{j, x});
            }
        }
    }

    size_t offset = 0;
    for (size_t i = 0; i < res.shape[1]; ++i)
        res.offset[i+1] = (offset += tmp[i].size());
    res.data.reserve(offset);

    for (size_t i = 0; i < res.shape[1]; ++i)
        for (const auto &x : tmp[i]) {
            res.data.push_back(x);
        }

    return res;
}
