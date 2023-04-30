// Copyright 2023 Strogantsev Anton
#include <gtest/gtest.h>
#include "./graham_con_hull_omp.h"

TEST(ConvexHullOMP, EmptyVector) {
    std::vector<Point> points;
    auto hull = constructConvexHull(points);
    EXPECT_TRUE(hull.empty());
}

TEST(ConvexHullOMP, ThreePoints) {
    std::vector<Point> points{ {0, 0}, {1, 1}, {0, 1} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 3);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(1, 1));
    EXPECT_EQ(hull[2], Point(0, 1));
}

TEST(ConvexHullOMP, FourPoints) {
    std::vector<Point> points{ {0, 0}, {1, 1}, {0, 1}, {1, 0} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 4);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(1, 0));
    EXPECT_EQ(hull[2], Point(1, 1));
    EXPECT_EQ(hull[3], Point(0, 1));
}

TEST(ConvexHullOMP, TenPoints) {
    std::vector<Point> points{
        {0, 0}, {10, 10}, {0, 10}, {10, 0}, {11, 11},
        {5, 5}, {3, 1}, {2, 4}, {7, 3}, {11, 11}
    };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 4);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(10, 0));
    EXPECT_EQ(hull[2], Point(11, 11));
    EXPECT_EQ(hull[3], Point(0, 10));
}

TEST(ConvexHullOMP, PointsInALine) {
    std::vector<Point> points{ {0, 0}, {1, 0}, {2, 0}, {3, 0} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 2);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(3, 0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
