// Copyright 2023 Silaeva Natalya

#ifndef MODULES_TASK_3_SILAEVA_N_RADIX_SORT_DOUBLE_BATCHER_RADIX_SORT_DOUBLE_BATCHER_H_
#define MODULES_TASK_3_SILAEVA_N_RADIX_SORT_DOUBLE_BATCHER_RADIX_SORT_DOUBLE_BATCHER_H_

#include<vector>

class OddEvenMerge {
    std::vector<int> complete_to_end(const std::vector<int>& vec1,
        const std::vector<int>& vec2, int count_vec1, int count_vec2) {
        std::vector<int> result;
        int vec1_size = vec1.size();
        if (count_vec1 < vec1_size) {
            for (int i = count_vec1; i < vec1_size; i += 2) {
                result.push_back(vec1[i]);
            }
        }
        int vec2_size = vec2.size();
        if (count_vec2 < vec2_size) {
            for (int i = count_vec2; i < vec2_size; i += 2) {
                result.push_back(vec2[i]);
            }
        }

        return result;
    }

    std::vector<int> get_even_part(const std::vector<int>& vec1,
        const std::vector<int>& vec2) {
        std::vector<int> even_part;
        int count_vec1 = 0;
        int count_vec2 = 0;
        int vec1_size = vec1.size();
        int vec2_size = vec2.size();
        while (count_vec1 < vec1_size && count_vec2 < vec2_size) {
            if (vec1[count_vec1] < vec2[count_vec2]) {
                even_part.push_back(vec1[count_vec1]);
                count_vec1 += 2;
            } else {
                even_part.push_back(vec2[count_vec2]);
                count_vec2 += 2;
            }
        }

        std::vector<int> end_vector = complete_to_end(vec1, vec2,
            count_vec1, count_vec2);
        even_part.insert(even_part.end(), end_vector.begin(), end_vector.end());

        return even_part;
    }

    std::vector<int> get_odd_part(const std::vector<int>& vec1,
        const std::vector<int>& vec2) {
        std::vector<int> odd_part;
        int count_vec1 = 1;
        int count_vec2 = 1;
        int vec1_size = vec1.size();
        int vec2_size = vec2.size();
        while (count_vec1 < vec1_size && count_vec2 < vec2_size) {
            if (vec1[count_vec1] < vec2[count_vec2]) {
                odd_part.push_back(vec1[count_vec1]);
                count_vec1 += 2;
            } else {
                odd_part.push_back(vec2[count_vec2]);
                count_vec2 += 2;
            }
        }

        std::vector<int> end_vector = complete_to_end(vec1, vec2,
            count_vec1, count_vec2);
        odd_part.insert(odd_part.end(), end_vector.begin(), end_vector.end());

        return odd_part;
    }
    
 public:
    std::vector<int> odd_even_merge(const std::vector<int>& vec1,
                                    const std::vector<int>& vec2) {
        std::vector<int> even_vec = get_even_part(vec1, vec2);
        std::vector<int> odd_vec = get_odd_part(vec1, vec2);
        std::vector<int> result;
        if (!even_vec.empty()) {
            result.push_back(even_vec[0]);
        }
        int count_vec1 = 1;
        int count_vec2 = 0;
        int even_vec_size = even_vec.size();
        int odd_vec_size = odd_vec.size();
        while (count_vec1 < even_vec_size && count_vec2 < odd_vec_size) {
            if (even_vec[count_vec1] < odd_vec[count_vec2]) {
                result.push_back(even_vec[count_vec1]);
                result.push_back(odd_vec[count_vec2]);
            } else {
                result.push_back(odd_vec[count_vec2]);
                result.push_back(even_vec[count_vec1]);
            }
            count_vec1++;
            count_vec2++;
        }
        std::vector<int> end_vector = complete_to_end(even_vec, odd_vec,
                                                      count_vec1, count_vec2);
        result.insert(result.end(), end_vector.begin(), end_vector.end());
        return result;
    }
};

std::vector<std::vector<int>> get_vector_part_tbb(const std::vector<int>& vec,
    unsigned int part);
std::vector<int> to_int_tbb(const std::vector<double>& vec,
    unsigned int count);
std::vector<double> to_double_tbb(const std::vector<int>& vec,
    unsigned int count);
std::vector<int> counting_sort_tbb(const std::vector<int>& vec, int div);
std::vector<double> radix_sort_tbb(const std::vector<double>& vec,
    unsigned int count);

bool check_sort(const std::vector<double>& vec);
std::vector<double> get_random_double_vector(unsigned int elements);

#endif  // MODULES_TASK_3_SILAEVA_N_RADIX_SORT_DOUBLE_BATCHER_RADIX_SORT_DOUBLE_BATCHER_H_
