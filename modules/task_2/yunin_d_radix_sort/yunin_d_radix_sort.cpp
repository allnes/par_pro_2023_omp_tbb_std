// Copyright 2023 Yunin Daniil
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../../../modules/task_2/yunin_d_radix_sort/yunin_d_radix_sort.h"

void printVector(const std::vector<double>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<double> getRandomVector(int  size, int leftBound, int rightBound) {
    std::vector<double> vec(size);
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> buf(leftBound, rightBound);
    for (int i = 0; i < size; i++) {
        vec[i] = buf(gen);
    }
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



std::vector<double> radixSortSeq(const std::vector<double>& data) {
    int len = static_cast<int>(data.size());
    std::vector<double> in = data;
    std::vector<double> out(data.size());
    for (int i = 0; i < 4; i++) {
        countSort(in.data(), out.data(), len, 2 * i);
        countSort(out.data(), in.data(), len, 2 * i + 1);
    }
    if (!countSortFinalStep(in.data(), out.data(), len)) {
        in.swap(out);
    }
    return out;
}

std::vector<std::vector<double>> splitVector(const std::vector<double>& data, int numParts) {
    std::vector<std::vector<double>> resultVec;
    std::vector<double> tmp;

    if (numParts < 2 || data.size() < numParts) {
        resultVec.push_back(data);
        return resultVec;
    }

    int i = 0;
    int part = (data.size() / numParts) + 1;
    for (i = 0; i < numParts - 1; i++) {
        for (int j = i * part; j < (i + 1) * part; j++) {
            tmp.push_back(data[j]);
        }
        resultVec.push_back(tmp);
        tmp.clear();
    }
    for (int j = i * part; j < data.size(); j++) {
        tmp.push_back(data[j]);
    }
    resultVec.push_back(tmp);
    return resultVec;
}

std::vector<double> radixSortParallOmp(const std::vector<double>& data, int numParts) {
    std::vector<std::vector<double>> vectorsForParallel = splitVector(data, numParts);
    std::vector<double> finalResult;
    omp_set_num_threads(vectorsForParallel.size());
    // auto start1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < vectorsForParallel.size(); ++i) {
        vectorsForParallel[i] = radixSortSeq(vectorsForParallel[i]);
    }

    // auto stop1 = std::chrono::high_resolution_clock::now();
    // auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    // std::cout << "duration_omp: " << duration1.count() << '\n';
    for (int i = 0; i < vectorsForParallel.size(); i++) {
        finalResult = merge(finalResult, vectorsForParallel[i]);
    }
    // printVector(finalResult);
    return finalResult;
}
