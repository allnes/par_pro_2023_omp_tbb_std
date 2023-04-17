// Copyright 2023 Rezchikov Dmitrii
#include "../../../modules/task_1/rezchikov_d_radix_simple/ops.h"




void countingSortSeq(std::vector<int> * array, int l, int r, int place) {
    const int max = 10;
    int size = r - l;
    std::vector<int> output(size);
    std::vector<int> count(max);

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = l; i < r; ++i)
        count[((*array)[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; ++i)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = r - 1; i >= l; --i) {
        count[((*array)[i] / place) % 10]--;
        output[count[((*array)[i] / place) % 10]] = (*array)[i];
    }
    for (int i = l; i < r; i++)
        (*array)[i] = output[i];
}

void radSortSeq(std::vector<int> * vec) {
    if ( vec->size() < 2 ) {
        return;
    }
    int len = std::floor(
                        std::log10(
                            *std::max_element(vec->begin(), vec->end()))) + 1;
    int pow = 1;

    for (int i = 0; i < len; ++i) {
        countingSortSeq(vec, 0, vec->size(), pow);
        pow *= 10;
    }
}

void mergeRadixSort(std::vector<int> * vec) {
    if (vec->size() < 2) {
        return;
    }
    int pvt = vec->size() / 2;

    std::vector<int> v1(vec->begin(), vec->begin() + pvt);
    std::vector<int> v2(vec->begin() + pvt, vec->end() );

    radSortSeq(&v1);
    radSortSeq(&v2);

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vec->begin());
}

std::vector<int> getRndVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());

    std::vector<int> res(size);

    for (int i = 0; i < size; ++i) {
        res[i] = gen() % 1000;
    }
    return res;
}

/*
void radSortPar( std::vector<int> & vec ){
    if ( vec.size() < 2 ){
        return;
    }
    #pragma omp parallel shared(vec)
    {
        int l, r;
        l = omp_get_thread_num() * (vec.size() / omp_get_num_threads() );
        r = omp_get_thread_num() == omp_get_num_threads()
                                    ? vec.size()
                                    : (omp_get_thread_num() + 1 ) * (vec.size() / omp_get_num_threads() );
        // #pragma omp seq
        //     std::cout << "thread #" << omp_get_thread_num() << ": l = " << l << ", r = " << r << "\n";
        int len = std::floor(std::log10(*std::max_element(vec.begin() + l, vec.begin() + r))) + 1;
        int pow = 1;
        for ( int i = 0; i < len; ++i){          
            countingSortSeq(vec, l, r, pow);
            pow *= 10;
        }
        #pragma 
    }
    #pragma omp parallel
    {
        //std::cout << omp_get_num_threads() << std::endl;   
         #pragma omp for schedule(static)
            for ( int i = 0; i < len; ++i){
                std::vector<int> vTmp(vec.size());
                countingSortSeq(vec, vec.size(), pow);
                pow *= 10;
            }
    }

}
*/
