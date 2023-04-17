// Copyright 2023 Korobeynikova Alice
#include "../../../modules/task_1/korobeynikova_a_histogram_linear_stretching/histogram_linear_stretching.h"

#include <iostream>
#include <random>

constexpr int RANGEMIN = 0;
constexpr int RANGEMAX = 255;

static std::pair<Color, Color> findRange(const Image& image) {
  std::pair<Color, Color> range = {RANGEMAX, RANGEMIN};
  for (auto pixel : image) {
    if (pixel < range.first) {
      range.first = pixel;
    }
    if (pixel > range.second) {
      range.second = pixel;
    }
  }
  return range;
}

void linearHistogramStretching(Image* image) {
  std::pair<Color, Color> range = findRange(*image);
  if (range.second != range.first) {
    for (auto& pixel : *image) {
      pixel = (pixel - range.first) * (RANGEMAX - RANGEMIN) /
              (range.second - range.first);
    }
  }
}
