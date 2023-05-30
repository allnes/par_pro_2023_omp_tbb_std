// Copyright 2023 Bugrov Andrey
#include "../../../modules/task_4/bugrov_a_bin_marking/bin_marking.h"

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

// +
void first_par_pass(int** p_image, CardR* card, int n, int m, const int k_back,
                    int offset) {
  for (int i = 0; i < n; i++) {
    size_t R_n = 0;
    R tmp;
    for (size_t j = 0; j < m; j++) {
      if (p_image[i][j] != k_back) {
        R_n++;
        tmp.p_left = i * offset * m + j;
        tmp.L_next_left = tmp.L_next_right = tmp.L_prev_left =
            tmp.L_prev_right = 0;
        tmp.L = i * offset * (m / 2 + 1) + R_n;
        while (p_image[i][j] != k_back && j < m) {
          j++;
        }
        tmp.p_right = i * offset * m + j - 1;
        (*card)[i * (m / 2 + 1) + R_n - 1] = tmp;
      }
    }
  }
}

//-
// prev or next left != prev or next right
void second_par_pass(CardR* card, int n, int m) {
  const int w = m / 2 + 1;  // width of (*card)
  bool right_exists = false;
  bool was_in_while = false;
  for (int i = 0; i < n; i++) {
    int j = 0;
    // finding all segments in row
    while (j < w && (*card)[i * w + j].L != 0) {
      int to_find_adjacent_segment = (i - 1) * w;
      // finding left neighbour in (i-1)-th row
      while (i > 0 && to_find_adjacent_segment < i * w &&
             (*card)[to_find_adjacent_segment].L != 0 &&
             (*card)[to_find_adjacent_segment].p_right % m <
                 (*card)[i * w + j].p_left % m) {
        to_find_adjacent_segment++;
      }
      if (i > 0 && to_find_adjacent_segment <= i * w &&
          (*card)[to_find_adjacent_segment].L > 0 &&
          (*card)[to_find_adjacent_segment].p_left % m <=
              (*card)[i * w + j].p_right % m) {
        (*card)[i * w + j].L_prev_left = (*card)[to_find_adjacent_segment].L;
        to_find_adjacent_segment++;

        // finding right neighbour in (i-1)-th row
        while ((*card)[to_find_adjacent_segment].L != 0 &&
               to_find_adjacent_segment < i * w &&
               (*card)[to_find_adjacent_segment].p_left % m <=
                   (*card)[i * w + j].p_right % m) {
          to_find_adjacent_segment++;
          was_in_while = true;
        }
        if (was_in_while) {
          if (to_find_adjacent_segment < i * w + 1) {
            // it is not nesessary  to check does
            // (*card)[to_find_adjacent_segment-1].L != 0 or not because at
            // least one iteration (with  to_find_adjacent_segment-1 was
            // performed
            (*card)[i * w + j].L_prev_right =
                (*card)[to_find_adjacent_segment - 1].L;
          }
        } else {
          if ((*card)[to_find_adjacent_segment].p_left % m <=
                  (*card)[i * w + j].p_right % m &&
              (*card)[to_find_adjacent_segment].L != 0 &&
              to_find_adjacent_segment < i * w) {
            (*card)[i * w + j].L_prev_right =
                (*card)[to_find_adjacent_segment].L;
          }
        }
        was_in_while = false;
      }

      to_find_adjacent_segment = (i + 1) * w;

      // finding left neighbour in (i+1)-th row
      while (i < n - 1 && to_find_adjacent_segment < (i + 2) * w &&
             (*card)[to_find_adjacent_segment].L != 0 &&
             (*card)[to_find_adjacent_segment].p_right % m <
                 (*card)[i * w + j].p_left % m) {
        to_find_adjacent_segment++;
      }
      if (i < n - 1 && to_find_adjacent_segment <= (i + 2) * w &&
          (*card)[to_find_adjacent_segment].L != 0 &&
          (*card)[to_find_adjacent_segment].p_left % m <=
              (*card)[i * w + j].p_right % m) {
        (*card)[i * w + j].L_next_left = (*card)[to_find_adjacent_segment].L;
        to_find_adjacent_segment++;
        // finding right neighbour in (i+1)-th row
        while ((*card)[to_find_adjacent_segment].L != 0 &&
               (*card)[to_find_adjacent_segment].p_left % m <=
                   (*card)[i * w + j].p_right % m) {
          to_find_adjacent_segment++;
          was_in_while = true;
        }
        if ((*card)[to_find_adjacent_segment].L != 0 &&
            to_find_adjacent_segment < (i + 2) * w) {
          if (was_in_while) {
            if ((*card)[to_find_adjacent_segment - 1].p_left % m <=
                (*card)[i * w + j].p_right % m) {
              (*card)[i * w + j].L_next_right =
                  (*card)[to_find_adjacent_segment - 1].L;
            }
          } else {
            if ((*card)[to_find_adjacent_segment].p_left % m <=
                (*card)[i * w + j].p_right % m) {
              (*card)[i * w + j].L_next_right =
                  (*card)[to_find_adjacent_segment].L;
            }
          }
          was_in_while = false;
        }
      }
      j++;
    }
  }
}
void third_par_pass(CardR* card, int n, int m) {
  bool been_changed = false;
  int w = m / 2 + 1;
  do {
    been_changed = false;
    // labels - private
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < w && (*card)[i * w + j].L > 0; j++) {
        int cur_id = i * w + j;
        size_t labels[4] = {
            (*card)[cur_id].L_prev_left, (*card)[cur_id].L_prev_right,
            (*card)[cur_id].L_next_left, (*card)[cur_id].L_next_right};
        size_t cur_min = UINT64_MAX;
        for (int p = 0; p < 4; p++) {
          if (labels[p] != 0 && labels[p] < cur_min) {
            cur_min = labels[p];
          }
        }
        if (cur_min < (*card)[cur_id].L) {
          (*card)[cur_id].L = min((*card)[(*card)[cur_id].L - 1].L, cur_min);
          been_changed = true;
        }
      }
    }
  } while (been_changed);
}

//+
// TO DO: make a documentation
void forth_par_pass(CardR* card, int n, int m) {
  size_t w = m / 2 + 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      size_t L = (*card)[i * w + j].L;
      if (L > 0) {
        size_t L_i = (*card)[L - 1].L;
        while (L_i != L) {
          L_i = (*card)[L_i - 1].L;
          L = (*card)[L - 1].L;
        }
        (*card)[i * w + j].L = L_i;
      }
    }
  }
}

//-
// TO DO: make a documentation
void mark_assign_pass(CardR* card, vector<vector<int>>* p_marks, int n, int m) {
  size_t w = m / 2 + 1;
  // real_numbers[counter] = label of component which should be named as counter
  vector<size_t> real_numbers;
  real_numbers.resize(n * w + 1);
  size_t counter = 1;
  int p = 0;
  for (; p < n; p++) {
    if ((*card)[p * w].L != 0) {
      real_numbers[(*card)[p * w].L] = 1;
      break;
    }
  }
  if ((*card)[p * w].L == 0) {
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if ((*card)[i * w + j].L == 0) {
        /*std::cout << "i = " << i << " j = " << j << "\n";*/
        break;
      }
      if (real_numbers[(*card)[i * w + j].L] != 0) {
        (*card)[i * w + j].L = real_numbers[(*card)[i * w + j].L];
      } else {
        // if ((*card)[i * w + j].L != 0) {
        counter++;
        real_numbers[(*card)[i * w + j].L] = counter;
        (*card)[i * w + j].L = real_numbers[(*card)[i * w + j].L];
        //}
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if ((*card)[i * w + j].L == 0) {
        break;
      }
      //&& (*card)[i * w + j].L != 0; j++) {
      size_t begin = (*card)[i * w + j].p_left % m;
      size_t end = (*card)[i * w + j].p_right % m;
      while (begin <= end) {
        (*p_marks)[i][begin] = (*card)[i * w + j].L;
        begin++;
      }
    }
  }
}
void parallel_passes(int** image, CardR* card, const int n, const int m,
                     const int k_back, int offset) {
  first_par_pass(image, card, n, m, k_back, offset);
  second_par_pass(card, n, m);
  third_par_pass(card, n, m);
  forth_par_pass(card, n, m);
}

void par_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed,
                 const int thread_num = 4) {
  int cur_mark = 1;
  const int k_back = 1;  // backround of image (white color)
  std::thread* workers = new std::thread[thread_num];
  int part = n / thread_num;
  int remainder = n % thread_num;
  R* card = new R[(m / 2+1) * n];
  for (int i = 0; i < thread_num - 1; i++) {
    small_cards[i] = new CardR(m, part);
  }
  small_cards[thread_num - 1] = new CardR(m, part + remainder);
  int** p_image = new int*[n];
  for (int i = 0; i < n; i++) {
    p_image[i] = new int[m];
    for (int j = 0; j < m; j++) {
      p_image[i][j] = image[i][j];
    }
  }
  for (int i = 0; i < thread_num - 1; i++) {
    workers[i] = std::thread(parallel_passes, p_image + i * part,
                             small_cards[i], part, m, k_back, part * i);
  }
  workers[thread_num - 1] =
      std::thread(parallel_passes, p_image + (thread_num - 1) * part,
                  small_cards[thread_num - 1], part + remainder, m, k_back,
                  part * (thread_num - 1));
  for (int i = 0; i < thread_num; i++) {
    workers[i].join();
  }
  for (int i = 0; i < thread_num - 1; i++) {
    for (int j = 0; j < (m / 2 + 1) * part; j++) {
      card[i * part * (m / 2 + 1) + j] = (*small_cards[i])[j];
    }
  }
  for (int j = 0; j < (m / 2 + 1) * part; j++) {
    card[(thread_num - 1) * part * (m / 2 + 1) + j] =
        (*small_cards[(thread_num - 1)])[j];
  }
  for (int i = 0; i < n; i++) {
    delete[] p_image[i];
  }
  delete[] p_image;
  // should be non-parallel
  mark_assign_pass(&card, marks, n, m);
  delete[] workers;
}
