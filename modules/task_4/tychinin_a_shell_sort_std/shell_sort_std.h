// Copyright 2023 Tychinin Alexey
#ifndef MODULES_TASK_4_TYCHININ_A_SHELL_SORT_STD_SHELL_SORT_STD_H_
#define MODULES_TASK_4_TYCHININ_A_SHELL_SORT_STD_SHELL_SORT_STD_H_

#include <cstddef>
#include <vector>

namespace task4 {
    std::vector<double> shell_sort(const std::vector<double>& vec);

    std::vector<std::vector<double>> make_partitions(const std::vector<double>& vec, size_t partitions_n);

    std::vector<double> parallel_shell_sort(const std::vector<double>& vec);

    std::vector<double> merge_sorted_partitions(const std::vector<double>& part1,
                                                const std::vector<double>& part2);

}  // namespace task4

#endif  // MODULES_TASK_4_TYCHININ_A_SHELL_SORT_STD_SHELL_SORT_STD_H_
