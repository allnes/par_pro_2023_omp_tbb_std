// Copyright 2023 Korobeynikova Alice
#include "../../../modules/task_2/korobeynikova_a_histogram_linear_stretching/histogram_linear_stretching.h"

#include <omp.h>

#include <iostream>

constexpr int RANGEMIN = 0;
constexpr int RANGEMAX = 255;

static std::pair<Color, Color> parFindRange(const Image& image) {
  int num_threads = 0;
#pragma omp parallel
  { num_threads = omp_get_num_threads(); }
  std::vector<std::pair<Color, Color>> ranges(num_threads,
                                              {RANGEMAX, RANGEMIN});
#pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
#pragma omp for
    for (int i = 0; i < image.size(); ++i) {
      ranges[thread_id].first = std::min(image[i], ranges[thread_id].first);
      ranges[thread_id].second = std::max(image[i], ranges[thread_id].second);
    }
  }
  std::pair<Color, Color> range({RANGEMAX, RANGEMIN});
  for (auto elem : ranges) {
    range.first = std::min(elem.first, range.first);
    range.second = std::max(elem.second, range.second);
  }
  return range;
}

static std::pair<Color, Color> seqFindRange(const Image& image) {
  std::pair<Color, Color> range({RANGEMAX, RANGEMIN});
  for (int i = 0; i < image.size(); ++i) {
    range.first = std::min(image[i], range.first);
    range.second = std::max(image[i], range.second);
  }
  return range;
}

void sequentialLinearHistogramStretching(Image* image_ptr) {
  Image& image = *image_ptr;
  std::pair<Color, Color> range = seqFindRange(image);
  if (range.second != range.first) {
    for (auto& pixel : image) {
      pixel = (pixel - range.first) * (RANGEMAX - RANGEMIN) /
              (range.second - range.first);
    }
  }
}

void parallelLinearHistogramStretching(Image* image_ptr) {
  Image& image = *image_ptr;
  std::pair<Color, Color> range = parFindRange(image);
  if (range.second != range.first) {
#pragma omp parallel for
    for (int i = 0; i < image.size(); ++i) {
      image[i] = (image[i] - range.first) * (RANGEMAX - RANGEMIN) /
                 (range.second - range.first);
    }
  }
}
