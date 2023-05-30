// Copyright 2023 Bugrov Andrey
#pragma once
#include <time.h>  // rand seed

#include <algorithm>  // min
#include <iostream>   // checksk
#include <map>        // pairs
#include <queue>      // queue for Depth-first search
#include <random>     // mt19937
#include <thread>     //thread
#include <vector>     // vector
using std::min;
using std::mt19937;
using std::pair;
using std::queue;
using std::vector;

void seq_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed);
bool are_matrix_eq(const vector<vector<int>>& a, const vector<vector<int>>& b,
                   int n, int m);
void par_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed,
                 const int thread_num);
struct R {
  // label
  size_t L;
  size_t p_left;
  size_t p_right;
  size_t L_prev_left;
  size_t L_prev_right;
  size_t L_next_left;
  size_t L_next_right;
  R()
      : L(0),
        p_left(0),
        p_right(0),
        L_prev_left(0),
        L_prev_right(0),
        L_next_left(0),
        L_next_right(0) {}
  const R& operator=(const R& r) {
    L = r.L;
    p_left = r.p_left;
    p_right = r.p_right;
    L_prev_left = r.L_prev_left;
    L_prev_right = r.L_prev_right;
    L_next_left = r.L_next_left;
    L_next_right = r.L_next_right;
    return *this;
  }
};
struct CardR {
 public:
  vector<R> card;
  size_t size_;

 public:
  CardR(size_t width, size_t height)
      : size_((width / 2 + 1) * height), card(0) {
    card.resize(size_);
  }
  R& operator[](size_t i) { return card[i]; }
  const CardR& operator=(const CardR& card_) {
    card = card_.card;
    size_ = card_.size_;
    return *this;
  }
};

// void first_par_pass(int** p_image, CardR& card, int n, int m, const int
// k_back); void second_par_pass(CardR& card, int n, int m); void
// third_par_pass(CardR& card, int n, int m);

// struct EqLabel {
//  size_t label;
//
// public:
//  EqLabel(size_t label_ = 0) : label(label_) {}
// };
