// Copyright 2023 Bushmakin Maksim
#include "../../../modules/task_3/bushmakin_m_shellbatcher/shellbatcher.h"

std::vector<int> getRandomIntVec(int length) {
    std::random_device randomDevice;
    std::mt19937 engine(randomDevice());
    std::uniform_int_distribution<> distrib(1, 99);
    std::vector<int> vec(length);

    for (int i = 0; i < length; i++)
        vec[i] = distrib(engine);

    return vec;
}

void printIntVec(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << "\n";
}

void printIntVec(int* vec, int n) {
    for (int i = 0; i < n; i++)
        std::cout << vec[i] << " ";
    std::cout << "\n";
}

bool isPowerOf2(int number) {
    if (number <= 0) {
        return false;
    }
    return (number & (number - 1)) == 0;
}

bool getPowerOf2(int number) {
    int power = 0;
    while (number != 1)
        number /= 2, power++;
    return power;
}

void shellsortSequential(int* vec, std::size_t n) {
    // Arrays with sizes less than 2 shouldn't be sorted
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

void batcherMergeOdd(int *partVecStart, int partSize) {
    // Here we work with two arrays of size partSize laying sequentially in memory.
    // Vector called tmp will store merged result.
    std::vector<int> tmp;
    tmp.reserve(partSize);

    // Then we iterate over first and second subarrays with two counters
    // and merge all to tmp
    int i = 1, j = partSize + 1;
    while (i <= partSize - 1 && j <= (partSize * 2) - 1) {
        if (partVecStart[i] <= partVecStart[j]) {
            tmp.push_back(partVecStart[i]);
            i += 2;
        } else {
            tmp.push_back(partVecStart[j]);
            j += 2;
        }
    }

    // Assuming elements left unmerged in one of subarrays
    while (i <= partSize - 1) {
        tmp.push_back(partVecStart[i]);
        i += 2;
    }
    while (j <= (partSize * 2) - 1) {
        tmp.push_back(partVecStart[j]);
        j += 2;
    }

    // Writing tmp elements to partVecStart odd positions
    for (int k = 1, t = 0; t != tmp.size(); k += 2, t += 1) {
        partVecStart[k] = tmp[t];
    }
}

void batcherMergeEven(int *partVecStart, int partSize) {
    // Here we work with two arrays of size partSize laying sequentially in memory
    // Vector called tmp will store merged result.
    std::vector<int> tmp;
    tmp.reserve(partSize);

    // Then we iterate over first and second subarrays with two counters
    // and merge all to tmp
    int i = 0, j = partSize;

    while (i <= partSize - 2 && j <= (partSize * 2) - 2) {
        if (partVecStart[i] <= partVecStart[j]) {
            tmp.push_back(partVecStart[i]);
            i += 2;
        } else {
            tmp.push_back(partVecStart[j]);
            j += 2;
        }
    }

    // Assuming elements left unmerged in one of subarrays
    while (i <= partSize - 2) {
        tmp.push_back(partVecStart[i]);
        i += 2;
    }
    while (j <= (partSize * 2) - 2) {
        tmp.push_back(partVecStart[j]);
        j += 2;
    }

    // Writing tmp elements to partVecStart even positions
    for (int k = 0, t = 0; t != tmp.size(); k += 2, t += 1) {
        partVecStart[k] = tmp[t];
    }
}

struct SortPartsFunctor {
    int* vec;
    int partSize;

    SortPartsFunctor(int* vec, int partSize) {
        this->vec = vec;
        this->partSize = partSize;
    }

    void operator() (const tbb::blocked_range<size_t>& range) const {
        for (size_t i = range.begin(); i < range.end(); i++) {
            int *partVecStart = vec + i * partSize;
            shellsortSequential(partVecStart, partSize);
        }
    }
};

struct BatcherMergeFunctor1 {
    int* vec;
    int partSize;

    BatcherMergeFunctor1(int* vec, int partSize) {
        this->vec = vec;
        this->partSize = partSize;
    }

    void operator() (const tbb::blocked_range<size_t>& range) const {
        for (size_t i = range.begin(); i < range.end(); i++) {
            int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;

            bool isOdd = (i % 2 == 1);
            int biggerPartSize = (partSize * 2);

            int *partVecStart = vec + biggerPartSize * j;

            if (isOdd)
                batcherMergeOdd(partVecStart, partSize);
            else
                batcherMergeEven(partVecStart, partSize);
        }
    }
};

struct BatcherMergeFunctor2 {
    int* vec;
    int partSize;

    BatcherMergeFunctor2(int* vec, int partSize) {
        this->vec = vec;
        this->partSize = partSize;
    }

    void operator() (const tbb::blocked_range<size_t>& range) const {
        for (size_t i = range.begin(); i < range.end(); i++) {
            int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;

            int biggerPartSize = (partSize * 2);

            int *partVecStart = vec + biggerPartSize * j;

            // Comparison of neighboring elements to make partVec fully sorted
            for (int k = 1; k <= biggerPartSize - 3; k++)
                if (partVecStart[k] > partVecStart[k + 1])
                    std::swap(partVecStart[k], partVecStart[k + 1]);
        }
    }
};

void batcherMergeParallel(int* vec, int partSize, int partsCount) {
    BatcherMergeFunctor1 functor1(vec, partSize);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount), functor1);

    BatcherMergeFunctor2 functor2(vec, partSize);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount, 2), functor2);
}

void shellsortTBB(std::vector<int>* vecPtr) {
    int originalSize = vecPtr->size();
    int partSize = 1024;  // 2^10

    // If vecsize <= partSize, we can easily sort our array sequentially
    if (vecPtr->size() <= partSize) {
        shellsortSequential(vecPtr->data(), vecPtr->size());
        return;
    }

    // If vecsize is not a power of 2, we add stub elements
    // to make vec vecsize == some power of 2
    while (!isPowerOf2(vecPtr->size()))
        vecPtr->push_back(STUB_ELEMENT);

    int n = vecPtr->size();
    int* vec = vecPtr->data();

    int partsCount = n / partSize;

    // Parallel sorting of parts
    SortPartsFunctor functor(vec, partSize);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, partsCount), functor);

    // Executing parallel series of batcher merges
    while (n / partSize != 1) {
        batcherMergeParallel(vec, partSize, partsCount);
        partsCount /= 2, partSize *= 2;
    }

    // Removing stub elements from the end of our vec
    while (vecPtr->size() != originalSize)
        vecPtr->pop_back();
}
