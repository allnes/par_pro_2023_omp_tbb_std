// Copyright 2023 Chernishev Nikita

#include "../../../modules/task_1/chernishev_n_jarvis_seq/chernishev_n_jarvis_seq.h"


std::vector<dot> JarvisSeq(std::vector<dot> Dots) {
    std::vector<dot> res;

    dot first = *Dots.begin();
    for (auto dot : Dots) {
        if (first.y > dot.y) first = dot;
        if ((first.y == dot.y) && (first.x > dot.x)) first = dot;
    }
    res.push_back(first);

    auto second = Dots.begin();
    for (auto dot = Dots.begin(); dot != Dots.end(); ++dot) {
        if (getRotate(first, *dot) > getRotate(first, *second)) second = dot;
        if (getRotate(first, *dot) == getRotate(first, *second)) {
            if (getLen(first, *second) > getLen(first, *dot)) second = dot;
        }
    }
    res.push_back(*second);
    Dots.erase(second);

    while (true) {
        int ResSize = res.size();
        dot lastRes = res.at(ResSize - 1);
        dot prevLastRes = res.at(ResSize - 2);

        auto next = Dots.begin();
        for (auto i = Dots.begin(); i != Dots.end(); i++) {
            if (getCos(prevLastRes, lastRes, *next) >
                getCos(prevLastRes, lastRes, *i))
                next = i;
        }
        if (*next == first) {
            return res;
        } else {
            res.push_back(*next);
            Dots.erase(next);
        }
    }
}

bool isEqual(const std::vector<dot>& lhs, const std::vector<dot>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (int i = 0; i < rhs.size(); i++) {
        if (rhs.at(i) != lhs.at(i)) return false;
    }
    return true;
}
