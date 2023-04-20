// Copyright 2023 Antonova Anastasya
#include <gtest/gtest.h>
#include <tbb/tick_count.h>

#include <cmath>
#include <vector>

#include "../../../modules/task_3/antonova_a_monte_carlo_tbb/monte_carlo_tbb.h"

double Integral_1(const std::vector<double>& x) { return x[0] * x[0]; }

double Integral_2(const std::vector<double>& x) {
  return 3 * x[0] * x[0] * x[0] + 2 * x[1] * x[1];
}

double Integral_3(const std::vector<double>& x) {
  return sin(x[0]) + 2 * x[1] + x[2] * x[2];
}

double Integral_4(const std::vector<double>& x) {
  return x[0] * x[0] + 2 * x[1] - cos(x[2]) + 2 * x[3] * x[3] * x[3] - 3 * x[4];
}

TEST(Monte_carlo_integral_test, test_result_of_integral) {
  double a = 0.0, b = 1.0;
  tbb::tick_count t1, t2;
  int num_th = 4;
  const int N = 250000;
  t1 = tbb::tick_count::now();
  double res_seq = seqMonteCarlo(Integral_1, {a}, {b}, N * num_th);
  t2 = tbb::tick_count::now();
  std::cout << " Seq_Time = " << (t2 - t1).seconds() << std::endl;
  t1 = tbb::tick_count::now();
  double res_tbb = tbbMonteCarlo(Integral_1, {a}, {b}, N);
  t2 = tbb::tick_count::now();
  std::cout << " Paral_Time = " << (t2 - t1).seconds() << std::endl;

  ASSERT_NEAR(res_seq, res_tbb, 0.5);
}

TEST(Monte_carlo_integral_test, test_result_of_integral_1) {
  std::vector<double> a = {0.0, 2.5};
  std::vector<double> b = {1.534, 3.12};
  tbb::tick_count t1, t2;
  int num_th = 4;
  const int N = 250000;

  t1 = tbb::tick_count::now();
  double res_seq = seqMonteCarlo(Integral_2, a, b, N * num_th);
  t2 = tbb::tick_count::now();
  std::cout << " Seq_Time = " << (t2 - t1).seconds() << std::endl;
  t1 = tbb::tick_count::now();
  double res_tbb = tbbMonteCarlo(Integral_2, a, b, N);
  t2 = tbb::tick_count::now();
  std::cout << " Paral_Time = " << (t2 - t1).seconds() << std::endl;

  ASSERT_NEAR(res_seq, res_tbb, 0.5);
}

TEST(Monte_carlo_integral_test, test_result_of_integral_2) {
  std::vector<double> a = {0.0, 2.5, 1.234};
  std::vector<double> b = {1.534, 3.12, 1.555};
  tbb::tick_count t1, t2;
  int num_th = 4;
  const int N = 250000;

  t1 = tbb::tick_count::now();
  double res_seq = seqMonteCarlo(Integral_3, a, b, N * num_th);
  t2 = tbb::tick_count::now();
  std::cout << " Seq_Time = " << (t2 - t1).seconds() << std::endl;
  t1 = tbb::tick_count::now();
  double res_tbb = tbbMonteCarlo(Integral_3, a, b, N);
  t2 = tbb::tick_count::now();
  std::cout << " Paral_Time = " << (t2 - t1).seconds() << std::endl;

  ASSERT_NEAR(res_seq, res_tbb, 0.5);
}

TEST(Monte_carlo_integral_test, test_result_of_integral_3) {
  std::vector<double> a = {0.3, 1.32, 1.234};
  std::vector<double> b = {3.534, 3.5, 1.435};
  tbb::tick_count t1, t2;
  int num_th = 4;
  const int N = 250000;

  t1 = tbb::tick_count::now();
  double res_seq = seqMonteCarlo(Integral_3, a, b, N * num_th);
  t2 = tbb::tick_count::now();
  std::cout << " Seq_Time = " << (t2 - t1).seconds() << std::endl;
  t1 = tbb::tick_count::now();
  double res_tbb = tbbMonteCarlo(Integral_3, a, b, N);
  t2 = tbb::tick_count::now();
  std::cout << " Paral_Time = " << (t2 - t1).seconds() << std::endl;

  ASSERT_NEAR(res_seq, res_tbb, 0.5);
}

TEST(Monte_carlo_integral_test, test_n_is_negative) {
  double a = 0.0, b = 3.0;
  ASSERT_ANY_THROW(tbbMonteCarlo(Integral_1, {a}, {b}, -1000));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
