// Copyright 2023 Goncharova Anna
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include "../../../modules/task_1/goncharova_a_sobel/goncharova_a_sobel.h"

image::image(int _width, int _height, std::vector<int>_matrix) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  width = _width;
  height = _height;
  matrix.resize(_width * _height);
  for (int i = 0; i < _width * _height; i++)
    matrix[i] = _matrix[i];
}

image::image(int _width, int _height) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  width = _width;
  height = _height;
  matrix.resize(_width * _height, 0);
}

std::vector<int> image::GetMatrix()const {
  return matrix;
}

void image::GetRandom() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < this->width * this->height; i++)
    this->matrix[i] = gen() % 256;
}

image& image::operator=(const image& Example) {
  if (this != &Example) {
    width = Example.width;
    height = Example.height;
    for (int i = 0; i < height*width; i++)
      matrix[i] = Example.matrix[i];
  }
  return *this;
}


image image::SeqSobel() {
  std::vector<int> Gx, Gy;
  Gx.resize(9);
  Gy.resize(9);
  Gx = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  Gy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
  image result(this->width-2, this->height-2);
  int i = 0;
  while (i <= this->width-3) {
    int j = 0;
    while (j <= this->height-3) {
      int ind = i * (this->height-2) + j;
      int X = 0, Y = 0, Ind_G = 0;
      int a = 0;
      while (a < 3) {
        int b = 0;
        while (b < 3) {
          X = Gx[Ind_G] * matrix[(i + a) * height + j + b] + X;
          Y = Gy[Ind_G] * matrix[(i + a) * height + j + b] + Y;
          Ind_G++;
          b++;
        }
        a++;
      }
      if (sqrt(X * X + Y * Y) > 255)
        result.matrix[ind] = 255;
      else
        result.matrix[ind] = sqrt(X * X + Y * Y);
      j++;
    }
    i++;
  }
  return result;
}

