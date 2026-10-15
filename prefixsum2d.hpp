#include <bits/stdc++.h>
using namespace std;

// 二次元累積和 1-indexed
struct PrefixSum2d {
    int h, w;
    vector<vector<int>> grid;

    PrefixSum2d(int h, int w) : h(h), w(w), grid(h + 1, vector<int>(w + 1)) {}

    void init() {
        for (int i = 1;i <= h;i++) {
            for (int j = 1;j <= w;j++) {
                grid[i][j] += grid[i][j - 1];
            }
        }
        for (int i = 1;i <= h;i++) {
            for (int j = 1;j <= w;j++) {
                grid[i][j] += grid[i - 1][j];
            }
        }
    }
    // a,b=左上、c,d=右上
    int get(int a, int b, int c, int d) {
        return grid[c][d] - grid[c][b - 1] - grid[a - 1][d] + grid[a - 1][b - 1];
    }
};
