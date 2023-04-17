// Copyright 2023 Dryamina Ksenia
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "./shell_sort.h"

TEST(Shell_Sort, Int_64) {
    int size = 64;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::sort(vec.begin(), vec.end());

    ASSERT_EQ(sequential, vec);
}

TEST(Shell_Sort, Int_128) {
    int size = 128;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::sort(vec.begin(), vec.end());

    ASSERT_EQ(sequential, vec);
}

TEST(Shell_Sort, Int_256) {
    int size = 256;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::sort(vec.begin(), vec.end());

    ASSERT_EQ(sequential, vec);
}

TEST(Shell_Sort, Int_512) {
    int size = 512;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::sort(vec.begin(), vec.end());

    ASSERT_EQ(sequential, vec);
}

TEST(Shell_Sort, Int_1024) {
    int size = 1024;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::sort(vec.begin(), vec.end());

    ASSERT_EQ(sequential, vec);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
