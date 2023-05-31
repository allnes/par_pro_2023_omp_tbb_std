// Copyright 2023 Bugrov Andrey
#include "../../../modules/task_4/bugrov_a_bin_marking/bin_marking.h"
#include "../../../3rdparty/unapproved/unapproved.h"

// matrixes can be both vectors and arrays

// matrixes can be both vectors and arrays
void seq_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed = 0) {
  int cur_mark = 0;
  const int k_back = 1;
  queue<pair<int, int>> cur_queue;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (image[i][j] != k_back && (*marks)[i][j] == k_unnamed) {
        cur_mark += 1;
        (*marks)[i][j] = cur_mark;
        cur_queue.push(pair<int, int>(i, j));
        while (!cur_queue.empty()) {
          pair<int, int> tmp = cur_queue.front();
          cur_queue.pop();
          if (tmp.first - 1 >= 0) {
            if ((*marks)[tmp.first - 1][tmp.second] == k_unnamed &&
                image[tmp.first - 1][tmp.second] != k_back) {
              (*marks)[tmp.first - 1][tmp.second] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first - 1, tmp.second));
            }
          }
          if (tmp.second - 1 >= 0) {
            if ((*marks)[tmp.first][tmp.second - 1] == k_unnamed &&
                image[tmp.first][tmp.second - 1] != k_back) {
              (*marks)[tmp.first][tmp.second - 1] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first, tmp.second - 1));
            }
          }
          if (tmp.first + 1 < n) {
            if ((*marks)[tmp.first + 1][tmp.second] == k_unnamed &&
                image[tmp.first + 1][tmp.second] != k_back) {
              (*marks)[tmp.first + 1][tmp.second] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first + 1, tmp.second));
            }
          }
          if (tmp.second + 1 < m) {
            if ((*marks)[tmp.first][tmp.second + 1] == k_unnamed &&
                image[tmp.first][tmp.second + 1] != k_back) {
              (*marks)[tmp.first][tmp.second + 1] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first, tmp.second + 1));
            }
          }
        }
      }
    }
  }
}

void first_par_pass(int** p_image, R* card, int n, int m, const int k_back,
                    int offset) {
  for (int i = offset; i < n; i++) {
    size_t R_n = 0;
    R tmp;
    for (size_t j = 0; j < m; j++) {
      // std::cout << i * n + j << "\n";
      if (p_image[i][j] != k_back) {
        R_n++;
        tmp.p_left = i * m + j;
        tmp.L_next_left = tmp.L_next_right = tmp.L_prev_left =
            tmp.L_prev_right = 0;
        tmp.L = i * (m / 2 + 1) + R_n;
        while (p_image[i][j] != k_back && j < m) {
          j++;
        }
        tmp.p_right = i * m + j - 1;
        card[i * (m / 2 + 1) + R_n - 1] = tmp;
      }
    }
  }
}

void find_neighbours(R* card, int i, int j, int n, int m, int neighbour) {
  bool was_in_while = false;
  const int w = m / 2 + 1;  // width of card
  int to_find_adjacent_segment = neighbour * w;
  int bound;
  if (neighbour > i) {
    bound = n - 1;
  } else {
    bound = 0;
  }
  if (i != bound) {
    // finding left neighbour
    while (to_find_adjacent_segment < (neighbour + 1) * w &&
           card[to_find_adjacent_segment].L != 0 &&
           card[to_find_adjacent_segment].p_right % m <
               card[i * w + j].p_left % m) {
      to_find_adjacent_segment++;
    }
    if (to_find_adjacent_segment < (neighbour + 1) * w &&
        card[to_find_adjacent_segment].L != 0 &&
        card[to_find_adjacent_segment].p_left % m <=
            card[i * w + j].p_right % m) {
      if (neighbour < i) {
        card[i * w + j].L_prev_left = card[to_find_adjacent_segment].L;
      } else {
        card[i * w + j].L_next_left = card[to_find_adjacent_segment].L;
      }
      to_find_adjacent_segment++;
      // finding right neighbour
      while (card[to_find_adjacent_segment].L != 0 &&
             to_find_adjacent_segment < (neighbour + 1) * w &&
             card[to_find_adjacent_segment].p_left % m <=
                 card[i * w + j].p_right % m) {
        to_find_adjacent_segment++;
        was_in_while = true;
      }
      if (was_in_while) {
        if (to_find_adjacent_segment - 1 < (neighbour + 1) * w) {
          // it is not nesessary to check
          // card[to_find_adjacent_segment-1].L != 0 and or not because at
          // least one iteration (with  to_find_adjacent_segment-1) was
          // performed
          if (neighbour < i) {
            card[i * w + j].L_prev_right = card[to_find_adjacent_segment - 1].L;
          } else {
            card[i * w + j].L_next_right = card[to_find_adjacent_segment - 1].L;
          }
        }
      }
    }
  }
}
void second_par_pass(R* card, int n, int m, int offset) {
  const int w = m / 2 + 1;  // width of card
  for (int i = offset; i < n; i++) {
    int j = 0;
    // finding all segments in row
    for (int j = 0; j < w && card[i * w + j].L != 0; j++) {
      find_neighbours(card, i, j, n, m, i - 1);
      find_neighbours(card, i, j, n, m, i + 1);
    }
  }
}

void third_par_pass(R* card, int n, int m, int offset, bool* been_changed) {
  // labels - private
  size_t w = m / 2 + 1;
  // std::cout << offset << " ";
  for (int i = offset; i < n; i++) {
    for (int j = 0; j < w && card[i * w + j].L > 0; j++) {
      int cur_id = i * w + j;
      size_t labels[4];
      if (card[cur_id].L_prev_left != 0) {
        labels[0] = card[card[cur_id].L_prev_left - 1].L;
      } else {
        labels[0] = UINT64_MAX;
      }
      if (card[cur_id].L_prev_right != 0) {
        labels[1] = card[card[cur_id].L_prev_right - 1].L;
      } else {
        labels[1] = UINT64_MAX;
      }
      if (card[cur_id].L_next_left != 0) {
        labels[2] = card[card[cur_id].L_next_left - 1].L;
      } else {
        labels[2] = UINT64_MAX;
      }
      if (card[cur_id].L_next_right != 0) {
        labels[3] = card[card[cur_id].L_next_right - 1].L;
      } else {
        labels[3] = UINT64_MAX;
      }
      size_t cur_min = UINT64_MAX;
      for (int p = 0; p < 4; p++) {
        if (labels[p] != 0 && labels[p] < cur_min) {
          cur_min = labels[p];
        }
      }
      if (cur_min < card[cur_id].L) {
        card[cur_id].L = min(card[card[cur_id].L - 1].L, cur_min);
        (*been_changed) = true;
      }
    }
  }
}

void forth_par_pass(R* card, int n, int m, int offset) {
  size_t w = m / 2 + 1;
  for (int i = offset; i < n; i++) {
    for (int j = 0; j < w; j++) {
      size_t L = card[i * w + j].L;
      if (L > 0) {
        size_t L_i = card[L - 1].L;
        while (L_i != L) {
          L_i = card[L_i - 1].L;
          L = card[L - 1].L;
        }
        card[i * w + j].L = L_i;
      }
    }
  }
}
void mark_assign_pass(R* card, vector<vector<int>>* p_marks, int n, int m) {
  size_t w = m / 2 + 1;
  // real_numbers[counter] = label of component which should be named as counter
  vector<size_t> real_numbers;
  real_numbers.resize(n * w + 1);
  size_t counter = 1;
  int p = 0;
  for (; p < n; p++) {
    if (card[p * w].L != 0) {
      real_numbers[card[p * w].L] = 1;
      break;
    }
  }
  if (card[p * w].L == 0) {
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if (card[i * w + j].L == 0) {
        /*std::cout << "i = " << i << " j = " << j << "\n";*/
        break;
      }
      if (real_numbers[card[i * w + j].L] != 0) {
        card[i * w + j].L = real_numbers[card[i * w + j].L];
      } else {
        // if (card[i * w + j].L != 0) {
        counter++;
        real_numbers[card[i * w + j].L] = counter;
        card[i * w + j].L = real_numbers[card[i * w + j].L];
        //}
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if (card[i * w + j].L == 0) {
        break;
      }
      //&& card[i * w + j].L != 0; j++) {
      size_t begin = card[i * w + j].p_left % m;
      size_t end = card[i * w + j].p_right % m;
      while (begin <= end) {
        (*p_marks)[i][begin] = card[i * w + j].L;
        begin++;
      }
    }
  }
}
void parallel_passes(int** image, R* card, const int n, const int m,
                     const int k_back, int offset) {
  first_par_pass(image, card, n, m, k_back, offset);
  second_par_pass(card, n, m, offset);
  /*third_par_pass(card, n, m, offset);
  forth_par_pass(card, n, m, offset);*/
}

void par_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed,
                 const int thread_num = 4) {
  int cur_mark = 1;
  const int k_back = 1;  // backround of image (white color)
  std::thread* workers = new std::thread[thread_num];
  int part = n / thread_num;
  // int remainder = n % thread_num;
  R* card = new R[(m / 2 + 1) * n];
  int** p_image = new int*[n];
  for (int i = 0; i < n; i++) {
    p_image[i] = new int[m];
    for (int j = 0; j < m; j++) {
      p_image[i][j] = image[i][j];
    }
  }
  int offset = 0;
  for (int i = 0; i < thread_num - 1; i++) {
    workers[i] = std::thread(parallel_passes, p_image, card, part + offset, m,
                             k_back, offset);
    offset += part;
  }
  workers[thread_num - 1] =
      std::thread(parallel_passes, p_image, card, n, m, k_back, offset);
  for (int i = 0; i < thread_num; i++) {
    workers[i].join();
  }
  offset = 0;
  for (int i = 0; i < thread_num - 1; i++) {
    workers[i] = std::thread(second_par_pass, card, part + offset, m, offset);
    offset += part;
  }
  offset = (thread_num - 2) * part;
  workers[thread_num - 1] = std::thread(second_par_pass, card, n, m, offset);
  for (int i = 0; i < thread_num; i++) {
    workers[i].join();
  }
  for (int i = 0; i < n; i++) {
    delete[] p_image[i];
  }
  delete[] p_image;
  bool been_changed;

  do {
    offset = 0;
    been_changed = false;
    for (int i = 0; i < thread_num - 1; i++) {
      workers[i] = std::thread(third_par_pass, card, part + offset, m, offset,
                               &been_changed);
      offset += part;
    }
    offset = (thread_num - 2) * part;
    workers[thread_num - 1] =
        std::thread(third_par_pass, card, n, m, offset, &been_changed);
    for (int i = 0; i < thread_num; i++) {
      workers[i].join();
    }
  } while (been_changed);
  offset = 0;

  forth_par_pass(card, n, m, 0);
  int out_card[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      out_card[i][j] = 0;
    }
  }
  // should be non-parallel
  mark_assign_pass(card, marks, n, m);
  delete[] workers;
}
