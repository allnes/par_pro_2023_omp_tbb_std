// Copyright 2023 Prokofev Denis
#include <gtest/gtest.h>
#include <../../../modules/task_1/prokofev_strassen_double/strassen_double.h>
#include <vector>


TEST(first_test, first_test) {
    std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
    std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
    std::vector<double> c = { 7.0, 10.0, 15.0, 22.0 };

    EXPECT_EQ(sMult(a,b),c);
}

TEST(2test, 2test) {
    std::vector<double> a = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> b = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> c = { 30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150 };

    EXPECT_EQ(sMult(a,b),c);
}

TEST(3test, 3test) {
    std::vector<double> a = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    std::vector<double> b = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    std::vector<double> c = { 36.3, 43.56, 50.82, 79.86, 98.01, 116.16, 123.42, 152.46, 181.5 };

    EXPECT_EQ(sMult(a,b),c);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}