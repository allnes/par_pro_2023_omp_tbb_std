// Copyright 2023 Nosonova Darina
#ifndef MODULES_TASK_2_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_H_
#define MODULES_TASK_2_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_H_

#include <bitset>
#include <random>

union convDouble {
    double d;
    unsigned char ch[8];
};

struct DCArray {
    int size;
    convDouble *data;

    explicit DCArray(int _size = 0) : size(_size) { data = new convDouble[size]; }

    DCArray getPart(int first, int last) {
        if ((last > size) || (first < 0)) {
            return DCArray();
        }

        int size = last - first;
        DCArray result(size);

        for (int i = 0; i < size; i++) {
            result.data[i] = data[first + i];
        }

        return result;
    }

    bool isSorted() {
        for (int i = 1; i < size; i++) {
            if (data[i - 1].d > data[i].d) return false;
        }
        return true;
    }

    void setRandValue(double lower_bound, double upper_bound) {
        for (int i = 0; i < size; i++) {
            std::random_device rd;
            std::mt19937 gen(rd());
            int r = static_cast<int>(gen());

            data[i].d =
                lower_bound + ((upper_bound - lower_bound) * r / RAND_MAX);
        }
    }

    DCArray(const DCArray &leftVal) : size(leftVal.size) {
        data = new convDouble[size];
        for (int i = 0; i < size; i++) {
            data[i] = leftVal.data[i];
        }
    }

    DCArray &operator=(const DCArray &leftVal) {
        if (this == &leftVal) return *this;
        size = leftVal.size;
        data = new convDouble[size];
        for (int i = 0; i < size; i++) {
            data[i] = leftVal.data[i];
        }
        return *this;
    }

    DCArray(DCArray &&leftVal) : size(leftVal.size), data(leftVal.data) {
        leftVal.data = nullptr;
    }

    DCArray &operator=(DCArray &&leftVal) {
        if (this == &leftVal) return *this;
        size = leftVal.size;
        data = leftVal.data;
        leftVal.data = nullptr;
        return *this;
    }

    ~DCArray() { delete[] data; }
};

void RadixSort(DCArray *array);

DCArray Merge(const DCArray &left, const DCArray &right);

void OMPRadixSort(DCArray *array, int threads_nom);

#endif  // MODULES_TASK_2_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_NOSONOVA_D_DOUBLE_RADIX_SORT_OMP_H_
