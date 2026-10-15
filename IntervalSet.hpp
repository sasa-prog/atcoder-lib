#include <bits/stdc++.h>
using namespace std;
using ll=long long;

// 区間をsetで管理するテク
struct IntervalSet {
    set<pair<ll, ll>> st; // {R, L}の形式で区間を管理する
    // 区間を追加
    void insert(ll l, ll r) {
        auto itr = st.lower_bound({l, LLONG_MIN});
        if (itr != st.begin()) {
            auto pre = prev(itr);
            if (pre->first + 1 >= l) {
                l = min(l, pre -> second);
                r = max(r, pre->first);
                st.erase(pre);
            }
        }
        while (itr != st.end() && itr->second <= r + 1) {
            l = min(l, itr->second);
            r = max(r, itr->first);
            itr = st.erase(itr);
        }
        st.insert({r, l});
    }
    // 区間を削除
    void erase(ll l, ll r) {
        auto itr = st.lower_bound({l, LLONG_MIN});
        vector<pair<ll, ll>> v;
        while(itr != st.end()) {
            ll sl = itr->second;
            ll sr = itr->first;
            if (r < sl) break;
            if ((sl < l) && (r < sr)) {
                v.push_back({l - 1, sl});
                v.push_back({sr, r + 1});
            } else if ((sl < l) && (l <= sr)) {
                v.push_back({l - 1, sl});
            } else if ((r < sr)&&(sl <= r)) {
                v.push_back({sr, r + 1});
            }
            itr = st.erase(itr);
        }
        for (int i = 0;i < v.size();i++) {
            st.insert(v[i]);
        }
    }
    // 空判定
    bool empty() {
        return st.empty();
    }
    // 幾つの重複しない区間が登録されているか
    int size() {
        return st.size();
    }
    // xを含む区間が存在するか
    bool contains(ll x) {
        auto itr = st.lower_bound({x, LLONG_MIN});

        if (itr == st.end()) {
            return false;
        }

        return itr->second <= x;
    }
};
