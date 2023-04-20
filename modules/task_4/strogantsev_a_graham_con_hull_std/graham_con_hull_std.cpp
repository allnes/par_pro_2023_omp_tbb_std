// Copyright 2023 Strogantsev Anton
#include <algorithm>
#include <iterator>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../../modules/task_4/strogantsev_a_graham_con_hull_std/graham_con_hull_std.h"


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

    const int threadCount = std::thread::hardware_concurrency();
    const int step = (points.size() / threadCount) + (points.size() % threadCount != 0);

    auto promises = std::vector<std::promise<std::vector<Point>>>(threadCount);
    auto futures = std::vector<std::future<std::vector<Point>>>(threadCount);
    auto threads = std::vector<std::thread>();

    for (int i = 0; i < threadCount; i++) {
        futures[i] = promises[i].get_future();
        threads.push_back(std::thread([&](int i, std::promise<std::vector<Point>> promise) {
            std::vector<Point> localStack;

            auto left = pointsCopy.begin() + step * i;
            auto right = pointsCopy.begin() + std::min(step * (i + 1), static_cast<int>(points.size()));

            for (const Point& point : std::vector<Point>(left, right)) {
                while (localStack.size() > 1 &&
                    getOrientation(localStack[localStack.size() - 2], localStack.back(), point) != Orientation::RIGHT)
                    localStack.pop_back();
                localStack.push_back(point);
            }

            promise.set_value(std::move(localStack));
        }, i, std::move(promises[i])));
    }

    std::vector<Point> result;
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
        auto localStack = futures[i].get();
        std::copy(localStack.begin(), localStack.end(), std::back_inserter(result));
    }

    return constructConvexHullSeq(result);
}
