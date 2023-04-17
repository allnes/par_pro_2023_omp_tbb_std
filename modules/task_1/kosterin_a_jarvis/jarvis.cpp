// Copyright 2023 Kosterin Alexey
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include "../../../modules/task_1/kosterin_a_jarvis/jarvis.h"

int Cross(SVector a, SVector b) { return a.x * b.y - b.x * a.y; }

std::vector<SPoint> CreateArray(int size) {
  if (size < 3) {
    throw size;
  }
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<SPoint> arr(size);
  for (int i = 0; i < size; i++) {
    arr[i].x = gen() % 10;
    arr[i].y = gen() % 10;
  }
  return arr;
}

void Swap(SPoint &arr1, SPoint &arr2) {
  SPoint buf;
  buf.x = arr1.x;
  buf.y = arr1.y;

  arr1.x = arr2.x;
  arr1.y = arr2.y;

  arr2.x = buf.x;
  arr2.y = buf.y;
}
bool ChekJarvis(std::vector<SPoint> jarArr) {
  int size = jarArr.size();
  for (int i = 0; i < size; i++) {
    int fPoint = i, sPoint = i + 1, thPoint = i + 2;
    if (sPoint >= size) {
      sPoint = 0;
      thPoint = 1;
    }
    if (thPoint >= size) {
      thPoint = 0;
    }
    if (Cross(SVector(jarArr[fPoint], jarArr[sPoint]),
              SVector(jarArr[sPoint], jarArr[thPoint])) < 0)
      return false;
  }
  return true;
}

std::vector<SPoint> DoJarvis(std::vector<SPoint> arr, int size) {
  for (int i = 1; i < size; i++) {
    if (arr[i].y < arr[0].y)
      Swap(arr[0], arr[i]);
    else if (arr[i].y == arr[0].y && arr[i].x < arr[0].x)
      Swap(arr[0], arr[i]);
  }
  std::vector<SPoint> point;
  int currP = 0;
  bool fl = true;
  while (true) {
    point.push_back(arr[currP]);
    int id = 0;
    for (int i = 0; i < arr.size(); i++) {
      if (i != currP && (fl == true || Cross(SVector(arr[currP], arr[i]),
                                           SVector(arr[currP], arr[id])) > 0)) {
        id = i;
        fl = false;
      }
    }
    if (id == 0) {
      break;
    } else {
      currP = id;
    }
  }
  return point;
}
