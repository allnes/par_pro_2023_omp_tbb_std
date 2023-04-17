// Copyright 2023 Okulov Stepan
#include "../../../modules/task_1/okulov_s_marking_comp/marking_comp.h"

#include <ctime>
#include <random>
#include <set>
#include <vector>

void create_random_image(std::vector<std::vector<int>> *image) {
  std::mt19937 gen(time(0));

  for (int i = 0; i < (*image).size(); i++) {
    for (int j = 0; j < image[0].size(); j++) {
      (*image)[i][j] = gen() % 2;
    }
  }
}
void marking(std::vector<std::vector<int>> *img,
             std::vector<std::vector<int>> *marked) {
  int label = 0;
  std::set<std::pair<int, int>> eq;
  int C;  // up
  int B;  // left
  for (int i = 0; i < (*img).size(); i++) {
    for (int j = 0; j < (*img)[0].size(); j++) {
      if (j == 0)
        B = 0;
      else
        B = (*marked)[i][j - 1];
      if (i == 0)
        C = 0;
      else
        C = (*marked)[i - 1][j];
      if ((*img)[i][j] == 0) {
        continue;
      } else if (B == 0 && C != 0) {
        (*marked)[i][j] = C;
      } else if (B != 0 && C == 0) {
        (*marked)[i][j] = B;

      } else if (B == 0 && C == 0) {
        label++;
        (*marked)[i][j] = label;
      } else if (B != 0 && C != 0) {
        if (B == C) {
          (*marked)[i][j] = C;
        } else {
          if (B < C) {
            (*marked)[i][j] = B;
            eq.insert(std::pair<int, int>(C, B));
          }
          if (B > C) {
            (*marked)[i][j] = C;
            eq.insert(std::pair<int, int>(B, C));
          }
        }
      }
    }
  }
  for (std::pair<int, int> cur_eq : eq) {
    for (int i = 0; i < (*img).size(); i++) {
      for (int j = 0; j < (*img)[0].size(); j++) {
        if ((*marked)[i][j] == cur_eq.first) (*marked)[i][j] = cur_eq.second;
      }
    }
  }
}
