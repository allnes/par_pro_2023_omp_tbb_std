// Copyright 2023 Popov Nikita
#include "../../../modules/task_1/popov_n_alg_of_jarvis/alg_of_jarvis.h"

int check_orientation(Point i, Point j, Point k) {
  int value = (j.y - i.y) * (k.x - j.x) - (j.x - i.x) * (k.y - j.y);
  if (value == 0) return 0;
  return (value > 0) ? 1 : 2;
}

std::vector<Point> get_convex_body(const std::vector<Point>& p_arr) {
  int size = p_arr.size();
  if (size < 3) return std::vector<Point>();
  std::vector<Point> convex_body;
  int a = 0;
  for (int i = 1; i < size; i++) {
    if (p_arr[i].x < p_arr[a].x) {
      a = i;
    }
  }
  int change = a;
  int b;

  do {
    convex_body.push_back(p_arr[change]);
    b = (change + 1) % size;
    for (int i = 0; i < size; i++) {
      if (check_orientation(p_arr[change], p_arr[i], p_arr[b]) == 2) {
        b = i;
      }
    }
    change = b;
  }

  while (a != change); {}
  return convex_body;
}
