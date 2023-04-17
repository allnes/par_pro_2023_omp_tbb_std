  // Copyright 2023 Polyackov Lev
#include "../../modules/task_4/polyackov_l_shell_sort_std/polyackov_l_shell_sort_std.h"

std::vector<int> get_random_vec(int size, unsigned int seed) {
  std::mt19937 gen;
  gen.seed(seed);

  std::vector<int> vec(size);

  for (int i = 0; i < size; i++) {
    vec[i] = gen() % 100;
  }

  return vec;
}

std::vector<int> shell_sort_seq(const std::vector<int>& vec) {
  std::vector<int> result_vec(vec);

  for (int delta = result_vec.size() / 2; delta > 0; delta /= 2) {
    for (int i = delta; i < result_vec.size(); i++) {
      int tmp = result_vec[i];

      int j;
      for (j = i; j >= delta && result_vec[j - delta] > tmp; j -= delta)
        result_vec[j] = result_vec[j - delta];

      result_vec[j] = tmp;
    }
  }
  return result_vec;
}

std::vector<int> simple_merge(const std::vector<int>& first_vec, const std::vector<int>& second_vec) {
  int i = 0, j = 0, k = 0;

  int first_size = first_vec.size();
  int second_size = second_vec.size();

  std::vector<int> result_vec(first_size + second_size);

  while (first_size != 0 && second_size != 0) {
    if (first_vec[i] < second_vec[j]) {
      result_vec[k] = first_vec[i++];
      first_size--;
    } else {
      result_vec[k] = second_vec[j++];
      second_size--;
    }
    k++;
  }

  if (first_size == 0) {
    for (int m = j; m < j + second_size; k++, m++) {
      result_vec[k] = second_vec[m];
    }
  } else if (second_size == 0) {
    for (int m = i; m < i + first_size; k++, m++) {
      result_vec[k] = first_vec[m];
    }
  }

  return result_vec;
}

std::vector<std::vector<int>> simple_separate(const std::vector<int>& vec, int num_of_parts) {
  std::vector<std::vector<int>> result_vec;
  std::vector<int> tmp;

  if (num_of_parts < 2 || vec.size() < num_of_parts) {
    result_vec.push_back(vec);
    return result_vec;
  }

  int i = 0;
  int chunk = vec.size() / num_of_parts;
  for (i = 0; i < num_of_parts - 1; i++) {
    tmp.insert(tmp.end(), vec.begin() + i * chunk, vec.begin() + i * chunk + chunk);
    result_vec.push_back(tmp);
    tmp.clear();
  }
  tmp.insert(tmp.end(), vec.begin() + i * chunk, vec.end());
  result_vec.push_back(tmp);

  return result_vec;
}

std::vector<int> shell_sort_with_simple_merge_seq(const std::vector<int>& vec, int num_of_parts) {
  std::vector<std::vector<int>> tmp_res = simple_separate(vec, num_of_parts);

  std::vector<int> res;

  for (int i = 0; i < tmp_res.size(); i++) {
    tmp_res[i] = shell_sort_seq(tmp_res[i]);
    res = simple_merge(res, tmp_res[i]);
  }

  return res;
}

std::vector<int> shell_sort_with_simple_merge_std(const std::vector<int>& vec, int num_of_parts) {
  std::vector<std::vector<int>> tmp_res = simple_separate(vec, num_of_parts);

  std::vector<int> res;

  std::vector<std::thread> threads;
  for (int i = 0; i < tmp_res.size(); ++i) {
    threads.emplace_back([i, &tmp_res]() {
      tmp_res[i] = shell_sort_seq(tmp_res[i]);
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }

  for (int i = 0; i < tmp_res.size(); i++) {
    res = simple_merge(res, tmp_res[i]);
  }

  return res;
}
