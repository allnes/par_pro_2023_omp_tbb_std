// Copyright 2023 Kochetov Maksim
#include "../../../modules/task_3/kochetov_m_shell_batcher/shell_batcher.h"

std::vector<int> GetRandomVec(int length) {
    std::random_device rndDev;
    std::mt19937 engine(rndDev());
    std::uniform_int_distribution<> dist(1, 100);
    std::vector<int> vec(length);
    for (int i = 0; i < length; i++) vec[i] = dist(engine);
    return vec;
}

void PrintVec(int* vec, int n) {
    for (int i = 0; i < n; i++) std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PrintVec(std::vector<int> vec) { PrintVec(vec.data(), vec.size()); }

bool Is2Power(int number) {
    if (number <= 0) return false;
    return ((number - 1) & number) == 0;
}

bool What2Power(int number) {
    int power = 0;
    while (number != 1) power++, number /= 2;
    return power;
}

void ShellsortSeq(int* vec, std::size_t n) {
    if (n <= 1) return;

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

void BatcherOddOrEvenMerge(int* partStartPtr, int partSize, bool isOdd) {
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
    if (isOdd) k++;

    for (int t = 0; t != tmp.size(); k += 2, t += 1) partStartPtr[k] = tmp[t];
}

struct UniversalFunctor {
    int* vec;
    int partSize;
    int taskId;

    UniversalFunctor(int* vec, int partSize, int taskId) {
        this->vec = vec;
        this->partSize = partSize;
        this->taskId = taskId;
    }

    void operator()(const tbb::blocked_range<size_t>& range) const {
        if (taskId == 0) {
            for (size_t i = range.begin(); i < range.end(); i++) {
                ShellsortSeq(vec + i * partSize, partSize);
            }
        } else if (taskId == 1) {
            for (size_t i = range.begin(); i < range.end(); i++) {
                int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
                bool isOdd = (i % 2 == 1);
                int* partStartPtr = vec + (partSize * 2) * j;
                BatcherOddOrEvenMerge(partStartPtr, partSize, isOdd);
            }
        } else {
            for (size_t i = range.begin(); i < range.end(); i++) {
                int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
                int bPartSize = (partSize * 2);
                int* partStartPtr = vec + bPartSize * j;
                for (int k = 1; k <= bPartSize - 3; k++) {
                    if (partStartPtr[k + 1] < partStartPtr[k]) {
                        std::swap(partStartPtr[k + 1], partStartPtr[k]);
                    }
                }
            }
        }
    }
};

void BatcherParallelMerge(int* vec, int partSize, int partsCount) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount),
                      UniversalFunctor(vec, partSize, 1));
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount, 2),
                      UniversalFunctor(vec, partSize, 2));
}

void ShellsortParallel(std::vector<int>* vecPtr) {
    int partSize = 512;
    int oldSize = vecPtr->size();

    if (vecPtr->size() <= partSize) {
        ShellsortSeq(vecPtr->data(), vecPtr->size());
        return;
    }

    while (!Is2Power(vecPtr->size())) {
        vecPtr->push_back(FILLER);
    }

    int partsCount = vecPtr->size() / partSize;

    UniversalFunctor functor(vecPtr->data(), partSize, 0);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount), functor);

    while (vecPtr->size() / partSize != 1) {
        BatcherParallelMerge(vecPtr->data(), partSize, partsCount);
        partsCount /= 2, partSize *= 2;
    }
    while (vecPtr->size() != oldSize) {
        vecPtr->pop_back();
    }
}
