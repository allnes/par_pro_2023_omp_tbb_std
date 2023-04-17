// Copyright 2023 Sukharev Artem

#include<vector>
#include<stack>
#include<iostream>
#include<algorithm>
#include<cmath>
#include "../../../modules/task_1/sukharev_a_convex_hull_binimg/sukharev_a_convex_hull_binimg.h"

std::vector<std::vector<std::pair<int, int>>> build_components(
    const std::vector<std::vector<int>>& img, const int n, const int m) {
    std::vector<std::vector<std::pair<int, int>>> res;
    std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
    int dx[8] = {0, 0, -1, -1, -1, 1, 1, 1};
    int dy[8] = {1, -1, -1, 1, 0, -1, 1, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j] == false && img[i][j] == 1) {
                std::stack<std::pair<int, int>> st;
                st.push(std::make_pair(i, j));
                used[i][j] = true;
                res.push_back(std::vector<std::pair<int, int>>(0));
                while (!st.empty()) {
                    int tx = st.top().first;
                    int ty = st.top().second;
                    res.back().push_back(std::make_pair(tx, ty));
                    st.pop();
                    for (int p = 0; p < 8; p++) {
                        int nx = tx + dx[p];
                        int ny = ty + dy[p];
                        if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                            if (used[nx][ny] == false && img[nx][ny] == 1) {
                                st.push(std::make_pair(nx, ny));
                                used[nx][ny] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

int crossProd(std::pair<int, int> a, std::pair<int, int> b,
            std::pair<int, int> c) {
    return (b.first - a.first) * (c.second - b.second)
                - (c.first - b.first) * (b.second - a.second);
}

std::vector<std::pair<int, int>> graham(
                const std::vector<std::pair<int, int>>& _v) {
    std::vector<std::pair<int, int>> v = _v;
    int n = v.size();
    int o = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[o]) {
            o = i;
        }
    }
    if (o != 0) {
        swap(v[o], v[0]);
    }
    std::pair<int, int> bg = v[0];
    std::sort(v.begin()+1, v.end(),
        [bg](std::pair<int, int> a, std::pair<int, int> b){
            int u = (a.second - bg.second) * (b.first - bg.first);
            int v = (b.second - bg.second) * (a.first - bg.first);
            if (u == v) {
                return std::hypot(a.first - bg.first, a.second - bg.second)<
                       std::hypot(b.first - bg.first, b.second - bg.second);
            }
            return u < v;
        });
    std::vector<std::pair<int, int>> res = {bg};
    for (int i = 1; i < n; i++) {
        while (res.size() >= 2
                && crossProd(res[res.size()-2], res.back(), v[i]) <= 0) {
            res.pop_back();
        }
        res.push_back(v[i]);
//        std::cout<<"====="<<res.size()<<"\n";
//        for(auto &x:res)
//            std::cout<<x.first<<" "<<x.second<<"\n";
    }
    while (res.size() >= 3
            && crossProd(res[res.size()-2], res.back(), bg) <= 0) {
        res.pop_back();
    }
    return res;
}

std::vector<std::vector<int>> build_convhull_img(
        const std::vector<std::vector<int>>& img) {
    int n, m;
    n = img.size();
    m = img[0].size();
    std::vector<std::vector<std::pair<int, int>>> compn =
            build_components(img, n, m);
    std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
    for (int k = 0; k < compn.size(); k++) {
        compn[k] = graham(compn[k]);
        for (const std::pair<int, int> x : compn[k]) {
            res[x.first][x.second] = k + 1;
        }
    }
    return res;
}

void printImg(const std::vector<std::vector<int>>& g) {
    for (const std::vector<int> &x : g) {
        for (int y : x) {
            std::cout << y;
        }
        std::cout << "\n";
    }
}

