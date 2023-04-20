// Copyright 2023 Strogantsev Anton
#include <tbb/tbb.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "../../../modules/task_3/strogantsev_a_graham_con_hull_tbb/graham_con_hull_tbb.h"


enum class Orientation {
    COLLINEAR,
    LEFT,
    RIGHT,
};

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

struct ConvexHullTbbMediator {
    mutable std::vector<Point> stack;

    ConvexHullTbbMediator() = default;
    ConvexHullTbbMediator(const ConvexHullTbbMediator& s, tbb::split) {}

    void operator()(const tbb::blocked_range<std::vector<Point>::iterator>& points) {
        for (const Point& point : points) {
            while (stack.size() > 1 &&
                getOrientation(stack[stack.size() - 2], stack.back(), point) != Orientation::RIGHT)
                stack.pop_back();
            stack.push_back(point);
        }
    }
    void join(const ConvexHullTbbMediator& r) {
        std::copy(r.stack.begin(), r.stack.end(), std::back_inserter(stack));
    }
};

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

    ConvexHullTbbMediator mediator;
    tbb::parallel_reduce(
        tbb::blocked_range<std::vector<Point>::iterator>(pointsCopy.begin(), pointsCopy.end()),
        mediator);

    return constructConvexHullSeq(mediator.stack);
}
