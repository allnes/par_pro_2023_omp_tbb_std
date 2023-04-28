// Copyright 2023 Goncharova Anna

#ifndef MODULES_TASK_2_GONCHAROVA_A_SOBEL_OMP_GONCHAROVA_A_SOBEL_OMP_H_
#define MODULES_TASK_2_GONCHAROVA_A_SOBEL_OMP_GONCHAROVA_A_SOBEL_OMP_H_

#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>

class image {
public:
	int width = 0, height = 0;
	std::vector<int> matrix;
	image(int _width, int _height);
};

image getRandomMatrix(int _width, int _height);
image SequenceMainFunction(image Start);
image OmpMainFunction(image Start);

#endif  // MODULES_TASK_2_GONCHAROVA_A_SOBEL_OMP_GONCHAROVA_A_SOBEL_OMP_H_
