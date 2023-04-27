// Copyright 2023 Makarov Mikhail
#include <gtest/gtest.h>
#include "../../../modules/task_2/makarov_m_kanons_method/kanons_method.h"

TEST(KanonsMethodOMP, ThrowZeroThreads) {
    Matrix A = CreateRandomMatrix(3);
    Matrix B = CreateRandomMatrix(3);
    ASSERT_ANY_THROW(CannonAlg(A, B, 0));
}

TEST(KanonsMethodOMP, ThrowIncorrectresult1MatSizes) {
    Matrix A = CreateRandomMatrix(3);
    Matrix B = CreateRandomMatrix(4);
    ASSERT_ANY_THROW(CannonAlg(A, B, 4));
}

TEST(KanonsMethodOMP, MultTest12x12) {
    Matrix A = CreateRandomMatrix(12);
    Matrix B = CreateRandomMatrix(12);

    Matrix result1 = MultBlock(A, B, 4);
    Matrix result2 = CannonAlg(A, B, 4);
    EXPECT_TRUE(MatricesNear(result1, result2));
}

TEST(KanonsMethodOMP, MultTest3x3) {
    Matrix A = {{5.0, 6.0, 7.1},
                {2.3, 1.8, 2.3},
                {6.1, 2.5, 3.0}};
    Matrix B = {{1.5, 1.3, 1.2},
                {1.1, 1.0, 0.9},
                {0.8, 4.0, 7.0}};
    Matrix result = {{19.78, 40.9, 61.1},
                     {7.27, 13.99, 20.48},
                     {14.3, 22.43, 30.57}};
    EXPECT_TRUE(MatricesNear(result, CannonAlg(A, B, 4)));
}

TEST(KanonsMethodOMP, MultRandomTest4x4) {
    Matrix A = CreateRandomMatrix(4);
    Matrix B = CreateRandomMatrix(4);
    EXPECT_TRUE(MatricesNear(MultUsual(A, B), CannonAlg(A, B, 4)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
