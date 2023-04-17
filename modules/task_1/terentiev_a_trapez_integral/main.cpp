// Copyright 2023 Terentiev Alexander
#include <gtest/gtest.h>
#include "../../../modules/task_1/terentiev_a_trapez_integral/trapez_integral.h"


TEST(Trapez_Integral_Seq, Test1) {
    ASSERT_TRUE(Testing(0, 0, 0, 3, 2, 1, Func1, 4.5));
}

TEST(Trapez_Integral_Seq, Test2) {
    ASSERT_TRUE(Testing(1, 1, 1, 2, 2, 2, Func1, 3.375));
}

TEST(Trapez_Integral_Seq, Test3) {
    ASSERT_TRUE(Testing(5, 0, 1, 7, 3, 2, Func1, 81));
}

TEST(Trapez_Integral_Seq, Test4) {
    ASSERT_TRUE(Testing(1, 1, 1, 2, 2, 2, Func2, 0.33302));
}

TEST(Trapez_Integral_Seq, Test5) {
    ASSERT_TRUE(Testing(1, 2, 3, 7, 6, 5, Func2, 1.092));
}
