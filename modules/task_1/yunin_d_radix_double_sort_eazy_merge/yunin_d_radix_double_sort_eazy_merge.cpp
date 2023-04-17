// Copyright 2023 Yunin Daniil
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include "../../../modules/task_1/yunin_d_radix_double_sort_eazy_merge/yunin_d_radix_double_sort_eazy_merge.h"

void printVector(const std::vector<double>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<double> randomVec(int size, int leftBound, int rightBound) {
    std::vector<double> vec(size);
    std::mt19937 gen;
    gen.seed(static_cast<uint32_t>(time(0)));
    std::uniform_real_distribution<double> buf(leftBound, rightBound);
    std::transform(vec.begin(), vec.end(), vec.begin(),
        [&](double x) { return buf(gen); });
    return vec;
}

std::vector<double> merge(const std::vector<double>& arr1,
    const std::vector<double>& arr2) {
    int len1 = arr1.size();
    int len2 = arr2.size();
    std::vector<double> out;
    out.resize(len1 + len2);
    int indexFirst = 0, indexSecond = 0;
    for (int i = 0; i < len1 + len2; i++) {
        if (indexFirst == len1) {
            out[i] = arr2[indexSecond];
            indexSecond++;
            continue;
        }
        if (indexSecond == len2) {
            out[i] = arr1[indexFirst];
            indexFirst++;
            continue;
        }
        if (arr1[indexFirst] > arr2[indexSecond]) {
            out[i] = arr2[indexSecond];
            indexSecond++;
        } else if (arr1[indexFirst] <= arr2[indexSecond]) {
            out[i] = arr1[indexFirst];
            indexFirst++;
        }
    }
    return out;
}

void countSort(double* in, double* out, int len, int exp) {
    unsigned char* buf = reinterpret_cast<unsigned char*>(in);
    int count[256] = { 0 };
    for (int i = 0; i < len; i++) {
        count[buf[8 * i + exp]]++;
    }
    /*for (int i = 0; i < 256; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;*/
    int sum = 0;
    for (int i = 0; i < 256; i++) {
        int temp = count[i];
        count[i] = sum;
        sum += temp;
    }
    /*for (int i = 0; i < 256; i++) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;*/
    for (int i = 0; i < len; i++) {
        out[count[buf[8 * i + exp]]] = in[i];
        count[buf[8 * i + exp]]++;
    }
}

bool countSortFinalStep(double* in, double* out, int len) {
    int firstNegativeIndex = -1;
    int firstPositiveIndex = -1;
    bool positiveFlag = false, negativeFlag = false;
    for (int i = 0; i < len; i++) {
        if (positiveFlag && negativeFlag) {
            break;
        }
        if (in[i] < 0 && !negativeFlag) {
            firstNegativeIndex = i;
            negativeFlag = true;
        }
        if (in[i] > 0 && !positiveFlag) {
            firstPositiveIndex = i;
            positiveFlag = true;
        }
    }
    if (positiveFlag && negativeFlag) {
        int j = len - 1;
        bool flag = false;
        for (int i = 0; i < len; i++) {
            out[i] = in[j];
            if (flag) {
                j++;
            } else {
                j--;
            }
            if (j == firstNegativeIndex - 1 && !flag) {
                j = 0;
                flag = true;
            }
        }
        return true;
    } else if (!positiveFlag) {
        for (int i = len - 1, j = 0; i >= 0; i--, j++) {
            out[j] = in[i];
        }
        return true;
    }
    return false;
}

std::vector<double> radixSort(const std::vector<double>& data1,
    const std::vector<double>& data2) {
    int len1 = static_cast<int>(data1.size());
    int len2 = static_cast<int>(data2.size());
    std::vector<double> in1 = data1;
    std::vector<double> out1(data1.size());
    std::vector<double> in2 = data2;
    std::vector<double> out2(data2.size());
    for (int i = 0; i < 4; i++) {
        countSort(in1.data(), out1.data(), len1, 2 * i);
        countSort(out1.data(), in1.data(), len1, 2 * i + 1);
    }
    if (!countSortFinalStep(in1.data(), out1.data(), len1)) {
        in1.swap(out1);
    }
    for (int i = 0; i < 4; i++) {
        countSort(in2.data(), out2.data(), len2, 2 * i);
        countSort(out2.data(), in2.data(), len2, 2 * i + 1);
    }
    if (!countSortFinalStep(in2.data(), out2.data(), len2)) {
        in2.swap(out2);
    }
    return merge(out1, out2);
}

