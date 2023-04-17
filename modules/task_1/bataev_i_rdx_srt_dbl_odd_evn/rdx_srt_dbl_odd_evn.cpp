// Copyright 2023 Bataev Ivan
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <string>
#include <limits>
#include <random>
#include <cstring>
#include "../../../modules/task_1/bataev_i_rdx_srt_dbl_odd_evn/rdx_srt_dbl_odd_evn.h"

using std::uint8_t;

void printVector(const std::vector<double>& v, const std::string& prefix) {
    std::cout << prefix << "[";
    for (int i = 0; i < v.size() - 1; i++) { std::cout << v[i] << ", "; }
    std::cout << v[v.size() - 1] << "]\n";
}

std::vector<double> getRandomVector(int size, double left, double right) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<double> distr(left, right);

    std::vector<double> v(size);
    for (auto& elem : v) { elem = distr(mersenne); }
    return v;
}

void dblRdxSrt(uint8_t* inOutBuf, uint8_t* tmpBuf, const int bufSize) {
    uint8_t* inBuf = inOutBuf;
    uint8_t* outBuf = tmpBuf;
    const int dblBytes = sizeof(double);
    int countBytes[256];
    int offsets[256];

    int pass;
    for (pass = 0; pass < dblBytes - 1; pass++) {
        // count number of each byte in input buffer
        std::memset(countBytes, 0, 256*sizeof(int));
        for (int i = 0; i < bufSize; i+=dblBytes) {
            uint8_t rdxVal = inBuf[i + pass];
            countBytes[rdxVal]++;
        }

        // calc index offsets in output buffer for each byte
        offsets[0] = 0;
        for (int i = 1; i < 256; i++)
            offsets[i] = offsets[i - 1] + countBytes[i - 1];

        for (int i = 0; i < bufSize; i+=dblBytes) {
            uint8_t rdxVal = inBuf[i + pass];
            std::memcpy(outBuf + dblBytes*(offsets[rdxVal]++), inBuf + i, dblBytes);
            // increment to keep correct order when identical byte
        }

        std::swap(inBuf, outBuf);  // swap ptrs
    }

    // the last pass
    pass = dblBytes - 1;
    std::memset(countBytes, 0, 256*sizeof(int));
    for (int i = 0; i < bufSize; i+=dblBytes) {
        uint8_t rdxVal = inBuf[i + pass];
        countBytes[rdxVal]++;
    }

    int countNegatives = 0;
    for (int i = 128; i < 256; i++)
        countNegatives += countBytes[i];
    offsets[0] = countNegatives;
    offsets[255] = 0;
    for (int i = 1; i < 128; i++) {
        offsets[i] = offsets[i - 1] + countBytes[i - 1];  // for positive numbers
        offsets[255 - i] = offsets[256 - i] + countBytes[256 - i];  // for negative numbers
    }
    for (int i = 128; i < 256; i++)
        offsets[i] += countBytes[i];
    // for negative numbers to keep correct order when identical byte
    // (+ prefix decrement below)

    for (int i = 0; i < bufSize; i+=dblBytes) {
        uint8_t rdxVal = inBuf[i + pass];
        if (rdxVal < 128)  // for positive numbers
            std::memcpy(outBuf + dblBytes*(offsets[rdxVal]++), inBuf + i, dblBytes);
        else  // for negative numbers
            std::memcpy(outBuf + dblBytes*(--offsets[rdxVal]), inBuf + i, dblBytes);
    }

    // if result is in tmpBuf copy it to inOutBuf
    if (pass%2 == 0)
        std::memcpy(inOutBuf, tmpBuf, bufSize);
}

// pair of buffer parts for compare-exchange
struct Comparator {
    int part1;
    int part2;
};

// void printVector(const std::vector<Comparator>& v, const std::string& prefix) {
//     if (v.size() == 0) { return; }
//     std::cout << prefix << "[";
//     for (int i = 0; i < v.size() - 1; i++)
//         std::cout << "(" << v[i].part1 << ", " << v[i].part2 << "), ";
//     std::cout << "(" << v[v.size() - 1].part1 << ", " << v[v.size() - 1].part2 << ")]\n";
// }

void mrgNets(const std::vector<int>& upParts, const std::vector<int>& downParts, std::vector<Comparator>* comprtrs) {
    size_t sumSize = upParts.size() + downParts.size();  // n + m
    if (sumSize == 1) {  // network is empty
        return;
    } else if (sumSize == 2) {  // network contains only one comparator
        (*comprtrs).push_back({ upParts[0], downParts[0] });
        return;
    }

    std::vector<int> upOddParts;
    std::vector<int> upEvenParts;
    for (int i = 0; i < upParts.size(); i++) {
        if (i % 2)
            upEvenParts.push_back(upParts[i]);
        else
            upOddParts.push_back(upParts[i]);
    }
    std::vector<int> downOddParts;
    std::vector<int> downEvenParts;
    for (int i = 0; i < downParts.size(); i++) {
        if (i % 2)
            downEvenParts.push_back(downParts[i]);
        else
            downOddParts.push_back(downParts[i]);
    }

    mrgNets(upOddParts, downOddParts, comprtrs);
    mrgNets(upEvenParts, downEvenParts, comprtrs);

    std::vector<int> unionParts(sumSize);
    std::memcpy(unionParts.data(), upParts.data(), upParts.size()*sizeof(int));
    std::memcpy(unionParts.data() + upParts.size(), downParts.data(), downParts.size()*sizeof(int));

    for (int i = 1; i < sumSize - 1; i += 2)
        (*comprtrs).push_back({ unionParts[i], unionParts[i + 1] });
}

void bldNet(const std::vector<int>& parts, std::vector<Comparator>* comprtrs) {
    if (parts.size() == 1)
        return;

    std::vector<int> upParts(parts.begin(), parts.begin() + parts.size() / 2);
    std::vector<int> downParts(parts.begin() + parts.size() / 2, parts.end());

    bldNet(upParts, comprtrs);
    bldNet(downParts, comprtrs);
    mrgNets(upParts, downParts, comprtrs);
}

void compExch(double** upPart, double** downPart, double** upTmpPart, double** downTmpPart, int sizePart) {
    // in "up" put smaller elems, in "down" larger elems
    for (int i = 0, j = 0, k = 0; k < sizePart; k++) {
        if ((*upPart)[i] < (*downPart)[j])
            (*upTmpPart)[k] = (*upPart)[i++];
        else
            (*upTmpPart)[k] = (*downPart)[j++];
    }

    for (int i = sizePart - 1, j = sizePart - 1, k = sizePart - 1; k >= 0; k--) {
        if ((*downPart)[i] > (*upPart)[j])
            (*downTmpPart)[k] = (*downPart)[i--];
        else
            (*downTmpPart)[k] = (*upPart)[j--];
    }

    // swap ptrs
    std::swap(*upTmpPart, *upPart);
    std::swap(*downTmpPart, *downPart);
}

// all "numParts" parts must be sorted and the same size "sizePart"
void oddEvnMerge(std::vector<double>* buf, std::vector<double>* tmpBuf, int numParts, int sizePart) {
    if ((*buf).size() != numParts * sizePart)
        return;
    std::vector<double*> partsPtrs;
    std::vector<double*> tmpPartsPtrs;
    for (int shift = 0; shift < (*buf).size(); shift += sizePart) {
        partsPtrs.push_back((*buf).data() + shift);
        tmpPartsPtrs.push_back((*tmpBuf).data() + shift);
    }

    std::vector<Comparator> comprtrs;
    std::vector<int> parts;
    for (int i = 0; i < numParts; i++)
        parts.push_back(i);
    // build Batcher's sotrting network for parts of buffer
    bldNet(parts, &comprtrs);

    // printVector(comprtrs, "Comparators: ");

    // use the network to merge these parts
    for (int i = 0; i < comprtrs.size(); ++i)
        compExch(&(partsPtrs[comprtrs[i].part1]), &(partsPtrs[comprtrs[i].part2]),
                    &(tmpPartsPtrs[comprtrs[i].part1]), &(tmpPartsPtrs[comprtrs[i].part2]), sizePart);
        // compare-exchange for each comparator from sorting network

    // if partPtr points to part of tmpBuf copy this part to buf
    for (int i = 0; i < numParts; i++)
        if (partsPtrs[i] != (*buf).data() + i*sizePart)
            std::memcpy((*buf).data() + i*sizePart, (*tmpBuf).data() + i*sizePart, sizePart*sizeof(double));
}

void seqRdxSrt(std::vector<double>* buf, const int size, const int numParts) {
    // all sorted parts must be the same size for Batcher's merge
    // add temp max elems to the end of buf while it's not
    while ((*buf).size()%numParts)
        (*buf).push_back(std::numeric_limits<double>::max());
        // will be added (numParts - (*buf).size()%numParts) tmp elems

    std::vector<double> tmpBuf((*buf).size());
    int sizePart = (*buf).size()/numParts;

    // sort each part separately with radix sort
    for (int shift = 0; shift < (*buf).size(); shift += sizePart)
        dblRdxSrt(reinterpret_cast<uint8_t*>((*buf).data() + shift),
                    reinterpret_cast<uint8_t*>(tmpBuf.data() + shift), sizePart*sizeof(double));
    // printVector(*buf);

    // merging parts together
    oddEvnMerge(buf, &tmpBuf, numParts, sizePart);

    // delete temp elems
    while ((*buf).size() - size)
        (*buf).pop_back();
}

