// Copyright 2023 Busko Polina

#ifndef MODULES_TASK_2_BUSKO_P_OPERATOR_SOBELYA_OPERATOR_SOBELYA_H_
#define MODULES_TASK_2_BUSKO_P_OPERATOR_SOBELYA_OPERATOR_SOBELYA_H_

#include <vector>
#include <random>


const int MIN_VALUE_PIX = 0;
const int MAX_VALUE_PIX = 255;

struct SobelFilter {
    const std::vector<std::vector<int>> xFilter = { {-1, -2, -1},
                                             {0, 0, 0},
                                             {1, 2, 1} };
    const std::vector<std::vector<int>> yFilter = { {-1, 0, 1},
                                             {-2, 0, 2},
                                             {-1, 0, 1} };
};
class Img {
 private:
    int sizeX;
    int sizeY;
    std::vector<std::vector<int>> image;
 public:
    Img(int x, int y);
    Img(int x, int y, int value);
    std::vector<std::vector<int>> SeqSobel();
    std::vector<std::vector<int>> ParallelSobel();
    void print();
};

#endif  // MODULES_TASK_2_BUSKO_P_OPERATOR_SOBELYA_OPERATOR_SOBELYA_H_
