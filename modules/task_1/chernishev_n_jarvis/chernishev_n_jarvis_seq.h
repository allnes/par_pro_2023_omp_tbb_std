// Copyright 2023 Chernishev Nikita

#ifndef MODULES_TASK_1_CHERNISHEV_N_JARVIS_SEQ_CHERNISHEV_N_JARVIS_SEQ_H_
#define MODULES_TASK_1_CHERNISHEV_N_JARVIS_SEQ_CHERNISHEV_N_JARVIS_SEQ_H_
#include <cmath>
#include <random>
#include <vector>

struct dot {
    double x;
    double y;
    dot(int _x, int _y) : x(_x), y(_y) {}

    dot() {  // random dot
        std::random_device rd;
        std::mt19937 gen_x(rd());
        std::mt19937 gen_y(rd());

        int _x = static_cast<int>(gen_x());
        int _y = static_cast<int>(gen_y());

        x = _x % 100;
        y = _y % 100;
    }

    friend bool operator==(const dot& lhs, const dot& rhs) {
        return ((lhs.x == rhs.x) && (lhs.y == rhs.y)) ? (true) : (false);
    }

    friend bool operator!=(const dot& lhs, const dot& rhs) {
        return !(lhs == rhs);
    }

    friend double getRotate(const dot& a, const dot& b) {
        double res = atan2(b.y - a.y, b.x - a.x);
        if (res < 0) res += 2 * M_PI;
        return res;
    }

    friend double getLen(const dot& a, const dot& b) {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    }

    friend double getCos(const dot& A, const dot& O, const dot& B) {
        double mult = (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
        double len1 = sqrt(pow(A.x - O.x, 2) + pow(A.y - O.y, 2));
        double len2 = sqrt(pow(B.x - O.x, 2) + pow(B.y - O.y, 2));
        return mult / (len1 * len2);
    }
};

std::vector<dot> JarvisSeq(std::vector<dot> Dots);
bool isEqual(const std::vector<dot>& lhs, const std::vector<dot>& rhs);

#endif  // MODULES_TASK_1_CHERNISHEV_N_JARVIS_SEQ_CHERNISHEV_N_JARVIS_SEQ_H_
