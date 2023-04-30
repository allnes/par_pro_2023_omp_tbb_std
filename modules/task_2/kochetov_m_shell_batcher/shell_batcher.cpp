// Copyright 2023 Kochetov Maksim
#include "../../../modules/task_2/kochetov_m_shell_batcher/shell_batcher.h"

std::vector<int> GetRandomVec(int length) {
    std::random_device rndDev;
    std::mt19937 engine(rndDev());
    std::uniform_int_distribution<> dist(1, 100);
    std::vector<int> vec(length);
    for (int i = 0; i < length; i++)
        vec[i] = dist(engine);
    return vec;
}

void PrintVec(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PrintVec(int* vec, int n) {
    for (int i = 0; i < n; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

bool Is2Power(int number) {
    if (number <= 0)
        return false;
    return (number & (number - 1)) == 0;
}

bool What2Power(int number) {
    int power = 0;
    while (number != 1) {
        number /= 2;
        power++;
    }
    return power;
}

void ShellsortSeq(int* vec, std::size_t n) {
    if (n <= 1)
        return;

    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i += 1) {
            int temp = vec[i];
            int j;

            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap)
                vec[j] = vec[j - gap];

            vec[j] = temp;
        }
    }
}

void BatcherOddOrEvenMerge(int *partStartPtr, int partSize, bool isOdd) {
    std::vector<int> tmp;
    tmp.reserve(partSize);

    int i = 0, j = partSize;
    int iLimit = partSize - 2, jLimit = (partSize * 2) - 2;
    if (isOdd) {
        i++, j++;
        iLimit++, jLimit++;
    }

    while (i <= iLimit && j <= jLimit) {
        if (partStartPtr[i] <= partStartPtr[j]) {
            tmp.push_back(partStartPtr[i]);
            i += 2;
        } else {
            tmp.push_back(partStartPtr[j]);
            j += 2;
        }
    }

    while (i <= iLimit) {
        tmp.push_back(partStartPtr[i]);
        i += 2;
    }
    while (j <= jLimit) {
        tmp.push_back(partStartPtr[j]);
        j += 2;
    }

    int k = 0;
    if (isOdd)
        k++;

    for (int t = 0; t != tmp.size(); k += 2, t += 1)
        partStartPtr[k] = tmp[t];
}

void BatcherParallelMerge(int* vec, int partSize, int partsCount) {
    # pragma omp parallel for
    for (int i = 0; i <= partsCount - 1; i++) {
        int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
        bool isOdd = (i % 2 == 1);
        int bPartSize = (partSize * 2);
        int *partStartPtr = vec + bPartSize * j;
        BatcherOddOrEvenMerge(partStartPtr, partSize, isOdd);
    }

    # pragma omp parallel for
    for (int i = 0; i <= partsCount - 1; i += 2) {
        int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
        int bPartSize = (partSize * 2);
        int *partStartPtr = vec + bPartSize * j;
        for (int k = 1; k <= bPartSize - 3; k++) {
            if (partStartPtr[k + 1] < partStartPtr[k]) {
                std::swap(partStartPtr[k + 1], partStartPtr[k]);
            }
        }
    }
}

void ShellsortParallel(std::vector<int>* vecPtr) {
    int oldSize = vecPtr->size();
    int partSize = 512;

    if (vecPtr->size() <= partSize) {
        ShellsortSeq(vecPtr->data(), vecPtr->size());
        return;
    }

    while (!Is2Power(vecPtr->size())) {
        vecPtr->push_back(FILLER);
    }

    int n = vecPtr->size();
    int* vecData = vecPtr->data();
    int partsCount = n / partSize;

    # pragma omp parallel for
        for (int i = 0; i < partsCount; i++) {
            int *partStartPtr = vecData + i * partSize;
            ShellsortSeq(partStartPtr, partSize);
        }

    while (n / partSize != 1) {
        BatcherParallelMerge(vecData, partSize, partsCount);
        partsCount /= 2, partSize *= 2;
    }
    while (vecPtr->size() != oldSize) {
        vecPtr->pop_back();
    }
}
