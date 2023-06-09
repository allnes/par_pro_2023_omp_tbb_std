// Copyright 2023 Yarakhtin Anton
#ifndef MODULES_TASK_3_YARAKHTIN_A_SIMPSON_METHOD_TBB_SIMPSON_METHOD_TBB_H_
#define MODULES_TASK_3_YARAKHTIN_A_SIMPSON_METHOD_TBB_SIMPSON_METHOD_TBB_H_

#include<functional>
#include<tuple>
#include<vector>
#include<utility>

double simpson_method(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func);

double simpson_method_tbb(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func);

#endif  // MODULES_TASK_3_YARAKHTIN_A_SIMPSON_METHOD_TBB_SIMPSON_METHOD_TBB_H_
