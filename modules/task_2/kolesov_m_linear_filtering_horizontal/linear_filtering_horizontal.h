// Copyright 2023 Maxim Kolesov
#pragma once

#include <omp.h>
#include <vector>
#include <cstdint>

constexpr uint32_t kernelSize = 3;

std::vector<float> getKernel(uint32_t n);
/**
 * @param hex Format: 0xAABBCC where AA - red, BB - green, CC - blue
 */
void hexToColors(uint32_t hex, uint8_t *red, uint8_t *green, uint8_t *blue);

/**
 * @return Format: 0xAABBCC where AA - red, BB - green, CC - blue
 */
uint32_t colorsToHex(uint8_t red, uint8_t green, uint8_t blue);

template<typename T>
T clamp(T value, T min, T max);

/**
 * @param image similar to image in processLine method
 * @param width similar to width in processLine method
 * @param height similar to height in processLine method
 * @param x in range [0, width - 1]
 * @param y in range [0, height - 1]
 */
uint32_t getColor(const std::vector<uint32_t> &image, uint32_t width, uint32_t height, uint32_t x, uint32_t y);

/**
 * @param image Array of hex (0xAABBCC where AA - red, BB - green, CC - blue) values
 * @param width starts at 1
 * @param height starts at 1
 * @param lineNumber Number of line in range [0, height - 1]
 */
std::vector<uint32_t> processLine(
    const std::vector<uint32_t> &image,
    uint32_t width,
    uint32_t height,
    uint32_t lineNumber
);
std::vector<uint32_t> process(const std::vector<uint32_t> &image, uint32_t width, uint32_t height);

std::vector<uint32_t> processParallel(const std::vector<uint32_t> &image, uint32_t width, uint32_t height);
