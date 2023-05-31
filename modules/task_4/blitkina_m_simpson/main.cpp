// Copyright 2023 Blitkina Maria
#include <gtest/gtest.h>
#include <omp.h>
#include <cmath>
#include <vector>
#include <functional>
#include <utility>
#include <chrono>
#include "./simpson.h"

TEST(Simson_Method_STD, Can_Integrate_One_Dim_Func) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0]; };  // y(x) = x
    std::vector<std::pair<double, double>> scope = { {0, 1} };  // expected 0.5
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.5, 1);
}

TEST(Simson_Method_STD, Can_Integrate_One_Dim_Func_2) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] * vec[0] * vec[0]; };  // y(x) = x * x * x
    std::vector<std::pair<double, double>> scope = { {0, 1} };  // expected 0.25
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.25, 1);
}

TEST(Simson_Method_STD, Can_Integrate_Two_Dim_Func) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + 2 * sin(vec[1]); };  // y(x) = x + 2 * sin(y)
    std::vector<std::pair<double, double>> scope = { {0, 0.2}, {0, 3.14159} };  // expected 0.862832
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.862832, 0.1);
}

TEST(Simson_Method_STD, Can_Integrate_Two_Dim_Func_2) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + vec[1] * vec[1]; };  // y(x) = x + y*y
    std::vector<std::pair<double, double>> scope = { {0, 1}, {0, 2} };  // expected 3.6
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 3.6, 1);
}

TEST(Simson_Method_STD, Can_Integrate_Two_Dim_Func_3) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + vec[1]; };  // y(x) = x + y
    std::vector<std::pair<double, double>> scope = { {0, 0.5}, {0, 0.5} };  // expected 0.125
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.125, 0.01);
}

// TEST(Simson_Method_STD, Can_Integrate_Three_Dim_Func) {
//     std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
//         return sin(vec[0]) * vec[1] * cos(vec[2]);};  // f(x,y,z) = sin(x) * y * cos(z)
//     std::vector<std::pair<double, double>> scope = { {0, 1}, {0, 0.5}, {0, 1} };  // expected 0
//     auto time1 = std::chrono::high_resolution_clock::now(); 
//     double res = calcIntegral(scope, f);
//     auto time2 = std::chrono::high_resolution_clock::now(); 
//     std:: cout << "\nTime : " << std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1).count() << std::endl;
//     EXPECT_NEAR(res, 0.0483528, 0.01);
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
