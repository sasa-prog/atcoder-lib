#include <bits/stdc++.h>
using namespace std;


/// @brief CartesianTree
/// @tparam T 要素の型(int, long long, double?)
/// @tparam Compare 比較関数(指定なし・greater：小さい値が根、less：大きい値が根)
// 2026/09/02版
template <typename T, typename Compare = greater<T>>
struct CartesianTree {
    vector<int> par;
    vector<int> left;
    vector<int> right;
    CartesianTree(const vector<T>& v) {
        int n = v.size();
        par.assign(n, -1);
        left.assign(n, -1);
        right.assign(n, -1);
        vector<int> st;
        st.reserve(n);
        for (int i = 0;i < n;i++) {
            int last = -1;
            while (!st.empty() && Compare()(v[st.back()], v[i])) {
                last = st.back();
                st.pop_back();
            }
            if (!st.empty()) {
                par[i] = st.back();
                right[st.back()] = i;
            }
            if (last != -1) {
                par[last] = i;
                left[i] = last;
            }
            st.push_back(i);
        }
    }
};


