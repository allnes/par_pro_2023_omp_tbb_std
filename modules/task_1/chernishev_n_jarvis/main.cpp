// Copyright 2023 Chernyshev Nikita

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <list>
#include <random>

struct dot {
    double x;
    double y;
    dot(int _x, int _y) : x(_x), y(_y) {}
    bool operator==(dot b) {
        return ((x == b.x) && (y == b.y)) ? (true) : (false);
    }
    bool operator!=(dot b) { return !operator==(b); }
};

double getRotate(dot a, dot b) {
    double res = atan2(b.y - a.y, b.x - a.x);
    if (res < 0) res += 2 * M_PI;
    return res;
}

double getLen(dot a, dot b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double getCos(dot A, dot O, dot B) {
    double mult = (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
    double len1 = sqrt(pow(A.x - O.x, 2) + pow(A.y - O.y, 2));
    double len2 = sqrt(pow(B.x - O.x, 2) + pow(B.y - O.y, 2));
    return mult / (len1 * len2);
}

std::list<dot> JarvisSeq(std::list<dot> Dots) {
    std::list<dot> res;

    dot first = *Dots.begin();
    for (auto dot : Dots) {
        if (first.y > dot.y) first = dot;
        if ((first.y == dot.y) && (first.x > dot.x)) first = dot;
    }
    res.push_back(first);

    dot second = *Dots.begin();
    for (auto dot : Dots) {
        if (getRotate(first, dot) > getRotate(first, second)) second = dot;
        if (getRotate(first, dot) == getRotate(first, second)) {
            if (getLen(first, second) > getLen(first, dot)) second = dot;
        }
    }
    res.push_back(second);
    Dots.remove(second);

    while (true) {
        auto iter = res.end();
        --iter;
        dot lastRes = *iter;
        --iter;
        dot prevLastRes = *iter;

        dot next = *Dots.begin();
        for (auto i : Dots) {
            if (getCos(prevLastRes, lastRes, next) >
                getCos(prevLastRes, lastRes, i))
                next = i;
        }
        if (next == first) {
            return res;
        } else {
            res.push_back(next);
            Dots.remove(next);
        }
    }
}

bool isEQUAL(std::list<dot> A, std::list<dot> B) {
    if (A.size() != B.size()) return false;
    auto j = B.begin();
    for (auto i = A.begin(); i != A.end(); ++i) {
        if (*i != *j) return false;
        ++j;
    }
    return true;
}

TEST(Sequential, Test_Jurvis_100) {
    std::list<dot> testList{
        dot(83, 86), dot(77, 15), dot(93, 35), dot(86, 92), dot(49, 21),
        dot(62, 27), dot(90, 59), dot(63, 26), dot(40, 26), dot(72, 36),
        dot(11, 68), dot(67, 29), dot(82, 30), dot(62, 23), dot(67, 35),
        dot(29, 2),  dot(22, 58), dot(69, 67), dot(93, 56), dot(11, 42),
        dot(29, 73), dot(21, 19), dot(84, 37), dot(98, 24), dot(15, 70),
        dot(13, 26), dot(91, 80), dot(56, 73), dot(62, 70), dot(96, 81),
        dot(5, 25),  dot(84, 27), dot(36, 5),  dot(46, 29), dot(13, 57),
        dot(24, 95), dot(82, 45), dot(14, 67), dot(34, 64), dot(43, 50),
        dot(87, 8),  dot(76, 78), dot(88, 84), dot(3, 51),  dot(54, 99),
        dot(32, 60), dot(76, 68), dot(39, 12), dot(26, 86), dot(94, 39),
        dot(95, 70), dot(34, 78), dot(67, 1),  dot(97, 2),  dot(17, 92),
        dot(52, 56), dot(1, 80),  dot(86, 41), dot(65, 89), dot(44, 19),
        dot(40, 29), dot(31, 17), dot(97, 71), dot(81, 75), dot(9, 27),
        dot(67, 56), dot(97, 53), dot(86, 65), dot(6, 83),  dot(19, 24),
        dot(28, 71), dot(32, 29), dot(3, 19),  dot(70, 68), dot(8, 15),
        dot(40, 49), dot(96, 23), dot(18, 45), dot(46, 51), dot(21, 55),
        dot(79, 88), dot(64, 28), dot(41, 50), dot(93, 0),  dot(34, 64),
        dot(24, 14), dot(87, 56), dot(43, 91), dot(27, 65), dot(59, 36),
        dot(32, 51), dot(37, 28), dot(75, 7),  dot(74, 21), dot(58, 95),
        dot(29, 37), dot(35, 93), dot(18, 28), dot(43, 11), dot(28, 29)};
    std::list<dot> testRes{dot(93, 0),  dot(29, 2),  dot(8, 15),  dot(3, 19),
                           dot(1, 80),  dot(17, 92), dot(24, 95), dot(54, 99),
                           dot(86, 92), dot(96, 81), dot(97, 71), dot(98, 24),
                           dot(97, 2)};
    std::list<dot> res = JarvisSeq(testList);

    EXPECT_TRUE(isEQUAL(testRes, res));
}
TEST(Sequential, Test_Jurvis_50) {
    std::list<dot> testList{
        dot(76, 4),  dot(43, 63), dot(13, 38), dot(6, 40),  dot(4, 18),
        dot(28, 88), dot(69, 17), dot(17, 96), dot(24, 43), dot(70, 83),
        dot(90, 99), dot(72, 25), dot(44, 90), dot(5, 39),  dot(54, 86),
        dot(69, 82), dot(42, 64), dot(97, 7),  dot(55, 4),  dot(48, 11),
        dot(22, 28), dot(99, 43), dot(46, 68), dot(40, 22), dot(11, 10),
        dot(5, 1),   dot(61, 30), dot(78, 5),  dot(20, 36), dot(44, 26),
        dot(22, 65), dot(8, 16),  dot(82, 58), dot(24, 37), dot(62, 24),
        dot(0, 36),  dot(52, 99), dot(79, 50), dot(68, 71), dot(73, 31),
        dot(81, 30), dot(33, 94), dot(60, 63), dot(99, 81), dot(99, 96),
        dot(59, 73), dot(13, 68), dot(90, 95), dot(26, 66), dot(84, 40)};
    std::list<dot> testRes{dot(5, 1),   dot(0, 36),  dot(17, 96),
                           dot(52, 99), dot(90, 99), dot(99, 96),
                           dot(99, 43), dot(97, 7),  dot(76, 4)};
    std::list<dot> res = JarvisSeq(testList);

    EXPECT_TRUE(isEQUAL(testRes, res));
}
TEST(Sequential, Test_Sum_10) {
    std::list<dot> testList{dot(90, 84), dot(76, 42), dot(36, 7),  dot(45, 56),
                            dot(79, 18), dot(87, 12), dot(48, 72), dot(59, 9),
                            dot(36, 10), dot(42, 87)};
    std::list<dot> testRes{dot(36, 7),  dot(36, 10), dot(42, 87),
                           dot(90, 84), dot(87, 12), dot(59, 9)};
    std::list<dot> res = JarvisSeq(testList);

    EXPECT_TRUE(isEQUAL(testRes, res));
}
TEST(Sequential, Test_Sum_20) {
    std::list<dot> testList{dot(6, 1),   dot(13, 72), dot(21, 55), dot(19, 99),
                            dot(21, 4),  dot(39, 11), dot(40, 67), dot(5, 28),
                            dot(27, 50), dot(84, 58), dot(20, 24), dot(22, 69),
                            dot(96, 81), dot(30, 84), dot(92, 72), dot(72, 50),
                            dot(25, 85), dot(22, 99), dot(40, 42), dot(98, 13)};
    std::list<dot> testRes{dot(6, 1),   dot(5, 28),  dot(13, 72), dot(19, 99),
                           dot(22, 99), dot(96, 81), dot(98, 13)};
    std::list<dot> res = JarvisSeq(testList);

    EXPECT_TRUE(isEQUAL(testRes, res));
}
TEST(Sequential, Test_Sum_120) {
    std::list<dot> testList{
        dot(98, 90), dot(24, 90), dot(9, 81),  dot(19, 36), dot(32, 55),
        dot(94, 4),  dot(79, 69), dot(73, 76), dot(50, 55), dot(60, 42),
        dot(79, 84), dot(93, 5),  dot(21, 67), dot(4, 13),  dot(61, 54),
        dot(26, 59), dot(44, 2),  dot(2, 6),   dot(84, 21), dot(42, 68),
        dot(28, 89), dot(72, 8),  dot(58, 98), dot(36, 8),  dot(53, 48),
        dot(3, 33),  dot(33, 48), dot(90, 54), dot(67, 46), dot(68, 29),
        dot(0, 46),  dot(88, 97), dot(49, 90), dot(3, 33),  dot(63, 97),
        dot(53, 92), dot(86, 25), dot(52, 96), dot(75, 88), dot(57, 29),
        dot(36, 60), dot(14, 21), dot(60, 4),  dot(28, 27), dot(50, 48),
        dot(56, 2),  dot(94, 97), dot(99, 43), dot(39, 2),  dot(28, 3),
        dot(0, 81),  dot(47, 38), dot(59, 51), dot(35, 34), dot(39, 92),
        dot(15, 27), dot(4, 29),  dot(49, 64), dot(85, 29), dot(43, 35),
        dot(77, 0),  dot(38, 71), dot(49, 89), dot(67, 88), dot(92, 95),
        dot(43, 44), dot(29, 90), dot(82, 40), dot(41, 69), dot(26, 32),
        dot(61, 42), dot(60, 17), dot(23, 61), dot(81, 9),  dot(90, 25),
        dot(96, 67), dot(77, 34), dot(90, 26), dot(24, 57), dot(14, 68),
        dot(5, 58),  dot(12, 86), dot(0, 46),  dot(26, 94), dot(16, 52),
        dot(78, 29), dot(46, 90), dot(47, 70), dot(51, 80), dot(31, 93),
        dot(57, 27), dot(12, 86), dot(14, 55), dot(12, 90), dot(12, 79),
        dot(10, 69), dot(89, 74), dot(55, 41), dot(20, 33), dot(87, 88),
        dot(38, 66), dot(70, 84), dot(56, 17), dot(6, 60),  dot(49, 37),
        dot(5, 59),  dot(17, 18), dot(45, 83), dot(73, 58), dot(73, 37),
        dot(89, 83), dot(7, 78),  dot(57, 14), dot(71, 29), dot(0, 59),
        dot(18, 38), dot(25, 88), dot(74, 33), dot(57, 81), dot(93, 58)};
    std::list<dot> testRes{dot(77, 0),  dot(39, 2),  dot(28, 3),  dot(2, 6),
                           dot(0, 46),  dot(0, 81),  dot(12, 90), dot(26, 94),
                           dot(58, 98), dot(94, 97), dot(98, 90), dot(99, 43),
                           dot(94, 4)};
    std::list<dot> res = JarvisSeq(testList);

    EXPECT_TRUE(isEQUAL(testRes, res));
}
