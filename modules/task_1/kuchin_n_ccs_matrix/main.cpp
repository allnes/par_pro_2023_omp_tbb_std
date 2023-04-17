// Copyright 2022 Kuchin Nikita

#include <gtest/gtest.h>

#include <cmath>

#include "./ccs_matrix.h"

TEST(Str, test1) {
    SparceMatrix A;
    A.n = 3;
    A.data = {1.2, 3.4, 5.1};
    A.row_id = {2, 0, 0};
    A.col_ptr = {0, 1, 2, 3};
    SparceMatrix B;
    B.n = 3;
    B.data = {6.22, 2.18};
    B.row_id = {2, 1};
    B.col_ptr = {0, 1, 1, 2};
    SparceMatrix C;
    C.n = 3;
    C.data = {31.722, 7.412};
    C.row_id = {0, 0};
    C.col_ptr = {0, 1, 1, 2};
    SparceMatrix res = multiply(A, B);
    for (int i = 0; i < C.data.size(); i++) {
        ASSERT_TRUE(fabs(C.data[i] - res.data[i]) < 0.1);
    }
    EXPECT_EQ(C.row_id, res.row_id);
    EXPECT_EQ(C.col_ptr, res.col_ptr);
}

TEST(Str, test2) {
    SparceMatrix A;
    A.n = 4;
    A.data = {1.3, 7.5, 6.3, 2.1, 9.5};
    A.row_id = {0, 2, 1, 3, 2};
    A.col_ptr = {0, 1, 2, 4, 5};
    SparceMatrix B;
    B.n = 4;
    B.data = {1.4, 5.9, 8.3, 3.1, 2.2};
    B.row_id = {0, 1, 3, 1, 2};
    B.col_ptr = {0, 1, 3, 4, 5};
    SparceMatrix C;
    C.n = 4;
    C.data = {1.82, 123.1, 23.25, 13.86, 4.62};
    C.row_id = {
        0, 2, 2, 1, 3,
    };
    C.col_ptr = {0, 1, 2, 3, 5};
    SparceMatrix res = multiply(A, B);
    for (int i = 0; i < C.data.size(); i++) {
        ASSERT_TRUE(fabs(C.data[i] - res.data[i]) < 0.1);
    }
    EXPECT_EQ(C.row_id, res.row_id);
    EXPECT_EQ(C.col_ptr, res.col_ptr);
}

TEST(Str, test3) {
    SparceMatrix A;
    A.n = 6;
    A.data = {1, 7, 3, 4, 2, 2, 5};
    A.row_id = {0, 5, 1, 1, 3, 0, 3};
    A.col_ptr = {0, 1, 2, 3, 5, 6, 7};
    SparceMatrix B;
    B.n = 6;
    B.data = {3, 1, 2, 1, 3, 3, 4, 1};
    B.row_id = {0, 4, 5, 1, 4, 3, 5, 0};
    B.col_ptr = {0, 2, 3, 5, 6, 7, 8};
    SparceMatrix C;
    C.n = 6;
    C.data = {5, 10, 6, 7, 12, 6, 20, 1};
    C.row_id = {0, 3, 0, 5, 1, 3, 3, 0};
    C.col_ptr = {0, 1, 2, 4, 6, 7, 8};
    SparceMatrix res = multiply(A, B);
    for (int i = 0; i < C.data.size(); i++) {
        ASSERT_TRUE(fabs(C.data[i] - res.data[i]) < 0.1);
    }
    EXPECT_EQ(C.row_id, res.row_id);
    EXPECT_EQ(C.col_ptr, res.col_ptr);
}
TEST(Str, test4) {
    SparceMatrix A;
    A.n = 5;
    A.data = {8.85, 7.69, 2.56, 12.85, 19.47, 4.53, 15.81};
    A.row_id = {0, 3, 2, 3, 1, 3, 2};
    A.col_ptr = {0, 2, 3, 4, 6, 7};
    SparceMatrix B;
    B.n = 5;
    B.data = {9.77, 1.05, 8.38, 15.54, 8.07, 7.27, 6.24};
    B.row_id = {3, 1, 3, 4, 4, 1, 2};
    B.col_ptr = {0, 1, 2, 4, 5, 7};
    SparceMatrix C;
    C.n = 5;
    C.data = {190.2219, 44.2581,  2.688,   163.1586, 245.6874,
              37.9614,  127.5867, 18.6112, 80.184};
    C.row_id = {1, 3, 2, 1, 2, 3, 2, 2, 3};
    C.col_ptr = {0, 2, 3, 6, 7, 9};
    SparceMatrix res = multiply(A, B);
    for (int i = 0; i < C.data.size(); i++) {
        ASSERT_TRUE(fabs(C.data[i] - res.data[i]) < 0.1);
    }
    EXPECT_EQ(C.row_id, res.row_id);
    EXPECT_EQ(C.col_ptr, res.col_ptr);
}
TEST(Str, test5) {
    SparceMatrix A;
    A.n = 4;
    A.data = {1.5, 3.2, 8.7, 2.5, 3.3};
    A.row_id = {0, 2, 3, 1, 2};
    A.col_ptr = {0, 1, 3, 4, 5};
    SparceMatrix B;
    B.n = 4;
    B.data = {4.2, 7.8, 3.2, 1.1};
    B.row_id = {1, 2, 1, 3};
    B.col_ptr = {0, 1, 2, 3, 4};
    SparceMatrix C;
    C.n = 4;
    C.data = {13.44, 36.54, 19.5, 10.24, 27.84, 3.63};
    C.row_id = {2, 3, 1, 2, 3, 2};
    C.col_ptr = {0, 2, 3, 5, 6};
    SparceMatrix res = multiply(A, B);
    for (int i = 0; i < C.data.size(); i++) {
        ASSERT_TRUE(fabs(C.data[i] - res.data[i]) < 0.1);
    }
    EXPECT_EQ(C.row_id, res.row_id);
    EXPECT_EQ(C.col_ptr, res.col_ptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
