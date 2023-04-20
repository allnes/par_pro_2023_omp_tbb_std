// Copyright 2023 Artemev Alexej
#include <gtest/gtest.h>
#include "./artemev_alexej_conj_grad.h"

TEST(PAR_CONJ_GRAD, TEST_2x2) {
    int n = 2;
    std::vector<std::vector<double>> A = { { 1, 3}, {3, 8} };
    std::vector<double> betta = { 4, 5 };
    std::vector<double> result = { -17, 7 };
    std::vector<double> decision = par_conj_grad_method(A, betta, n);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_3x3) {
    int n = 3;
    std::vector<std::vector<double>> A = { { 3, 4, 0}, {4, -3, 0}, {0, 0, 5} };
    std::vector<double> betta = { 1, 5, 9 };
    std::vector<double> result = { 0.92, -0.44, 1.8 };
    std::vector<double> decision = par_conj_grad_method(A, betta, n);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST2_3x3) {
    int n = 3;
    std::vector<std::vector<double>> A = { { 3.2, -1.7, 2.5}, {1.5, 6.2, -2.9}, {2.8, -1.7, 3.8} };
    std::vector<double> betta = { 3.7, 3.2, 2.8 };
    std::vector<double> result = { 2.094, -0.465, -1.015 };
    std::vector<double> decision = par_conj_grad_method(A, betta, n);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_5x5) {
    int n = 5;
    std::vector<std::vector<double>> A = { {5, 4, 0, 3, 6},
                                           {4, 6, 1, 5, 7},
                                           {0, 1, 0, 1, 1},
                                           {3, 5, 1, 5, 6},
                                           {6, 7, 1, 6, 10}, };
    std::vector<double> betta = { 2, 5, 0, 9, 1 };

    std::vector<double> x = par_conj_grad_method(A, betta, n);
    std::vector<double> result = { 5, -2, 1, 9, -7 };
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(x[i], result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_100x100) {
    int n = 4;
    std::vector<std::vector<double>> A = random_matrix(100);
    std::vector<double> vec = random_vec(100);
    clock_t start2 = clock();
    std::vector<double> par_result = par_conj_grad_method(A, vec, n);
    clock_t end2 = clock();
    clock_t start1 = clock();
    std::vector<double> seq_result = conj_grad_method(A, vec);
    clock_t end1 = clock();
    double par_time = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << "par_time:" << par_time << std::endl;
    double seq_time = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    std::cout << "seq_time:" << seq_time << std::endl;
    for (int i = 0; i < 100; i++) {
        ASSERT_NEAR(seq_result[i], par_result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_200x200) {
    int n = 4;
    std::vector<std::vector<double>> A = random_matrix(200);
    std::vector<double> vec = random_vec(200);
    clock_t start2 = clock();
    std::vector<double> par_result = par_conj_grad_method(A, vec, n);
    clock_t end2 = clock();
    clock_t start1 = clock();
    std::vector<double> seq_result = conj_grad_method(A, vec);
    clock_t end1 = clock();
    double par_time = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << "par_time:" << par_time << std::endl;
    double seq_time = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    std::cout << "seq_time:" << seq_time << std::endl;
    for (int i = 0; i < 200; i++) {
        ASSERT_NEAR(seq_result[i], par_result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_250x250) {
    int n = 4;
    std::vector<std::vector<double>> A = random_matrix(250);
    std::vector<double> vec = random_vec(250);
    clock_t start2 = clock();
    std::vector<double> par_result = par_conj_grad_method(A, vec, n);
    clock_t end2 = clock();
    clock_t start1 = clock();
    std::vector<double> seq_result = conj_grad_method(A, vec);
    clock_t end1 = clock();
    double par_time = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << "par_time:" << par_time << std::endl;
    double seq_time = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    std::cout << "seq_time:" << seq_time << std::endl;
    for (int i = 0; i < 250; i++) {
        ASSERT_NEAR(seq_result[i], par_result[i], 0.5);
    }
}

TEST(PAR_CONJ_GRAD, TEST_300x300) {
    int n = 4;
    std::vector<std::vector<double>> A = random_matrix(300);
    std::vector<double> vec = random_vec(300);
    clock_t start2 = clock();
    std::vector<double> par_result = par_conj_grad_method(A, vec, n);
    clock_t end2 = clock();
    clock_t start1 = clock();
    std::vector<double> seq_result = conj_grad_method(A, vec);
    clock_t end1 = clock();
    double par_time = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << "par_time:" << par_time << std::endl;
    double seq_time = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    std::cout << "seq_time:" << seq_time << std::endl;
    for (int i = 0; i < 300; i++) {
        ASSERT_NEAR(seq_result[i], par_result[i], 0.5);
    }
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
