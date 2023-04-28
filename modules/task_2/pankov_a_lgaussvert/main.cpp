// Copyright 2023 Pankov Anatoliy
#include "../../../modules/task_2/pankov_a_lgaussvert/lgaussvert.h"

TEST(LGaussVerticalOMP, MatrixMN0Test) {
    int m = 0;
    int n = 0;
    std::vector<double> Matrix(m * n);

    ASSERT_ANY_THROW(Matrix = OMPGaussFilter(Matrix, m, n));
}

TEST(LGaussVerticalOMP, ZeroMatrixTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> Matrix(0);

    ASSERT_ANY_THROW(Matrix = OMPGaussFilter(Matrix, m, n));
}

TEST(LGaussVerticalOMP, RandomTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> Matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(Matrix, n, m);
    std::vector<double> OmpResult = OMPGaussFilter(Matrix, n, m);

    ASSERT_EQ(SeqResult, OmpResult);
}

TEST(LGaussVerticalOMP, RandomTest10x10) {
    int m = 10;
    int n = 10;
    std::vector<double> Matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(Matrix, n, m);
    std::vector<double> OmpResult = OMPGaussFilter(Matrix, n, m);

    ASSERT_EQ(SeqResult, OmpResult);
}

TEST(LGaussVerticalOMP, RandomTest50x50) {
    int m = 50;
    int n = 50;
    std::vector<double> Matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(Matrix, n, m);
    std::vector<double> OmpResult = OMPGaussFilter(Matrix, n, m);

    ASSERT_EQ(SeqResult, OmpResult);
}

/* TEST(LGaussVerticalOMP, Test_Random_Matrix_Size_5000x5000) {
    int m = 1000;
    int n = 1000;
    std::vector<double> Matrix = MakeRandomMatrix(m, n);

    double TStart = omp_get_wtime();
    std::vector <double> SeqResult = SeqGaussFilter(Matrix, n, m);
    double TEnd = omp_get_wtime();
    double TSeq = TEnd - TStart;

    TStart = omp_get_wtime();
    std::vector <double> OmpResult = OMPGaussFilter(Matrix, n, m);
    TEnd = omp_get_wtime();
    double TOmp = TEnd - TStart;

    std::cout << "Sequential time: " << TSeq << std::endl;
    std::cout << "Parallel time: " << TOmp << std::endl;

    ASSERT_EQ(SeqResult, OmpResult);
} */

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
