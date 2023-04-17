// Copyright 2023 Tolkachev
#include "../../../modules/task_1/tolkachev_n_hoar_merge/hoar_merge.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
std::vector<int> Getvec(int n) {
  std::random_device randomDevice;
  std::mt19937 engine(randomDevice());
  std::uniform_int_distribution<> dist(0, 100);
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    vec[i] = dist(engine);
  }
  return vec;
}
void HoarSort(std::vector<int>* arr, int first, int last) {
  std::vector<int>& s = *arr;
  int left = first;
  int right = last;
  int middle = s[(first + last) / 2];

  do {
    while (s[left] < middle) left++;
    while (s[right] > middle) right--;

    if (left <= right) {
      if (s[left] > s[right]) {
        std::swap(s[left], s[right]);
      }
      left++;
      right--;
    }
  } while (left <= right);

  if (left < last) HoarSort(&s, left, last);
  if (first < right) HoarSort(&s, first, right);
}
void Merge(std::vector<int>* arr, std::vector<int>* arr2, int left, int mid,
           int right) {
  std::vector<int>& s = *arr;
  std::vector<int>& s2 = *arr2;
  int k = left;
  int l = left;
  int r = mid + 1;
  while (l <= mid && r <= right) {
    if (s[l] > s[r]) {
      s2[k] = s[r];
      k++;
      r++;
    } else {
      s2[k] = s[l];
      k++;
      l++;
    }
  }
  while (l <= mid) {
    s2[k] = s[l];
    k++;
    l++;
  }
  for (int i = left; i <= right; i++) {
    s[i] = s2[i];
  }
}

void MergeSort(std::vector<int>* arr, std::vector<int>* arr2, int left,
               int right) {
  if (left != right) {
    int mid = left + (right - left) / 2;
    MergeSort(arr, arr2, left, mid);
    MergeSort(arr, arr2, mid + 1, right);
    Merge(arr, arr2, left, mid, right);
  } else {
    return;
  }
}
