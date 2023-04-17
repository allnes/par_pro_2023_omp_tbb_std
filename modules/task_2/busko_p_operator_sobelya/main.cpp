// Copyright 2023 Busko Polina

#include <omp.h>
#include <gtest/gtest.h>
#include <iostream>
#include "./operator_sobelya.h"
TEST(SobelFilterOpenMP, matrix_100_on_100) {
    int size = 100;
    Img image(size, size, 1);
    double start;
    double end;

    start = omp_get_wtime();
    std::vector<std::vector<int>> seq_answer = image.SeqSobel();
    end = omp_get_wtime();
    std::cout << "Time of the sequential algorithm = " << end - start;
    std::cout << std::endl;

    start = omp_get_wtime();
    std::vector<std::vector<int>> parallel_answer = image.ParallelSobel();
    end = omp_get_wtime();
    std::cout << "Time of the parallel algorithm = " << end - start;
    std::cout << std::endl;

    ASSERT_EQ(seq_answer, parallel_answer);
}
TEST(SobelFilterOpenMP, matrix_1000_on_1000) {
    int size = 1000;
    Img image(size, size, 1);
    double start;
    double end;

    start = omp_get_wtime();
    std::vector<std::vector<int>> seq_answer = image.SeqSobel();
    end = omp_get_wtime();
    std::cout << "Time of the sequential algorithm = " << end - start;
    std::cout << std::endl;

    start = omp_get_wtime();
    std::vector<std::vector<int>> parallel_answer = image.ParallelSobel();
    end = omp_get_wtime();
    std::cout << "Time of the parallel algorithm = " << end - start;
    std::cout << std::endl;

    ASSERT_EQ(seq_answer, parallel_answer);
}
TEST(SobelFilterOpenMP, random_matrix_100_on_100) {
    int size = 100;
    Img image(size, size);
    double start;
    double end;

    start = omp_get_wtime();
    std::vector<std::vector<int>> seq_answer = image.SeqSobel();
    end = omp_get_wtime();
    std::cout << "Time of the sequential algorithm = " << end - start;
    std::cout << std::endl;

    start = omp_get_wtime();
    std::vector<std::vector<int>> parallel_answer = image.ParallelSobel();
    end = omp_get_wtime();
    std::cout << "Time of the parallel algorithm = " << end - start;
    std::cout << std::endl;

    ASSERT_EQ(seq_answer, parallel_answer);
}
TEST(SobelFilterOpenMP, random_matrix_500_on_500) {
    int size = 500;
    Img image(size, size);
    double start;
    double end;

    start = omp_get_wtime();
    std::vector<std::vector<int>> seq_answer = image.SeqSobel();
    end = omp_get_wtime();
    std::cout << "Time of the sequential algorithm = " << end - start;
    std::cout << std::endl;

    start = omp_get_wtime();
    std::vector<std::vector<int>> parallel_answer = image.ParallelSobel();
    end = omp_get_wtime();
    std::cout << "Time of the parallel algorithm = " << end - start;
    std::cout << std::endl;

    ASSERT_EQ(seq_answer, parallel_answer);
}
TEST(SobelFilterOpenMP, random_matrix_1000_on_1000) {
    int size = 1000;
    Img image(size, size);
    double start;
    double end;

    start = omp_get_wtime();
    std::vector<std::vector<int>> seq_answer = image.SeqSobel();
    end = omp_get_wtime();
    std::cout << "Time of the sequential algorithm = " << end - start;
    std::cout << std::endl;

    start = omp_get_wtime();
    std::vector<std::vector<int>> parallel_answer = image.ParallelSobel();
    end = omp_get_wtime();
    std::cout << "Time of the parallel algorithm = " << end - start;
    std::cout << std::endl;

    ASSERT_EQ(seq_answer, parallel_answer);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
