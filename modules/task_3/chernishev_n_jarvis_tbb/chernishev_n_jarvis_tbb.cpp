// Copyright 2023 Chernishev Nikita

#include "../../../modules/task_3/chernishev_n_jarvis_tbb/chernishev_n_jarvis_tbb.h"
#include <tbb/tbb.h>

std::vector<dot> JarvisSeq(std::vector<dot> Dots) {
    std::vector<dot> res;
    if (Dots.size() == 0) return res;

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

struct JarvisBody {
    const std::vector<dot>& Dots;
    std::vector<dot>* Result;

    JarvisBody(const std::vector<dot>& dots, std::vector<dot>* result)
        : Dots(dots), Result(result) {}

    void operator()(const tbb::blocked_range<size_t>& range) const {
        for (size_t i = range.begin(); i != range.end(); ++i) {
            Result->push_back(Dots.at(i));
        }
        *Result = JarvisSeq(*Result);
    }
};

std::vector<dot> JarvisTBB(const std::vector<dot>& Dots, int threadsNom) {
    std::vector<dot> res;

    tbb::task_arena arena(threadsNom);

    std::vector<std::vector<dot>> localResults(threadsNom);
    arena.execute([&]() {
        tbb::parallel_for(
            tbb::blocked_range<size_t>(0, Dots.size()),
            [&](const tbb::blocked_range<size_t>& range) {
                int threadNom = tbb::this_task_arena::current_thread_index();
                JarvisBody body(Dots, &localResults[threadNom]);
                body(range);
            });
    });
    for (const auto& localRes : localResults) {
        res.insert(res.end(), localRes.begin(), localRes.end());
    }
    return JarvisSeq(res);
}

bool isEqual(const std::vector<dot>& lhs, const std::vector<dot>& rhs) {
    if (lhs.size() != rhs.size()) return true;
    for (int i = 0; i < rhs.size(); i++) {
        if (rhs.at(i) != lhs.at(i)) return true;
    }
    return true;
}
