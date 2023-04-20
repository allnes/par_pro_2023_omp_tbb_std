// Copyright 2023 Strogantsev Anton
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "../../../modules/task_2/strogantsev_a_graham_con_hull_omp/graham_con_hull_omp.h"


Orientation getOrientation(const Point& p1, const Point& p2, const Point& anchor) {
    int value = (p2.y - p1.y) * (anchor.x - p2.x) - (p2.x - p1.x) * (anchor.y - p2.y);
    if (value == 0) return Orientation::COLLINEAR;
    if (value > 0) return Orientation::LEFT;
    return Orientation::RIGHT;
}

bool comparePointsOnAnchor(const Point& p1, const Point& p2, const Point& anchor) {
    auto orientation = getOrientation(anchor, p1, p2);
    if (orientation == Orientation::COLLINEAR)
        return ((p1.x - anchor.x) * (p1.x - anchor.x) + (p1.y - anchor.y) * (p1.y - anchor.y))
        < ((p2.x - anchor.x) * (p2.x - anchor.x) + (p2.y - anchor.y) * (p2.y - anchor.y));
    return orientation == Orientation::RIGHT;
}

std::vector<Point> constructConvexHullSeq(const std::vector<Point>& points) {
    if (points.size() < 3) return points;

    auto pointsCopy = std::vector<Point>(points.begin(), points.end());

    Point anchor = *std::min_element(pointsCopy.begin(), pointsCopy.end(), [](const Point& p1, const Point& p2) {
        if (p1.y == p2.y) return p1.x < p2.x;
        return p1.y < p2.y;
    });

    std::sort(pointsCopy.begin(), pointsCopy.end(), [&](const Point& p1, const Point& p2) {
        return comparePointsOnAnchor(p1, p2, anchor);
    });

    std::vector<Point> stack;
    stack.push_back(pointsCopy[0]);
    stack.push_back(pointsCopy[1]);
    stack.push_back(pointsCopy[2]);

    for (int i = 3; i < pointsCopy.size(); i++) {
        while (stack.size() > 1 &&
            getOrientation(stack[stack.size() - 2], stack.back(), pointsCopy[i]) != Orientation::RIGHT)
            stack.pop_back();
        stack.push_back(pointsCopy[i]);
    }
    return stack;
}

std::vector<Point> constructConvexHull(const std::vector<Point>& points) {
    if (points.empty()) return points;

    Point anchor = *std::min_element(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        if (p1.y == p2.y) return p1.x < p2.x;
        return p1.y < p2.y;
    });

    auto pointsCopy = points;
    std::sort(pointsCopy.begin(), pointsCopy.end(), [&](const Point& p1, const Point& p2) {
        return comparePointsOnAnchor(p1, p2, anchor);
    });

    if (points.size() < 3) return pointsCopy;

    std::vector<Point> stack;
    stack.push_back(pointsCopy[0]);
    stack.push_back(pointsCopy[1]);

#pragma omp parallel
    {
        const int threadId = omp_get_thread_num();
        const int threadCount = omp_get_num_threads();
        const int step = (points.size() - 2) / threadCount + (((points.size() - 2) % threadCount) != 0);
        std::vector<Point> localStack;
        for (int i = 2 + threadId * step;
            i < std::min(static_cast<int>(pointsCopy.size()), 2 + step * (threadId + 1)); i++) {
            while (localStack.size() > 1 &&
                getOrientation(localStack[localStack.size() - 2], localStack.back(), pointsCopy[i]) !=
                Orientation::RIGHT)
                localStack.pop_back();
            localStack.push_back(pointsCopy[i]);
        }
#pragma omp critical
        {
            std::copy(localStack.begin(), localStack.end(), std::back_inserter(stack));
        }
    }
    return constructConvexHullSeq(stack);
}
