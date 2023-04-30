// Copyright 2023 Pronina Tatiana
#include "../../../modules/task_2/pronina_t_gaussian_vert/gaussian_vert.h"

bool operator==(const rgb_coub& a, const rgb_coub& b) {
  return (a.red == b.red) && (a.green == b.green) && (a.blue == b.blue);
}

bool operator!=(const rgb_coub& a, const rgb_coub& b) {
  return (a.red != b.red) && (a.green != b.green) && (a.blue != b.blue);
}

std::vector<rgb_coub> getRandomImage(int rows, int columns) {
  if (columns <= 0 || rows <= 0) {
    throw "-1";
  }
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<rgb_coub> data(rows * columns);
  for (int i = 0; i < rows * columns; i++) {
    data[i].red = static_cast<unsigned char> (gen() % 256);
    data[i].green = static_cast<unsigned char> (gen() % 256);
    data[i].blue = static_cast<unsigned char> (gen() % 256);
  }
  return data;
}
std::vector<rgb_coub> Gaussian_Filter_Seq(const std::vector<rgb_coub>& img,
                                          int rows, int columns,
                                          const double sigma) {
  if (columns <= 0 || rows <= 0 || img.size() == 0 || sigma == 0.0) {
    throw "-1";
  }
  double norm = 0.0;
  double r, g, b;
  double Gaussian_Kernel[3][3];
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      Gaussian_Kernel[x + 1][y + 1] =
          std::exp(-(x * x + y * y) / (2 * pow(sigma, 2)));
      norm += Gaussian_Kernel[x + 1][y + 1];
    }
  }
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      Gaussian_Kernel[x + 1][y + 1] /= norm;
    }
  }
  std::vector<rgb_coub> result(rows * columns);
  int x, y;
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      r = g = b = 0.0;
      for (int k = -1; k < 2; k++) {
        for (int n = -1; n < 2; n++) {
          x = n + j;
          y = k + i;

          if (x > rows - 1 || x < 0) {
            x = j;
          }
          if (y > columns - 1 || y < 0) {
            y = i;
          }
          r += static_cast<double>(img[x * columns + y].red) *
               Gaussian_Kernel[k + 1][n + 1];
          g += static_cast<double>(img[x * columns + y].green) *
               Gaussian_Kernel[k + 1][n + 1];
          b += static_cast<double>(img[x * columns + y].blue) *
               Gaussian_Kernel[k + 1][n + 1];
        }
      }
      result[j * columns + i].red = static_cast<unsigned char>(r);
      result[j * columns + i].green = static_cast<unsigned char>(g);
      result[j * columns + i].blue = static_cast<unsigned char>(b);
    }
  }
  return result;
}

std::vector<rgb_coub> Gaussian_Filter_Omp(const std::vector<rgb_coub>& img,
                                          int rows, int columns,
                                          const double sigma) {
  if (columns <= 0 || rows <= 0 || img.size() == 0 || sigma == 0.0) {
    throw "-1";
  }
  double norm = 0.0;
  double r, g, b;
  double Gaussian_Kernel[3][3];
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      Gaussian_Kernel[x + 1][y + 1] =
          std::exp(-(x * x + y * y) / (2 * pow(sigma, 2)));
      norm += Gaussian_Kernel[x + 1][y + 1];
    }
  }
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      Gaussian_Kernel[x + 1][y + 1] /= norm;
    }
  }
  std::vector<rgb_coub> result(rows * columns);
  int x, y;
#pragma omp parallel for private(r, g, b, x, y)
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      r = g = b = 0.0;
      for (int k = -1; k < 2; k++) {
        for (int n = -1; n < 2; n++) {
          x = n + j;
          y = k + i;

          if (x > rows - 1 || x < 0) {
            x = j;
          }
          if (y > columns - 1 || y < 0) {
            y = i;
          }
          r += static_cast<double> (img[x * columns + y].red) *
               Gaussian_Kernel[k + 1][n + 1];
          g += static_cast<double> (img[x * columns + y].green) *
               Gaussian_Kernel[k + 1][n + 1];
          b += static_cast<double> (img[x * columns + y].blue) *
               Gaussian_Kernel[k + 1][n + 1];
        }
      }
      result[j * columns + i].red = static_cast<unsigned char>(r);
      result[j * columns + i].green = static_cast<unsigned char>(g);
      result[j * columns + i].blue = static_cast<unsigned char>(b);
    }
  }
  return result;
}
