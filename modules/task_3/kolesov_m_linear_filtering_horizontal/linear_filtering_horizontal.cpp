// Copyright 2023 Maxim Kolesov
#include <algorithm>
#include <cstring>
#include "../../../modules/task_3/kolesov_m_linear_filtering_horizontal/linear_filtering_horizontal.h"

std::vector<float> getKernel(uint32_t n) {
  std::vector<float> kernel(n*n, 1.0f / n);

  return kernel;
}

void hexToColors(uint32_t hex, uint8_t *red, uint8_t *green, uint8_t *blue) {
  *blue   = hex & 0xFF;
  *green  = (hex & 0xFF00) >> 8;
  *red    = (hex & 0xFF0000) >> 16;
}

uint32_t colorsToHex(uint8_t red, uint8_t green, uint8_t blue) {
  return (red << 16) | (green << 8) | blue;
}

template<typename T>
T clamp(T value, T min, T max) {
  return std::min(std::max(value, min), max);
}

uint32_t getColor(const std::vector<uint32_t> &image, uint32_t width, uint32_t height, uint32_t x, uint32_t y) {
  return image.at(y*width + x);
}

std::vector<uint32_t> processLine(
    const std::vector<uint32_t> &image,
    uint32_t width,
    uint32_t height,
    uint32_t lineNumber) {
  std::vector<uint32_t> line =
      std::vector<uint32_t>(image.begin() + width*lineNumber, image.begin() + width*lineNumber + width);
  std::vector<float> kernel = getKernel(kernelSize);

  for (uint32_t i = 0; i < line.size(); i++) {
    float redSum = 0, greenSum = 0, blueSum = 0;

    for (int32_t l = -(static_cast<int32_t>(kernelSize) / 2); l <= static_cast<int32_t>(kernelSize) / 2; l++) {
      for (int32_t k = -(static_cast<int32_t>(kernelSize) / 2); k <= static_cast<int32_t>(kernelSize) / 2; k++) {
        uint32_t x = clamp<uint32_t>(static_cast<int32_t>(i) + k, 0, width - 1);
        uint32_t y = clamp<uint32_t>(static_cast<int32_t>(lineNumber) + l, 0, height - 1);

        uint32_t color = getColor(image, width, height, x, y);
        uint8_t red = 0, green = 0, blue = 0;
        hexToColors(color, &red, &green, &blue);

        uint32_t kernelX = k + (kernelSize / 2);
        uint32_t kernelY = l + (kernelSize / 2);

        redSum += static_cast<float>(red) * kernel.at(kernelY*kernelSize + kernelX);
        greenSum += static_cast<float>(green) * kernel.at(kernelY*kernelSize + kernelX);
        blueSum += static_cast<float>(blue) * kernel.at(kernelY*kernelSize + kernelX);
      }
    }

    uint8_t red = static_cast<uint8_t>(clamp<uint32_t>(static_cast<uint32_t>(redSum), 0, 255));
    uint8_t green = static_cast<uint8_t>(clamp<uint32_t>(static_cast<uint32_t>(greenSum), 0, 255));
    uint8_t blue = static_cast<uint8_t>(clamp<uint32_t>(static_cast<uint32_t>(blueSum), 0, 255));

    line.at(i) = colorsToHex(red, green, blue);
  }

  return line;
}

std::vector<uint32_t> process(const std::vector<uint32_t> &image, uint32_t width, uint32_t height) {
  std::vector<uint32_t> result(image.size());

  for (uint32_t i = 0; i < height; i++) {
    std::vector<uint32_t> line = processLine(image, width, height, i);
    std::memcpy(result.data() + width*i, line.data(), line.size() * sizeof(uint32_t));
  }

  return result;
}

std::vector<uint32_t> processParallel(const std::vector<uint32_t> &image, uint32_t width, uint32_t height) {
  std::vector<uint32_t> result(image.size());

  tbb::parallel_for(tbb::blocked_range<uint32_t>(0, height, 1),
      [&](const tbb::blocked_range<uint32_t> &r) -> void {
      for (uint32_t i = r.begin(); i != r.end(); i++) {
        std::vector<uint32_t> line = processLine(image, width, height, i);
        std::memcpy(result.data() + width * i, line.data(), line.size() * sizeof(uint32_t));
      }
  });

  return result;
}
