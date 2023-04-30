// Copyright 2023 Nosonova Darina
#include <omp.h>

#include <list>
#include <vector>
#include "../../../modules/task_2/nosonova_d_double_radix_sort_omp/nosonova_d_double_radix_sort_omp.h"

void RadixSort(DCArray *array) {
    std::vector<std::vector<convDouble>> cArr(256);
    int digit = 0;
    // first bait initialization
    for (int i = 0; i < array->size; i++) {
        int zn{static_cast<int>(array->data[i].ch[digit])};
        cArr.at(zn).push_back(array->data[i]);
    }

    digit++;
    for (; digit <= 7; digit++) {
        std::vector<std::vector<convDouble>> reachVector(256);
        for (int i = 0; i < 256; i++) {
            for (auto j : cArr.at(i)) {
                int zn{static_cast<int>(j.ch[digit])};
                reachVector.at(zn).push_back(j);
            }
        }
        cArr = reachVector;
    }
    std::list<convDouble> ResultList;
    for (int i = 0; i < 256; i++) {
        for (auto j : cArr.at(i)) {
            int zn = static_cast<int>(j.ch[7]);
            if (zn & 128)
                ResultList.push_front(j);
            else
                ResultList.push_back(j);
        }
    }

    // convertation
    int i = 0;
    for (auto it : ResultList) {
        array->data[i] = it;
        i++;
    }
}

DCArray Merge(const DCArray &left, const DCArray &right) {
    DCArray result(left.size + right.size);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < left.size && j < right.size) {
        if (left.data[i].d < right.data[j].d) {
            result.data[k] = left.data[i];
            i++;
        } else {
            result.data[k] = right.data[j];
            j++;
        }
        k++;
    }
    while (i < left.size) {
        result.data[k] = left.data[i];
        k++;
        i++;
    }
    while (j < right.size) {
        result.data[k] = right.data[j];
        k++;
        j++;
    }

    return result;
}

void OMPRadixSort(DCArray *array, int threads_nom) {
    int delta = array->size / threads_nom;
    int ost = array->size % threads_nom;

    omp_set_num_threads(threads_nom);

    DCArray result(0);

#pragma omp parallel
    {
        int threadNom = omp_get_thread_num();

        int leftArrBound;
        int rightArrBound;

        if (threadNom == 0) {
            leftArrBound = 0;
            rightArrBound = delta + ost;
        } else {
            leftArrBound = (delta * threadNom) + ost;
            rightArrBound = leftArrBound + delta;
        }

        DCArray local_arr = array->getPart(leftArrBound, rightArrBound);

        RadixSort(&local_arr);

#pragma omp critical
        result = Merge(result, local_arr);
    }

    for (int i = 0; i < array->size; i++) {
        array->data[i] = result.data[i];
    }
}
