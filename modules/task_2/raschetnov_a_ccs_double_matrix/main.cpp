// Copyright 2023 Raschetnov Alexei

#include <gtest/gtest.h>
#include <iostream>
#include "../../../modules/task_2/raschetnov_a_ccs_double_matrix/ccs_double_matrix.h"

TEST(OMP_task, test1) {
    std::vector<double> values_a = {1.5, 5.6, 9, 3.4, 8.9};
    std::vector<int> rows_a = {0, 2, 0, 0, 1};
    std::vector<int> pointer_a = {0, 2, 3, 5};

    std::vector<double> values_b = {1.9, 5, 1.6, 2, 7.7};
    std::vector<int> rows_b = {0, 2, 0, 1, 2};
    std::vector<int> pointer_b = {0, 2, 3, 5};

    std::vector<double> values_c = {19.85, 44.5, 10.64, 2.4, 8.96, 44.18, 68.53};
    std::vector<int> rows_c = {0, 1, 2, 0, 2, 0, 1};
    std::vector<int> pointer_c = {0, 3, 5, 7};

    SparseMatrix a(3, 3, values_a, rows_a, pointer_a);
    SparseMatrix b(3, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test2) {
    std::vector<double> values_a = {4.4, 3.2, 1.1, 6.1, 4.9};
    std::vector<int> rows_a = {0, 1, 2, 0, 1};
    std::vector<int> pointer_a = {0, 3, 3, 5};

    std::vector<double> values_b = {2, 5.6, 4.2, 9.7};
    std::vector<int> rows_b = {0, 1, 0, 2};
    std::vector<int> pointer_b = {0, 1, 2, 4};

    std::vector<double> values_c = {8.8, 6.4, 2.2, 77.65, 60.97, 4.62};
    std::vector<int> rows_c = {0, 1, 2, 0, 1, 2};
    std::vector<int> pointer_c = {0, 3, 3, 6};

    SparseMatrix a(3, 3, values_a, rows_a, pointer_a);
    SparseMatrix b(3, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test3) {
    std::vector<double> values_a = {10.5, 1.9, 9.3, 2.2};
    std::vector<int> rows_a = {0, 2, 1, 1};
    std::vector<int> pointer_a = {0, 2, 3, 4};

    std::vector<double> values_b = {2, 7, 4.9, 3.3, 8.5};
    std::vector<int> rows_b = {0, 2, 1, 1, 2};
    std::vector<int> pointer_b = {0, 2, 3, 5};

    std::vector<double> values_c = {21, 15.4, 3.8, 45.57, 49.39};
    std::vector<int> rows_c = {0, 1, 2, 1, 1};
    std::vector<int> pointer_c = {0, 3, 4, 5};

    SparseMatrix a(3, 3, values_a, rows_a, pointer_a);
    SparseMatrix b(3, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test4) {
    std::vector<double> values_a = {4.76, 2.23, 5.71};
    std::vector<int> rows_a = {2, 0, 1};
    std::vector<int> pointer_a = {0, 1, 2, 3};

    std::vector<double> values_b = {11.2, 15.3, 7.77};
    std::vector<int> rows_b = {2, 1, 2};
    std::vector<int> pointer_b = {0, 1, 2, 3};

    std::vector<double> values_c = {63.952, 34.119, 44.3667};
    std::vector<int> rows_c = {1, 0, 1};
    std::vector<int> pointer_c = {0, 1, 2, 3};

    SparseMatrix a(3, 3, values_a, rows_a, pointer_a);
    SparseMatrix b(3, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test5) {
    std::vector<double> values_a = {1};
    std::vector<int> rows_a = {0};
    std::vector<int> pointer_a = {0, 0, 1, 1};

    std::vector<double> values_b = {10.11};
    std::vector<int> rows_b = {2};
    std::vector<int> pointer_b = {0, 1, 1, 1};

    SparseMatrix a(3, 3, values_a, rows_a, pointer_a);
    SparseMatrix b(3, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test6) {
    std::vector<double> values_a = {2, 1, 3};
    std::vector<int> rows_a = {1, 0, 2};
    std::vector<int> pointer_a = {0, 1, 3};

    std::vector<double> values_b = {1, 2, 3};
    std::vector<int> rows_b = {0, 1, 1};
    std::vector<int> pointer_b = {0, 1, 2, 3};

    std::vector<double> values_c = {2, 2, 6, 3, 9};
    std::vector<int> rows_c = {1, 0, 2, 0, 2};
    std::vector<int> pointer_c = {0, 1, 3, 5};

    SparseMatrix a(3, 2, values_a, rows_a, pointer_a);
    SparseMatrix b(2, 3, values_b, rows_b, pointer_b);
    SparseMatrix c(3, 3, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

TEST(OMP_task, test7) {
    std::vector<double> values_a = {9.7, 2.1, 1.3};
    std::vector<int> rows_a = {3, 0, 1};
    std::vector<int> pointer_a = {0, 1, 3};

    std::vector<double> values_b = {7, 2.4, 4.2, 8.8};
    std::vector<int> rows_b = {0, 1, 0, 1};
    std::vector<int> pointer_b = {0, 1, 2, 3, 4};

    std::vector<double> values_c = {67.9, 5.04, 3.12, 40.74, 18.48, 11.44};
    std::vector<int> rows_c = {3, 0, 1, 3, 0, 1};
    std::vector<int> pointer_c = {0, 1, 3, 4, 6};

    SparseMatrix a(4, 2, values_a, rows_a, pointer_a);
    SparseMatrix b(2, 4, values_b, rows_b, pointer_b);
    SparseMatrix c(4, 4, values_c, rows_c, pointer_c);
    SparseMatrix result(3, 3);

    // printf("C:\n");
    // c.print();
    result = a.transpose().multiply(b);
    // printf("result:\n");
    // result.print();

    EXPECT_EQ(true, c == result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
