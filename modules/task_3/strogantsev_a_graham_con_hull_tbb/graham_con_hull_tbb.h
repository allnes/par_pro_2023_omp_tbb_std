// Copyright 2023 Strogantsev Anton
#ifndef MODULES_TASK_3_STROGANTSEV_A_GRAHAM_CON_HULL_TBB_GRAHAM_CON_HULL_TBB_H_
#define MODULES_TASK_3_STROGANTSEV_A_GRAHAM_CON_HULL_TBB_GRAHAM_CON_HULL_TBB_H_

#include <vector>

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

std::vector<Point> constructConvexHull(const std::vector<Point>& points);

#endif  // MODULES_TASK_3_STROGANTSEV_A_GRAHAM_CON_HULL_TBB_GRAHAM_CON_HULL_TBB_H_
