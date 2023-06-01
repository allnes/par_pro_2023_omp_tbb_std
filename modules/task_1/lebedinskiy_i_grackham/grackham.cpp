// Copyright 2023 Lebedinskiy Ilya
#include "../../../modules/task_1/lebedinskiy_i_grackham/grackham.h"
std::pair<int, int> p0;

int distance(const std::pair<int, int>& dot1, const std::pair<int, int>& dot2) {
    return (dot1.first - dot2.first) * (dot1.first - dot2.first)+
(dot1.second - dot2.second) * (dot1.second - dot2.second);
}

int rotation(const std::pair<int, int>& dot1, const std::pair<int, int>& dot2,
    const std::pair<int, int>& dot3) {
    int val = (dot2.second - dot1.second) * (dot3.first - dot2.first) -
        (dot2.first - dot1.first) * (dot3.second - dot2.second);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

std::vector<std::pair<int, int>> greckham_seq(std::vector<std::pair<int, int>> vec) {
    if (vec.size() == 0) {
        std::vector<std::pair<int, int>> zero = { { 0, 0 } };
        return zero;
    }
    if (vec.size() == 3) {
        return vec;
    }
    int min = 0;
    int ymin = vec[0].second;
    int size = vec.size();
    for (int i = 1; i < size; i++) {
        int y = vec[i].second;

        if ((y < ymin) || (ymin == y && vec[i].first < vec[min].first)) {
            ymin = vec[i].second;
            min = i;
        }
    }
    std::swap(vec[0], vec[min]);
    p0 = vec[0];
    qsort(&vec[1], size - 1, sizeof(std::pair<int, int>), compare);
    std::vector<std::pair<int, int>> res;
    res.push_back(vec[0]);
    res.push_back(vec[1]);
    res.push_back(vec[2]);

    for (int i = 3; i < size; i++) {
        while (res.size() > 1 && rotation(res[res.size() - 2], res.back(), vec[i]) != 2) {
            res.pop_back();
        }
        res.push_back(vec[i]);
    }
    return res;
}

std::vector<std::pair<int, int>> gen_dots(int vectorSize) {
    std::mt19937 rand_r(time(0));
    std::vector<std::pair<int, int>> vec(vectorSize);
    for (int i = 0; i < vectorSize; i++) {
        vec[i].first = rand_r() % 100;
        vec[i].second = rand_r() % 100;
    }
    return vec;
}

int compare(const void* vp1, const void* vp2) {
    std::pair<int, int>* p1 = (std::pair<int, int>*)vp1;
    std::pair<int, int>* p2 = (std::pair<int, int>*)vp2;

    int o = rotation(p0, *p1, *p2);
    if (o == 0)
        return (distance(p0, *p2) >= distance(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}
